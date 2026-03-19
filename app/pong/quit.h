#ifndef QUIT
#define QUIT

#include <ArgonEngine/Node.h>
#include <ArgonEngine/VirtualResource.h>
#include <ArgonEngine/Text.h>
#include <ArgonEngine/ArgonInit.h>
#include <vector>
#include <functional>

#include "buttonUtils.h"
#include "menu.h"
#include "constants.h"

struct QuitGame : Argon::Node {
    Argon::VirtualResource font = "resource://GNF.ttf";

    Argon::Label message;

    GrowButton yes;
    GrowButton no;

    Menu menu;

    std::shared_ptr<Argon::Node> backTo;

    bool goBack;

    QuitGame(std::shared_ptr<Argon::Node> backTo):
        backTo(backTo),
        goBack(false),
        yes(std::vector<std::string>{"select", "leftClick"},
            [&](){ Argon::terminate_engine(); return nullptr; },
            Argon::Vector2f(1,1),
            Argon::Vector2f(2,2)),
        
        no(std::vector<std::string>{"select", "leftClick"},
           [=](){ return backTo; },
           Argon::Vector2f(1,1),
           Argon::Vector2f(2,2)),

        menu(std::vector<GrowButton*>{&yes, &no})
    {
        message.color.set(1,1,1,1);
        message.render_str("Are you sure you want to quit?",font,Argon::kLineCenter);

        yes.render("YES",font,"resource://buttonBG.png",Argon::kLineCenter, 0.5, 0);
        no.render("NO",font,"resource://buttonBG.png",Argon::kLineCenter, 0.5, 0);

        menu.incKey = "left";
        menu.decKey = "right";
    }

    void hide() {
        message.position[2] = 0;
        yes.setzPosition(0);
        no.setzPosition(0);
    }

    std::shared_ptr<Argon::Node> animate(float time) {
        auto sendTo = menu.animate(time);

        message.position[0] = 0;
        message.position[1] = 4;
        message.position[2] = constants::zAxisPos/2;

        yes.setxPosition(-2);
        yes.setzPosition(constants::zAxisPos/2);

        no.setxPosition(2);
        no.setzPosition(constants::zAxisPos/2);

        return sendTo;
    }
};

#endif

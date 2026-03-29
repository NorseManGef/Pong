#ifndef MENU_RETURN
#define MENU_RETURN

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <ArgonEngine/Text.h>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <ArgonEngine/Addons/uilib/ui.h>

#include "object.h"
#include "constants.h"
#include "wall.h"
#include "optionsMenu.h"

struct menuReturnModal : Argon::Node {
    Argon::VirtualResource font = "resource://GNF.ttf";
    Argon::VirtualResource buttonBG = "resource://buttonBG.png";

    Wall top;
    Wall bottom;
    Wall left;
    Wall right;
    Wall background;

    Argon::Label question;

    Argon::Addons::GrowButton yes;
    Argon::Addons::GrowButton no;

    float zAxisPos;
    float zAxisPosBG;
    float xRange;
    float yRange;

    IOInterface& buttons = IOInterface::instance();

    Argon::Addons::Menu menu;

    std::shared_ptr<Argon::Node> mainMenu;
    std::shared_ptr<Argon::Node> backTo;

    menuReturnModal(std::shared_ptr<Argon::Node> backTo, std::shared_ptr<Argon::Node> mainMenu):
        backTo(backTo),
        mainMenu(mainMenu),
        yes(std::vector<std::string>{"select", "leftClick"},
            [=](){ return mainMenu; },
            Argon::Vector2f(.3, .3),
            Argon::Vector2f(.45, .45)),
        no(std::vector<std::string>{"select", "leftClick"},
           [=](){ return backTo; },
           Argon::Vector2f(.3, .3),
           Argon::Vector2f(.45, .45)),

        menu(std::vector<Argon::Addons::Button*>{&yes, &no})
    {
        zAxisPos = constants::zAxisPos/4;

        menu.mousePosCorrection = abs(zAxisPos);

        zAxisPosBG = zAxisPos*1.5;

        // Makes the visible range of the x dimension one third of the xRange of Pong
        xRange = (constants::xRange/3)*(zAxisPos/constants::zAxisPos);

        // Makes the visible range of the y dimension one fourth of the yRange of Pong
        yRange = (constants::xRange/4)*(zAxisPos/constants::zAxisPos);

        yes.render("YES",font,buttonBG,Argon::kLineCenter, 0.5, 0);
        no.render("NO",font,buttonBG,Argon::kLineCenter, 0.5, 0);

        float lineWidth = yRange/15.0;
        top.dimensions.set(xRange*2.0+lineWidth, lineWidth, 1);
        bottom.dimensions.set(xRange*2.0+lineWidth, lineWidth, 1);

        left.dimensions.set(lineWidth, yRange*2, 1);
        right.dimensions.set(lineWidth, yRange*2, 1);

        float bgOffset = zAxisPosBG/zAxisPos;
        background.dimensions.set(xRange*2*bgOffset, yRange*2*bgOffset, 1);

        background.color = Argon::kBlackColor;

        question.render_str("Are you sure you want\nto return to menu?", font, Argon::kLineCenter);
        menu.incKey = "left";
        menu.decKey = "right";

        yes.selected = true;
        menu.selection = 0;
    }

    void hide() {
        top.position.set_all(0);
        bottom.position.set_all(0);

        left.position.set_all(0);
        right.position.set_all(0);

        background.position.set_all(0);

        yes.setPosition(0,0,0);
        no.setPosition(0,0,0);

        question.position.set_all(0);
    }

    std::shared_ptr<Argon::Node> animate(float time) {
        auto sendTo = menu.animate(time);

        top.position.set(0, yRange, zAxisPos);
        bottom.position.set(0, -yRange, zAxisPos);

        left.position.set(-xRange, 0, zAxisPos);
        right.position.set(xRange, 0, zAxisPos);

        background.position.set(0, 0, zAxisPosBG);

        yes.setPosition((-xRange/2)+.06, -yRange/2, zAxisPos);
        no.setPosition((xRange/2)+.05, -yRange/2, zAxisPos);

        question.position.set(0, yRange/3, zAxisPos);
        question.scale.set(.16, .16, 1);

        if(menu.keys.isReleased("pause")){
            return backTo;
        }
        
        return sendTo;
    }
};

#endif

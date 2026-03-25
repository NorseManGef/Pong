#ifndef OPTIONS_MENU
#define OPTIONS_MENU

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <ArgonEngine/Addons/BorderedLabel.h>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "wall.h"
#include "ButtonInterface.h"
#include "menu.h"
#include "buttonUtils.h"

struct OptionsMenu : Argon::Node {
    Argon::VirtualResource font = "resource://GNF.ttf";
    Argon::VirtualResource buttonBG = "resource://buttonBG.png";
    Wall outterTop;
    Wall outterBottom;
    Wall outterLeft;
    Wall outterRight;

    Wall innerLeft;

    GrowButton Back;
    GrowButton Controls;
    GrowButton Video;
    GrowButton Audio;

    Menu menu;

    Argon::Input input;

    Argon::Vector2f mousePosOld;

    ButtonInterface& buttons = ButtonInterface::instance();

    bool useSelection;

    bool mouseMoved;

    bool changed;

    OptionsMenu(std::shared_ptr<Argon::Node> prevNode):
        useSelection(false),
        changed(false),
        Back(std::vector<std::string>{"select", "leftClick"},
             [=](){ return prevNode; },
             Argon::Vector2f(1,1),
             Argon::Vector2f(1.5,1.5)),

        Controls(std::vector<std::string>{"select", "leftClick"},
                 [&](){ return nullptr; }, // TODO: make Controls do something
                 Argon::Vector2f(1,1),
                 Argon::Vector2f(1.5,1.5)),
        
        Video(std::vector<std::string>{"select", "leftClick"},
              [&](){ return nullptr; }, // TODO: make Video do something
              Argon::Vector2f(1,1),
              Argon::Vector2f(1.5,1.5)),

        Audio(std::vector<std::string>{"select", "leftClick"},
              [&](){ return nullptr; }, // TODO: make Audio do something
              Argon::Vector2f(1,1),
              Argon::Vector2f(1.5,1.5)),

        menu(std::vector<GrowButton*>{&Back, &Controls, &Video, &Audio})
    {
        Back.render("BACK",font,buttonBG,Argon::kLineCenter, 0.5, 0);
        Controls.render("CONTROLS",font,buttonBG,Argon::kLineCenter, 0.5, 0);
        Video.render("VIDEO",font,buttonBG,Argon::kLineCenter, 0.5, 0);
        Audio.render("AUDIO",font,buttonBG,Argon::kLineCenter, 0.5, 0);
    }

    std::shared_ptr<Argon::Node> animate(float time) {
        return nullptr;
    }
};

#endif

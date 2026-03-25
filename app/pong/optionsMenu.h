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
#include "constants.h"
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

    float zAxisPos;
    float zAxisPosBG;
    float xRange;
    float yRange;

    /*!
        \param prevNode the node from which the optionsMenu was opened.
        \param zAxisPos the zAxisPos of the previous node. 
        This menu's zAxisPos will be set to half of that value.
    */
    OptionsMenu(std::shared_ptr<Argon::Node> prevNode, float zAxisPos):
        useSelection(false),
        changed(false),
        zAxisPos(zAxisPos/2),
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
        zAxisPosBG = zAxisPos*1.5;

        // Makes the xRange equal to the xRange of Pong
        xRange = constants::xRange*(zAxisPos/constants::zAxisPos);

        // Makes the yRange equal to the yRange of Pong
        yRange = constants::yRange*(zAxisPos/constants::zAxisPos)*Argon::Screen::ratio();

        Back.render("BACK",font,buttonBG,Argon::kLineCenter, 0.5, 0);
        Controls.render("CONTROLS",font,buttonBG,Argon::kLineCenter, 0.5, 0);
        Video.render("VIDEO",font,buttonBG,Argon::kLineCenter, 0.5, 0);
        Audio.render("AUDIO",font,buttonBG,Argon::kLineCenter, 0.5, 0);

        float lineWidth = yRange/15.;
        outterTop.dimensions.set((xRange*2.)+lineWidth,lineWidth,1);
        outterBottom.dimensions.set((xRange*2.)+lineWidth,lineWidth,1);
        outterLeft.dimensions.set(lineWidth,(yRange*2.)+lineWidth,1);
        outterRight.dimensions.set(lineWidth,(yRange*2.)+lineWidth,1);
    }

    std::shared_ptr<Argon::Node> animate(float time) {
        outterTop.position.set(0,yRange,zAxisPos);
        outterBottom.position.set(0,-yRange,zAxisPos);
        outterLeft.position.set(-xRange,0,zAxisPos);
        outterRight.position.set(xRange,0,zAxisPos);
        return nullptr;
    }
};

#endif

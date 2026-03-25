#ifndef OPTIONS_MENU
#define OPTIONS_MENU

#include <iostream>

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
    Wall innerTop;

    GrowButton Back;
    GrowButton Controls;
    GrowButton Video;
    GrowButton Audio;

    Argon::Label optionMenuType;

    Menu menu;

    ButtonInterface& buttons = ButtonInterface::instance();

    bool useSelection;

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
             Argon::Vector2f(.35,.35),
             Argon::Vector2f(.45,.45)),

        Controls(std::vector<std::string>{"select", "leftClick"},
                 [&](){ return nullptr; }, // TODO: make Controls do something
                 Argon::Vector2f(.25,.35),
                 Argon::Vector2f(.275,.45)),
        
        Video(std::vector<std::string>{"select", "leftClick"},
              [&](){ return nullptr; }, // TODO: make Video do something
              Argon::Vector2f(.35,.35),
              Argon::Vector2f(.4,.45)),

        Audio(std::vector<std::string>{"select", "leftClick"},
              [&](){ return nullptr; }, // TODO: make Audio do something
              Argon::Vector2f(.35,.35),
              Argon::Vector2f(.4,.45)),

        menu(std::vector<GrowButton*>{&Back, &Controls, &Video, &Audio})
    {
        zAxisPosBG = zAxisPos*1.5;

        menu.mousePosCorrection = abs(zAxisPos/2);

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

        innerLeft.dimensions.set(lineWidth,(yRange*2.)-lineWidth,1);
        innerTop.dimensions.set((xRange*2.)-lineWidth,lineWidth,1);

        std::cout << "zAxisPos: " << zAxisPos << std::endl;
    }

    std::shared_ptr<Argon::Node> animate(float time) {
        auto sendTo = menu.animate(time);

        outterTop.position.set(0,yRange,zAxisPos);
        outterBottom.position.set(0,-yRange,zAxisPos);
        outterLeft.position.set(-xRange,0,zAxisPos);
        outterRight.position.set(xRange,0,zAxisPos);

        innerLeft.position.set(-xRange*.7,0,zAxisPos);
        innerTop.position.set(0,yRange*.7,zAxisPos);

        Back.setPosition(-xRange*.85, yRange*.85,zAxisPos);

        Controls.setPosition(-xRange*.85, yRange*.55,zAxisPos);
        Video.setPosition(-xRange*.85, yRange*.35,zAxisPos);
        Audio.setPosition(-xRange*.85, yRange*.15,zAxisPos);

        return sendTo;
    }
};

#endif

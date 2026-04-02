#ifndef PAUSEMENU
#define PAUSEMENU

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Hardware.h>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <functional>

#include "constants.h"
#include "wall.h"
#include "menuReturnModal.h"
#include "optionsMenu.h"

struct pauseModal : Argon::Node, std::enable_shared_from_this<pauseModal> {
    Argon::VirtualResource font = "resource://GNF.ttf";
    Argon::VirtualResource buttonBG = "resource://buttonBG.png";
    Wall top;
    Wall bottom;
    Wall left;
    Wall right;
    Wall background;

    Argon::Addons::GrowButton resume;
    Argon::Addons::GrowButton options;
    Argon::Addons::GrowButton back;

    Argon::Addons::Menu menu;

    float zAxisPos;
    float zAxisPosBG;
    float xRange;
    float yRange;

    std::shared_ptr<Argon::Node> backTo;

    std::shared_ptr<Argon::Node> mainMenu;

    IOInterface& buttons = IOInterface::instance();

    pauseModal(std::shared_ptr<Argon::Node> backTo, std::shared_ptr<Argon::Node> mainMenu):
        backTo(backTo),
        mainMenu(mainMenu),
        zAxisPos(constants::zAxisPos/2),
        resume(std::vector<std::string>{"select", "leftClick"},
               [=](){ return backTo; },
               Argon::Vector2f(1, 1),
               Argon::Vector2f(1.25, 1.25)),
        options(std::vector<std::string>{"select", "leftClick"},
                [&](){ return std::make_shared<OptionsMenu>(shared_from_this(), zAxisPos); },
                Argon::Vector2f(.90, 1),
                Argon::Vector2f(1.15, 1.25)),
        back(std::vector<std::string>{"select", "leftClick"},
             [=](){ return std::make_shared<menuReturnModal>(shared_from_this(), mainMenu); },
             Argon::Vector2f(1, 1),
             Argon::Vector2f(1.25, 1.25)),
        menu(std::vector<Argon::Addons::Selectable*>{&resume, &options, &back})
    {
        back.willHide = false;

        zAxisPosBG = zAxisPos*1.5;

        // Makes the visible range of the x dimension half of the xRange of Pong
        xRange = (constants::xRange/2)*(zAxisPos/constants::zAxisPos); 

        // Makes the visible range of the y dimension half of the yRange of Pong
        yRange = (constants::yRange/2)*(zAxisPos/constants::zAxisPos);

        resume.render("RESUME",font,buttonBG,Argon::kLineCenter, 0.5, 0);
        options.render("OPTIONS",font,buttonBG,Argon::kLineCenter, 0.5, 0);
        back.render("MENU",font,buttonBG,Argon::kLineCenter, 0.5, 0);

        float lineWidth = yRange/15.0;
        top.dimensions.set(xRange*2.0+lineWidth, lineWidth, 1);
        bottom.dimensions.set(xRange*2.0+lineWidth, lineWidth, 1);

        left.dimensions.set(lineWidth, yRange*2, 1);
        right.dimensions.set(lineWidth, yRange*2, 1);

        float bgOffset = zAxisPosBG/zAxisPos;
        background.dimensions.set(xRange*2*bgOffset, yRange*2*bgOffset, 1);

        background.color = Argon::kBlackColor;

        resume.selected = true;
        menu.selection = 0;
    }

    void hide() {
        top.position.set_all(0);
        bottom.position.set_all(0);

        left.position.set_all(0);
        right.position.set_all(0);

        background.position.set_all(0);

        resume.setPosition(0,0,0);
        options.setPosition(0,0,0);
        back.setPosition(0,0,0); 
        menu.willHide = false;
    }

    std::shared_ptr<Argon::Node> animate(float time) {
        auto sendTo = menu.animate(time);

        top.position.set(0, yRange, zAxisPos);
        bottom.position.set(0, -yRange, zAxisPos);

        left.position.set(-xRange, 0, zAxisPos);
        right.position.set(xRange, 0, zAxisPos);

        background.position.set(0,0,zAxisPosBG);

        resume.setPosition(0, yRange*.6, zAxisPos);
        options.setPosition(0, yRange*.1, zAxisPos);
        back.setPosition(0, -yRange*.4, zAxisPos);

        if(menu.keys.isReleased("pause")) {
            return backTo;
        }
        
        if(menu.willHide)hide();

        return sendTo;
    }
};

#endif

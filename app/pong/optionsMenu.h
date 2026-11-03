#ifndef OPTIONS_MENU
#define OPTIONS_MENU

#include <iostream>

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <ArgonEngine/Addons/BorderedLabel.h>
#include <ArgonEngine/Addons/uilib/ui.h>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "wall.h"
#include "constants.h"
#include "options.h"

struct OptionsMenu : Argon::Node {
    Argon::VirtualResource font = "resource://GNF.ttf";
    Argon::VirtualResource buttonBG = "resource://buttonBG.png";
    Wall outterTop;
    Wall outterBottom;
    Wall outterLeft;
    Wall outterRight;

    Wall innerLeft;
    Wall innerTop;

    Wall background;

    Argon::Addons::GrowButton Back;
    Argon::Addons::GrowButton Controls;
    Argon::Addons::GrowButton Video;
    Argon::Addons::GrowButton Audio;

    Argon::Addons::FillSliderBG Volume;

    Argon::Label optionsMenuType;

    int submenuController;

    Argon::Addons::Menu optmenu;
    Argon::Addons::Menu conmenu;
    Argon::Addons::Menu vidmenu;
    Argon::Addons::Menu audmenu;

    IOInterface& buttons = IOInterface::instance();

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
                 [&](){ submenuController = 1; return nullptr; },
                 Argon::Vector2f(.25,.35),
                 Argon::Vector2f(.275,.45)),
        
        Video(std::vector<std::string>{"select", "leftClick"},
              [&](){ submenuController = 2; return nullptr; },
              Argon::Vector2f(.35,.35),
              Argon::Vector2f(.4,.45)),

        Audio(std::vector<std::string>{"select", "leftClick"},
              [&](){ submenuController = 3; return nullptr; },
              Argon::Vector2f(.35,.35),
              Argon::Vector2f(.4,.45)),

        optmenu(
            std::vector<Argon::Addons::Selectable*>{
                &Back, 
                &Controls, 
                &Video, 
                &Audio
            }
        ),
        
        Volume(),

        audmenu(std::vector<Argon::Addons::Selectable*>{&Volume})
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

        Volume.marginY = 0.5;
        Volume.render("resource://Wall.png", "resource://Wall.png", "resource://Wall.png", font, Argon::kLineLeft);
        Volume.line.color = Argon::kBlackColor;
        Volume.sprite.color = Argon::kRedColor;
        Volume.valueDisplay.color = Argon::kGreenColor;

        Volume.setScale(2, .2, 0);

        float lineWidth = yRange/30.;
        outterTop.dimensions.set((xRange*2.)+lineWidth,lineWidth,1);
        outterBottom.dimensions.set((xRange*2.)+lineWidth,lineWidth,1);
        outterLeft.dimensions.set(lineWidth,(yRange*2.)+lineWidth,1);
        outterRight.dimensions.set(lineWidth,(yRange*2.)+lineWidth,1);

        innerLeft.dimensions.set(lineWidth,(yRange*2.)-lineWidth,1);
        innerTop.dimensions.set((xRange*2.)-lineWidth,lineWidth,1);

        background.dimensions.set(3*(xRange*2)+lineWidth,3*(yRange*2)+lineWidth,1);
        background.color.set(0,0,0,1);

        optionsMenuType.render_str("OPTIONS",font,Argon::kLineCenter);
        optionsMenuType.color.set(1,1,1,1);
        optionsMenuType.scale.set(.75, .5, 1);
        submenuController = 0;
    }

    std::shared_ptr<Argon::Node> doAudMenu(float time) {
        Volume.setPosition(xRange*.75, yRange*.5*0, zAxisPos);
        return audmenu.animate(time);
    }

    std::shared_ptr<Argon::Node> animate(float time) {
        std::shared_ptr<Argon::Node> sendTo = nullptr;

        if(buttons.isReleased("pause")) {
            submenuController = 0;
        }

        switch (submenuController) {
            case 0:
                sendTo = optmenu.animate(time);
                break;
            case 1:
                sendTo = conmenu.animate(time);
                vidmenu.hide();
                audmenu.hide();
                break;
            case 2:
                sendTo = vidmenu.animate(time);
                conmenu.hide();
                audmenu.hide();
                break;
            case 3:
                sendTo = doAudMenu(time);
                conmenu.hide();
                vidmenu.hide();
                break;
        }

        background.position.set(0,0,zAxisPosBG);

        outterTop.position.set(0,yRange,zAxisPos);
        outterBottom.position.set(0,-yRange,zAxisPos);
        outterLeft.position.set(-xRange,0,zAxisPos);
        outterRight.position.set(xRange,0,zAxisPos);

        innerLeft.position.set(-xRange*.7,0,zAxisPos);
        innerTop.position.set(0,yRange*.7,zAxisPos);

        optionsMenuType.position.set(xRange*.1,yRange*.77,zAxisPos);

        Back.setPosition(-xRange*.85, yRange*.85,zAxisPos);

        Controls.setPosition(-xRange*.85, yRange*.55,zAxisPos);
        Video.setPosition(-xRange*.85, yRange*.35,zAxisPos);
        Audio.setPosition(-xRange*.85, yRange*.15,zAxisPos);

        if(Controls.selected) {
            optionsMenuType.render_str("CONTROLS",font,Argon::kLineCenter);
        } else if(Video.selected) {
            optionsMenuType.render_str("VIDEO",font,Argon::kLineCenter);
        } else if(Audio.selected) {
            optionsMenuType.render_str("AUDIO",font,Argon::kLineCenter);
        }

        return sendTo;
    }
};

#endif

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Text.h>
#include <sstream>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/ArgonInit.h>
#include <ArgonEngine/Hardware.h>
#include <ArgonEngine/Addons/BorderedLabel.h>

#include "pong.h"
#include "optionsMenu.h"
#include "ButtonInterface.h"
#include "buttonUtils.h"
#include "menu.h"
#include "quit.h"

#ifndef PONGMENU_H
#define PONGMENU_H

struct PongMenu:public Argon::Node, std::enable_shared_from_this<PongMenu> {
    Argon::VirtualResource font = "resource://GNF.ttf";
    Argon::VirtualResource buttonBG = "resource://buttonBG.png";
    Argon::Label Title;
    GrowButton StartGame;
    GrowButton Options;
    GrowButton Quit;
    Argon::Timer timer;

    Menu menu;

    PongMenu():
        StartGame(std::vector<std::string>{"select", "leftClick"}, 
                  [&](){ return std::make_shared<Pong>(shared_from_this()); },
                  Argon::Vector2f(1, 1),
                  Argon::Vector2f(1.5, 1.5)),

        Options(std::vector<std::string>{"select", "leftClick"}, 
                  [&](){ return std::make_shared<OptionsMenu>(shared_from_this(), 
                                                              constants::zAxisPos/2); },
                  Argon::Vector2f(.75, 1),
                  Argon::Vector2f(.75*1.5, 1.5)),

        Quit(std::vector<std::string>{"select", "leftClick"}, 
                  [&](){ return std::make_shared<QuitGame>(shared_from_this()); },
                  Argon::Vector2f(1, 1),
                  Argon::Vector2f(1.5, 1.5)),

        menu(std::vector<GrowButton*>{&StartGame, &Options, &Quit})
    {
        Argon::Screen::title = "PONG";
        Title.color.set(1,0,1,1);

        StartGame.render("PLAY",font,buttonBG,Argon::kLineCenter, 0.5, 0);
        Options.render("OPTIONS",font,buttonBG,Argon::kLineCenter, 0.5, 0);
        Quit.render("QUIT",font,buttonBG,Argon::kLineCenter, 0.5, 0);

        Title.render_str("PONG",font,Argon::kLineCenter);
        Title.scale.set(2,2,1);
    }

    void hide() {
        Title.position[2] = 0;
        StartGame.setzPosition(0);
        Options.setzPosition(0);
        Quit.setzPosition(0);
        menu.willHide = false;
    }

    std::shared_ptr<Argon::Node>animate(float time) {
        auto sendTo = menu.animate(time);

        Title.position.set(0,7,constants::zAxisPos/2);
        StartGame.setPosition(0,1.75,constants::zAxisPos/2);
        Options.setPosition(0,0,constants::zAxisPos/2); 
        Quit.setPosition(0,-1.75,constants::zAxisPos/2);

        Title.rotation.set_euler_xyz(0, sin(timer.time()) * 0.2, 0);

        Title.color.set(fabs(sin(timer.time())),0,fabs(cos(timer.time())),1);

        if(menu.willHide)hide();

        return sendTo;
    }
};

#endif

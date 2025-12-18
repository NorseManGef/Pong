#include <ArgonEngine/Node.h>
#include <ArgonEngine/Text.h>
#include <sstream>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/ArgonInit.h>
#include <ArgonEngine/Hardware.h>

#include "pong.h"


#ifndef PONGMENU_H
#define PONGMENU_H

struct PongMenu:public Argon::Node {
    Argon::VirtualResource font = "resource://GeosansLight.ttf";
    Argon::Label Title;
    Argon::Label StartGame;
    Argon::Label Options;
    Argon::Label Quit;
    Argon::Input input;
    Argon::Timer timer;
    bool options;

    PongMenu() {
        Argon::Screen::title = "PONG";
        Title.color.set(1,0,1,1);
        StartGame.color.set(1,0,1,1);
        Options.color.set(1,0,1,1);
        Quit.color.set(1,0,1,1);
        Title.render_str("PONG",font,Argon::kLineCenter);
        Title.scale.set(2,2,1);
        StartGame.render_str("START GAME",font,Argon::kLineCenter);
        Quit.render_str("QUIT",font,Argon::kLineCenter);
        Options.render_str("OPTIONS",font,Argon::kLineCenter);
    }

    std::shared_ptr<Argon::Node>animate(float time) {
        Argon::Vector2f mousePos(input[Argon::kInputIDMouseX].value,
                                 input[Argon::kInputIDMouseY].value);

        Argon::Vector3f goalUp(2,2,2);
        Argon::Vector3f goalDown(1,1,1);
        float alpha = .7;

        Title.position.set(0,7,-10);
        StartGame.position.set(0,2,-10);
        Options.position.set(0,0,-10);
        Quit.position.set(0,-2,-10);

        Title.rotation.set_euler_xyz(0, sin(timer.time()) * 0.5, 0);

        Title.color.set(fabs(sin(timer.time())),0,fabs(cos(timer.time())),1);

        if(StartGame.overlaps_screen_coord(mousePos*10)) {
            StartGame.scale = StartGame.scale * alpha + goalUp * (1-alpha);

            if(input[Argon::kInputIDMouseButton1].value) {
                return std::make_shared<Pong>();
            }
        } else {
            StartGame.scale = StartGame.scale * alpha + goalDown * (1-alpha);
        }

        return nullptr;
    }
};

#endif

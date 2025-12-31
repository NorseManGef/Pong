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
    Argon::Sprite StartGame;
    Argon::Sprite Options;
    Argon::Sprite Quit;
    Argon::Input input;
    Argon::Timer timer;
    bool options;

    PongMenu() {
        Argon::Screen::title = "PONG";
        Title.color.set(1,0,1,1);
        StartGame.color.set(1,1,1,1);
        Options.color.set(1,1,1,1);
        Quit.color.set(1,1,1,1);
        Title.render_str("PONG",font,Argon::kLineCenter);
        Title.scale.set(2,2,1);
        StartGame.texture = "resource://Play.png";
        Quit.texture = "resource://Quit.png";
        Options.texture = "resource://Options.png";
    }

    std::shared_ptr<Argon::Node>animate(float time) {
        Argon::Vector2f mousePos(input[Argon::kInputIDMouseX].value,
                                 input[Argon::kInputIDMouseY].value);

        Argon::Vector3f goalUpStart(4,2,2);
        Argon::Vector3f goalDownStart(3,1.5,1);

        Argon::Vector3f goalUpOpts(4,4.0/3,0);
        Argon::Vector3f goalDownOpts(3,1,0);

        Argon::Vector3f goalUpQuit(3,1.5,0);
        Argon::Vector3f goalDownQuit(2,1,0);
        float alpha = .7;

        Title.position.set(0,7,-10);
        StartGame.position.set(0,2,-10);
        Options.position.set(0,0,-10); 
        Quit.position.set(0,-1.75,-10);

        Title.rotation.set_euler_xyz(0, sin(timer.time()) * 0.5, 0);

        Title.color.set(fabs(sin(timer.time())),0,fabs(cos(timer.time())),1);

        if(StartGame.overlaps_screen_coord(mousePos*10)) {
            StartGame.scale = StartGame.scale * alpha + goalUpStart * (1-alpha);

            if(input[Argon::kInputIDMouseButton1].value) {
                return std::make_shared<Pong>();
            }
        } else {
            StartGame.scale = StartGame.scale * alpha + goalDownStart * (1-alpha);
        }
        
        if(Options.overlaps_screen_coord(mousePos*10)) {
            Options.scale = Options.scale * alpha + goalUpOpts * (1-alpha);

            if(input[Argon::kInputIDMouseButton1].value) {

            }
        } else {
            Options.scale = Options.scale * alpha + goalDownOpts * (1-alpha);
        }
        
        if(Quit.overlaps_screen_coord(mousePos*10)) {
            Quit.scale = Quit.scale * alpha + goalUpQuit * (1-alpha);

            if(input[Argon::kInputIDMouseButton1].value) {
                Argon::terminate_engine();
            }
        } else {
            Quit.scale = Quit.scale * alpha + goalDownQuit * (1-alpha);
        } 

        return nullptr;
    }
};

#endif

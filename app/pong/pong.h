#ifndef __PONG__
#define __PONG__

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <ArgonEngine/Addons/uilib/iointerface.h>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "ball.h"
#include "pauseMenu.h"
#include "paddle.h"
#include "constants.h"

struct Pong : Argon::Node, std::enable_shared_from_this<Pong> {
    Ball ball;
    Paddle leftPaddle;
    Paddle rightPaddle;

    Wall topWall;
    Wall bottomWall;
    Wall leftWall;
    Wall rightWall;

    std::shared_ptr<Argon::Node> mainMenu;

    IOInterface& buttons = IOInterface::instance();
    
    Pong(std::shared_ptr<Argon::Node> mainMenu): 
        mainMenu(mainMenu)
    {
        ball.parent = this;
        name="pong";
        srand(time(nullptr));
        leftPaddle.position.set(-10/Argon::Screen::ratio(), 0, constants::zAxisPos);
        rightPaddle.position.set(10/Argon::Screen::ratio(), 0, constants::zAxisPos);

        topWall.dimensions[1] = 1;
        topWall.dimensions[0] = 20/Argon::Screen::ratio();
        topWall.position[1] = constants::yRange;
        topWall.scale.set(1.063,0.5,1);
        topWall.position[0] = 0;
        topWall.position[2] = constants::zAxisPos;

        bottomWall.dimensions[1] = 1;
        bottomWall.dimensions[0] = 20/Argon::Screen::ratio();
        bottomWall.scale.set(1.063,0.5,1);
        bottomWall.position[1] = -constants::yRange;
        bottomWall.position[0] = 0;
        bottomWall.position[2] = constants::zAxisPos;

        leftWall.dimensions[1] = 20;
        leftWall.dimensions[0] = 1;
        leftWall.scale.set(0.5,1.08,1);
        leftWall.position[1] = 0;
        leftWall.position[0] = -constants::xRange/Argon::Screen::ratio();
        leftWall.position[2] = constants::zAxisPos;

        rightWall.dimensions[1] = 20;
        rightWall.dimensions[0] = 1;
        rightWall.scale.set(0.5,1.08,1);
        rightWall.position[1] = 0;
        rightWall.position[0] = constants::xRange/Argon::Screen::ratio();
        rightWall.position[2] = constants::zAxisPos;

        leftPaddle.sprite.texture = "resource://Wall.png";
        rightPaddle.sprite.texture = "resource://Wall.png";

        leftPaddle.scale.set(0.5,1,1);
        rightPaddle.scale.set(0.5,1,1);

    }

    std::shared_ptr<Argon::Node> animate(float time) {
        if(buttons.isReleased("pause")) {
            return std::make_shared<pauseModal>(shared_from_this(), mainMenu);
        }

        rightPaddle.position[0] = 9.5/Argon::Screen::ratio();
        leftPaddle.position[0] = -9.5/Argon::Screen::ratio();

        topWall.dimensions[0] = 20/Argon::Screen::ratio();
        bottomWall.dimensions[0] = 20/Argon::Screen::ratio();

        leftWall.position[0] = -10.5/Argon::Screen::ratio();
        rightWall.position[0] = 10.5/Argon::Screen::ratio();

        rightPaddle.move();
        leftPaddle.move();


        ball.collide(rightPaddle);
        ball.collide(leftPaddle);
        ball.collide(topWall);
        ball.collide(bottomWall);
        if(ball.collide(leftWall)) {
            //TODO scoring
        }
        if(ball.collide(rightWall)) {
            //TODO scoring
        }
        ball.animate(time);
                
        return nullptr;
    }
};

#endif

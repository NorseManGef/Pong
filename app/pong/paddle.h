#ifndef __PADDLE__
#define __PADDLE__

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "object.h"
#include "util.h"
#include "ButtonInterface.h"

struct Paddle : public Object {
    Argon::Sprite sprite;
    Argon::Input input;

    ButtonInterface& buttons = ButtonInterface::instance();

    float accel;

    Paddle() {
        sprite.parent = this;

        velocity[0] = 0;
        velocity[1] = 0;
        velocity[2] = 0;

        friction = 10;

        dimensions.set(1,3,0);

        color = Argon::kWhiteColor;

        sprite.scale.set_all(1);
    }

    void move() {
        if(buttons.isPressed("paddleUp")  && position[1]+dimensions[1]/2 < 10.5) {
            if(velocity[1] < 0) {
                velocity[1] = 0;
            }

            velocity[1] = accelerator(0.5, 0.5, velocity[1]);
            position[1] += velocity[1];
        }
        if(buttons.isPressed("paddleDown") && position[1]-dimensions[1]/2 > -10.5) {
            if(velocity[1]>0) {
                velocity[1] = 0;
            }

            velocity[1] = -accelerator(0.5, 0.5, -velocity[1]);
            position[1] += velocity[1];
        }
    }

std::shared_ptr<Argon::Node> animate(float time) {
        return nullptr;
    }
};

#endif

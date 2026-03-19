#ifndef __BALL__
#define __BALL__

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "object.h"
#include "util.h"
#include "constants.h"

struct Ball : public Object {
    Argon::Sprite sprite; 

    Argon::Vector2f speed;
    const float colorChangeTime = 50;

    bool isRight = true;

    Ball() {
        sprite.parent = this;

        velocity[2] = 0;
        velocity[0] = speed[0] = 5;
        velocity[1] = speed[1] = 3;

        friction = 0;

        dimensions.set(1,1,0);
        position.set(0, 0, constants::zAxisPos);
        sprite.scale.set_all(1);
        sprite.texture = "resource://Ball.png";
    }

    void accelerate() {
        if(isRight) {
            velocity[0] = accelerator(0.2, 50, velocity[0]);
        } else {
            velocity[0] = -accelerator(0.2, 50, -velocity[0]);
        }
    }

    std::shared_ptr<Argon::Node> animate(float time) {
        accelerate();
        position[0]+=velocity[0]*time;
        position[1]+=velocity[1]*time;

        return nullptr;
    }

protected:
    void onCollide(const Object& other, bool l, bool r, bool t, bool b) {
        if(r && !l && velocity[0] > 0) {
            velocity[0] = -velocity[0]/2;
            velocity[1] += other.velocity[1]*(other.friction+friction);
            isRight = false;
        }
        if(l && !r && velocity[0] < 0) {
            velocity[0] = -velocity[0]/2;
            velocity[1] += other.velocity[1]*(other.friction+friction);
            isRight = true;
        }

        if(t && !b && velocity[1] > 0) {
            velocity[1] = -velocity[1]*.90;
        }
        if(b && !t && velocity[1] < 0) {
            velocity[1] = -velocity[1]*.90;
        }
    }
};

#endif

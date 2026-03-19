#ifndef __OBJECT__
#define __OBJECT__

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <memory>
#include <cstdlib>
#include <ctime>

struct Object : Argon::Node {
    Argon::Vector3f velocity;
    float friction;
    Argon::Sprite sprite;

    float top() const {
        return position[1]+dimensions[1]/2;
    }

    float bottom() const {
        return position[1]-dimensions[1]/2;
    }

    float right() const {
        return position[0]+dimensions[0]/2;
    }

    float left() const {
        return position[0]-dimensions[0]/2;
    }

    bool inXRange(float x) const {
        return x <= right() && x >= left();
    } 

    bool inYRange(float y) const {
        return y <= top() && y >= bottom();
    }

    bool collide(const Object &other) {
        bool l = false;
        bool r = false;
        bool t = false;
        bool b = false;

        if(other.inXRange(right()) && (other.inYRange(top()) || other.inYRange(bottom()))) {
            r = true;
        }
        if(other.inXRange(left()) && (other.inYRange(top()) || other.inYRange(bottom()))) {
            l = true;
        }

        if(other.inYRange(top()) && (other.inXRange(right()) || other.inXRange(left()))) {
            t = true;
        }
        if(other.inYRange(bottom()) && (other.inXRange(right()) || other.inXRange(left()))) {
            b = true;
        }

        if(!l && !r && !t && !b) {
            return false;
        } else {
            onCollide(other, l, r, t, b);
            return true;
        }
    }

protected:
    virtual void onCollide(const Object& source, bool l, bool r, bool t, bool b) {

    }
};

#endif

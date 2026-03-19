#ifndef WALL
#define WALL

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "object.h"

struct Wall : public Object {
    Argon::Sprite sprite;

    Wall() {
        sprite.parent = this;
        sprite.texture = "resource://Wall.png";
    }
};

#endif

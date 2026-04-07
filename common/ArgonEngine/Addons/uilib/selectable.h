#ifndef SELECTABLE
#define SELECTABLE

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>

namespace Argon {
namespace Addons {

struct Selectable {
    bool selected;
    bool willHide;

    Selectable(): selected(false), willHide(true) {}

    virtual void setPosition(float x, float y, float z) {
        setxPosition(x);
        setyPosition(y);
        setzPosition(z);
    }

    virtual void setxPosition(float x) = 0;

    virtual void setyPosition(float y) = 0;

    virtual void setzPosition(float z) = 0;

    virtual void setScale(float x, float y, float z) {
        setxScale(x);
        setyScale(y);
        setzScale(z);
    }

    virtual void setxScale(float x) = 0;

    virtual void setyScale(float y) = 0;

    virtual void setzScale(float z) = 0;

    virtual float xPosition() = 0;

    virtual float yPosition() = 0;

    virtual float zPosition() = 0;

    virtual bool overlaps_screen_coord(Vector2f coord) = 0;

    virtual std::shared_ptr<Argon::Node> animate(float time) = 0;
};

}
}
#endif

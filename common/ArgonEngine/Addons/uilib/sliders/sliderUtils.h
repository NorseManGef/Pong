#ifndef SLIDER_UTILS
#define SLIDER_UTILS

#include <ArgonEngine/Sprite.h>
namespace Argon {
namespace Addons {

struct SliderSprite : public Sprite {
    SliderSprite(): Sprite() {};

    float value;

    bool selected;
};

enum Axis {
    x = 0,
    y = 1,
};

}
}

#endif

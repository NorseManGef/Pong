#include "sliderUtils.h"

using namespace Argon::Addons;

Slider::Slider(int numSprites, float minVal, float maxVal, Axis axis): 
    numSprites(numSprites), 
    minVal(minVal), 
    maxVal(maxVal), 
    sprites(new SliderSprite[numSprites])
{}

Slider::~Slider() { delete[] sprites; delete background; }

FillSlider::FillSlider(float minVal, float maxVal, Axis axis): Slider(1, minVal, maxVal, axis) {};

void Slider::setVal(float val, SliderSprite& sprite) {
    sprite.value = val;

    sprite.position[axis] = (val/maxVal)*
                            (sprites[0].position[axis]+sprites[0].bounds.size[axis]) +
                            (sprites[0].position[axis]-sprites[0].bounds.size[axis]);

    if(val == 0) {
        sprite.position[axis] = sprites[0].position[axis]-sprites[0].bounds.size[axis];
    }
}

void Slider::animate(const Vector2f &mousePos, const bool mouseMoved) {
    for(int i = 0; i < numSprites; ++i) {
        Vector2f cmp = mousePos*(std::abs(sprites[i].position[2])/2);
        if(sprites[i].overlaps_screen_coord(cmp)) {
            if(keys.isPressed("leftClick")) {
                sprites[i].selected = true;
            }
        } 

        if(sprites[i].selected && keys.isPressed("leftClick")) {
            if(isQuantized) {
                int value;
                if(cmp[axis]>sprites[i].position[axis]+sprites[i].dimensions[axis]) {
                    value = maxVal;
                } else if(cmp[axis]<sprites[i].position[axis]+sprites[i].dimensions[axis]) {
                    value = minVal;
                } else {
                    value = cmp[axis]/(sprites[i].position[axis]+sprites[i].dimensions[axis]);
                }
                setVal(value, sprites[i]);
            } else {
                float value;
                if(cmp[axis]>sprites[i].position[axis]+sprites[i].dimensions[axis]) {
                    value = maxVal;
                } else if(cmp[axis]<sprites[i].position[axis]+sprites[i].dimensions[axis]) {
                    value = minVal;
                } else {
                    value = cmp[axis]/(sprites[i].position[axis]+sprites[i].dimensions[axis]);
                }
                setVal(value, sprites[i]);
            }
        } 

        if(!sprites[i].overlaps_screen_coord(cmp) 
            && !keys.isPressed("leftClick") 
            && sprites[i].selected) {

            sprites[i].selected = false;
        }
    }
}

bool Slider::keyboardable() {
    return (numSprites == 1);
}

void Slider::setPosition(float x, float y, float z) {
    setxPosition(x);
    setyPosition(y);
    setzPosition(z);
}

void Slider::setxPosition(float x) {
    line.position[1] = x;

    if(numSprites > 0) { 
        for(int i = 0; i < numSprites; ++i) {
            float offset = sprites[i].position[0] - sprites[0].position[0];

            sprites[i].position[0] = x - offset;
        }
        valueDisplay.position[0] = x + (valueDisplay.bounds.size[0]/2)
                                     + (sprites[0].bounds.size[0]/2); 

    } else {
        valueDisplay.position[0] = x;
    }
    if(background!=nullptr) {
        background->position[1] = y + (valueDisplay.bounds.size[0]/2);
    }
}

void Slider::setyPosition(float y) {
    line.position[1] = y;

    if(numSprites > 0) {

        for(int i = 0; i < numSprites; ++i) {
            float offset = sprites[i].position[1] - sprites[0].position[1];

            sprites[i].position[1] = y - offset;
        }

        valueDisplay.position[1] = y + (valueDisplay.bounds.size[1]/2)
                                     + (sprites[0].bounds.size[1]/2);
    } else {
        valueDisplay.position[1] = y;
    }
    if(background!=nullptr) {
        background->position[1] = y + (valueDisplay.bounds.size[0]/2);
    }
}

void Slider::setzPosition(float z) {
    if(numSprites > 0) {
        float _z = background!=nullptr ? z : z-zOffset;

        line.position[2] = _z;
        _z+=zOffset;

        for(int i = 0; i < numSprites; ++i) {
            _z+=zOffset;
            sprites[i].position[2] = _z;
        }

        if(background!=nullptr) {
            background->position[2] = z;
        }
    }
}

void Slider::setDimensions(float x, float y, float z) {
    setxDimensions(x);
    setyDimensions(y);
    setzDimensions(z);
}

void Slider::setxDimensions(float x) {
    for(int i = 0; i < numSprites; ++i) {
        sprites[i].dimensions[0] = x;
    }
    valueDisplay.dimensions[0] = x;
}

void Slider::setyDimensions(float y) {
    for(int i = 0; i < numSprites; ++i) {
        sprites[i].dimensions[1] = y;
    }
    valueDisplay.dimensions[1] = y;
}

void Slider::setzDimensions(float z) {
    for(int i = 0; i < numSprites; ++i) {
        sprites[i].dimensions[2] = z;
    }
    valueDisplay.dimensions[2] = z;
}

void Slider::setScale(float x, float y, float z) {

}

void Slider::setxScale(float x) {

}

void Slider::setyScale(float y) {

}

void Slider::setzScale(float z) {

}

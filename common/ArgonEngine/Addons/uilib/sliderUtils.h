#ifndef SLIDERUTILS
#define SLIDERUTILS

#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Text.h>
#include "iointerface.h"

namespace Argon {
namespace Addons {

enum Axis {
    x = 0,
    y = 1
};

struct SliderSprite : public Sprite {
    SliderSprite(): Sprite() {};

    float value;

    bool selected;
};

struct Slider {
    const int numSprites;
    SliderSprite* sprites;

    Sprite line;

    Sprite* background;

    enum Axis axis;

    Label valueDisplay;

    float minBound;

    float maxBound;
    
    float minVal;

    float maxVal;
    
    float marginX;
    
    float marginY;

    bool isQuantized;

    IOInterface keys = IOInterface::instance();

    Slider(int numSprites, float minVal, float maxVal, Axis axis);

    Slider() = delete;

    ~Slider();

    virtual void setPosition(float x, float y, float z);

    virtual void setxPosition(float x);

    virtual void setyPosition(float y);

    virtual void setzPosition(float z);

    virtual void setDimensions(float x, float y, float z);

    virtual void setxDimensions(float x);

    virtual void setyDimensions(float y);

    virtual void setzDimensions(float z);

    virtual void setScale(float x, float y, float z);

    virtual void setxScale(float x);

    virtual void setyScale(float y);

    virtual void setzScale(float z);

    virtual bool keyboardable();

    virtual void setVal(float val, SliderSprite& sprite);

    virtual void animate(const Vector2f &mousePos, const bool mouseMoved);

private:
    float zOffset = 1/100;
};

struct FillSlider : public Slider {
    FillSlider(float minVal, float maxVal, Axis = x);
};

struct FillSliderBG : public FillSlider {

};

struct PointSlider : public Slider {

};

struct PointSliderBG : public PointSlider {

};

struct DualPointSlider : public Slider {

};

struct DualPointSliderBG : public DualPointSlider {

};

}
}

#endif

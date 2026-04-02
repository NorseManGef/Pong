#ifndef SLIDERUTILS
#define SLIDERUTILS

#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Text.h>
#include "iointerface.h"
#include "selectable.h"

namespace Argon {
namespace Addons {

struct SliderSprite : public Sprite {
    SliderSprite(): Sprite() {};

    float value;

    bool selected;
};

struct Slider : public Selectable {
    Sprite line;

    Label valueDisplay;

    float minBound;

    float maxBound;
    
    float minVal;

    float maxVal;
    
    Slider();

    Slider(float minVal, float maxVal);

    virtual void render(VirtualResource lineTexture, 
                   VirtualResource spriteTexture,
                   VirtualResource labelFont) = 0;

    virtual void updateValueDisplay(float value, VirtualResource labelFont) = 0;

    virtual std::shared_ptr<Argon::Node> animate(float time) = 0;

private:
    float zOffset = 1/100;
};

struct FillSlider : public Slider {
    SliderSprite sprite;

    FillSlider();

    FillSlider(float minVal, float maxVal);

    void setPosition(float x, float y, float z);

    void setxPosition(float x);

    void setyPosition(float y);

    void setzPosition(float z);

    void setxScale(float x);

    void setyScale(float y);

    void setzScale(float z);

    bool overlaps_screen_coord(Vector2f coord);

    void render(VirtualResource lineTexture,
                VirtualResource spriteTexture,
                VirtualResource labelFont);

    std::shared_ptr<Argon::Node> animate(float time);

    void updateValueDisplay(float value, VirtualResource labelFont);
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

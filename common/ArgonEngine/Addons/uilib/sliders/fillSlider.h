#ifndef FILLSLIDER
#define FILLSLIDER

#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Text.h>
#include "../iointerface.h"
#include "../selectable.h"
#include "sliderUtils.h"
#include "slider.h"

namespace Argon {
namespace Addons {

struct FillSlider : public Slider {
    SliderSprite sprite;

    FillSlider();

    FillSlider(float minVal, float maxVal);

    FillSlider(Axis axis, float minVal, float maxVal);

    void setxPosition(float x);

    void setyPosition(float y);

    void setzPosition(float z);

    void setxScale(float x);

    void setyScale(float y);

    void setzScale(float z);

    void setxDimensions(float x);

    void setyDimensions(float y);

    void setzDimensions(float z);

    void setSpriteScale(float x, float y, float z);

    void setSpritexScale(float x) {
        sprite.scale[0] = x;
    }

    void setSpriteyScale(float y) {
        sprite.scale[1] = y;
    }

    void setSpritezScale(float z) {
        sprite.scale[2] = z;
    }

    void setLineScale(float x, float y, float z);

    void setLinexScale(float x);

    void setLineyScale(float y);

    void setLinezScale(float z);

    void setSpriteDimensions(float x, float y, float z);

    void setSpritexDimensions(float x) {
        sprite.dimensions[0] = x;
    }

    void setSpriteyDimensions(float y) {
        sprite.dimensions[1] = y;
    }

    void setSpritezDimensions(float z) {
        sprite.dimensions[2] = z;
    }

    void setLineDimensions(float x, float y, float z);

    void setLinexDimensions(float x);

    void setLineyDimensions(float y);

    void setLinezDimensions(float z);

    void setValueDisplayDimensions(float x, float y, float z);

    void setValueDisplayxDimensions(float x) {
        valueDisplay.dimensions[0] = x;
    }

    void setValueDisplayyDimensions(float y) {
        valueDisplay.dimensions[1] = y;
    }

    void setValueDisplayzDimensions(float z) {
        valueDisplay.dimensions[2] = z;
    }

    virtual bool overlaps_screen_coord(Vector2f coord) {
        return line.overlaps_screen_coord(coord);
    }

    virtual void render(VirtualResource lineTexture,
                        VirtualResource spriteTexture);

    virtual void render(VirtualResource lineTexture,
                        VirtualResource spriteTexture,
                        VirtualResource labelFont,
                        LineStyle style = kLineCenter);

    std::shared_ptr<Argon::Node> animate(float time);

    float getValue() {
        return sprite.value;
    }

    void setValue(float value) {
        sprite.value = value;
    }

protected:
    void calcSpritePos();
};

struct FillSliderBG : public FillSlider {
    Sprite background;

    float marginX;

    float marginY;

    FillSliderBG();

    FillSliderBG(float minVal, float maxVal);

    FillSliderBG(Axis axis, float minVal, float maxVal);

    void setxPosition(float x);

    void setyPosition(float y);

    void setzPosition(float z);

    void setxScale(float x);

    void setyScale(float y);

    void setzScale(float z);

    void setxDimensions(float x);

    void setyDimensions(float y);

    void setzDimensions(float z);

    void setBackgroundScale(float x, float y, float z);

    void setBackgroundxScale(float x) {
        background.scale[0] = x+marginX;
    }

    void setBackgroundyScale(float y) {
        background.scale[1] = y+marginY;
    }

    void setBackgroundzScale(float z) {
        background.scale[2] = z;
    }

    void setBackgroundDimensions(float x, float y, float z) {
        setBackgroundxDimensions(x);
        setBackgroundyDimensions(y);
        setBackgroundzDimensions(z);
    }

    void setBackgroundxDimensions(float x) {
        background.dimensions[0] = x;
    }

    void setBackgroundyDimensions(float y) {
        background.dimensions[1] = y;
    }

    void setBackgroundzDimensions(float z) {
        background.dimensions[2] = z;
    }
    
    bool overlaps_screen_coord(Vector2f coord) {
        return line.overlaps_screen_coord(coord);
    }

    void render(VirtualResource lineTexture,
                VirtualResource spriteTexture,
                VirtualResource bgTexture);

    void render(VirtualResource lineTexture,
                VirtualResource spriteTexture,
                VirtualResource bgTexture,
                VirtualResource labelFont,
                LineStyle labelStyle);
};
}
}

#endif

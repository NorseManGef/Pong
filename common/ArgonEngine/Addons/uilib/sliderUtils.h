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

enum Axis {
    x = 0,
    y = 1,
};

struct Slider : public Selectable {
    IOInterface keys = IOInterface::instance();

    Sprite line;

    Label valueDisplay;

    LineStyle lineStyle;

    VirtualResource valueDisplayFont;

    float minBound;

    float maxBound;
    
    float minVal;

    float maxVal;

    int displayPrecision;

    int kbnum;

    std::string inckey;

    std::string deckey;

    bool quantized;

    bool pressed;

    bool willHide;

    bool keyboardable;

    bool mouseable;

    Axis axis;
    
    Slider();

    Slider(Axis axis);

    Slider(float minVal, float maxVal);

    Slider(Axis axis, float minVal, float maxVal);

    virtual void setQuantized(bool a) {
        quantized = a;
    }

    virtual float xPosition() {
        return line.position[0];
    }

    virtual float yPosition() {
        return line.position[1];
    }
    
    virtual float zPosition() {
        return line.position[2];
    }

    virtual void setPrecision(int a) {
        displayPrecision = a;
    }

    virtual void render(VirtualResource lineTexture, 
                   VirtualResource spriteTexture,
                   VirtualResource labelFont,
                   LineStyle labelStyle = kLineCenter) = 0;

    virtual void updateValueDisplay(float value, VirtualResource labelFont);

    virtual std::shared_ptr<Argon::Node> animate(float time) = 0;

    virtual void setSpriteScale(float x, float y, float z) = 0;

    virtual void setSpritexScale(float x) = 0;

    virtual void setSpriteyScale(float y) = 0;

    virtual void setSpritezScale(float z) = 0;
    
    virtual void setLineScale(float x, float y, float z) = 0;

    virtual void setLinexScale(float x) = 0;

    virtual void setLineyScale(float y) = 0;

    virtual void setLinezScale(float z) = 0;

    virtual float getValue() = 0;

    virtual void setValue(float value) = 0;

    virtual void hide() {
        setzPosition(0);
    };

    virtual void setValueDisplayPosition(float x, float y, float z);

    virtual void setValueDisplayxPosition(float x);

    virtual void setValueDisplayyPosition(float y);
    
    virtual void setValueDisplayzPosition(float z);

    float zOffset = .001;

protected:
    virtual void setBounds();

    virtual float calculateValue();

    Vector3f vdp;
};

struct FillSlider : public Slider {
    SliderSprite sprite;

    FillSlider();

    FillSlider(float minVal, float maxVal);

    virtual void setxPosition(float x);

    virtual void setyPosition(float y);

    virtual void setzPosition(float z);

    virtual void setxScale(float x);

    virtual void setyScale(float y);

    virtual void setzScale(float z);

    void setSpriteScale(float x, float y, float z);

    void setSpritexScale(float x);

    void setSpriteyScale(float y);

    void setSpritezScale(float z);

    void setLineScale(float x, float y, float z);

    void setLinexScale(float x);

    void setLineyScale(float y);

    void setLinezScale(float z);

    virtual bool overlaps_screen_coord(Vector2f coord);

    void render(VirtualResource lineTexture,
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

private:
    void calcSpritePos();
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

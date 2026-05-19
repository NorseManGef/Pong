#ifndef SLIDER
#define SLIDER

#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Text.h>
#include "../iointerface.h"
#include "../selectable.h"
#include "ArgonEngine/Node.h"
#include "sliderUtils.h"

namespace Argon {
namespace Addons {

struct Slider : public Selectable {
    IOInterface keys = IOInterface::instance();

    Sprite line;

    Label valueDisplay;

    LineStyle lineStyle;

    VirtualResource valueDisplayFont;

    Vector2f vdScaleOffset;

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

    bool displayValues;

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

    virtual void setSpriteDimensions(float x, float y, float z) = 0;

    virtual void setSpritexDimensions(float x) = 0;

    virtual void setSpriteyDimensions(float y) = 0;

    virtual void setSpritezDimensions(float z) = 0;

    virtual void setLineDimensions(float x, float y, float z) = 0;

    virtual void setLinexDimensions(float x) = 0;

    virtual void setLineyDimensions(float y) = 0;

    virtual void setLinezDimensions(float z) = 0;

    virtual float getValue() = 0;

    virtual void setValue(float value) = 0;

    virtual void hide() {
        setzPosition(0);
    };

    virtual void setValueDisplayPosition(float x, float y, float z);

    virtual void setValueDisplayxPosition(float x) {
        valueDisplay.position[0] = x;
    }

    virtual void setValueDisplayyPosition(float y) {
        valueDisplay.position[1] = y;
    }
    
    virtual void setValueDisplayzPosition(float z) {
        valueDisplay.position[2] = z;
    }

    virtual void setValueDisplayScale(float x, float y, float z);

    virtual void setValueDisplayxScale(float x) {
        valueDisplay.position[0] += vdScaleOffset[0];
        valueDisplay.scale[0] = x;
    }

    virtual void setValueDisplayyScale(float y) {
        valueDisplay.position[1] += vdScaleOffset[1];
        valueDisplay.scale[1] = y;
    }

    virtual void setValueDisplayzScale(float z) {
        valueDisplay.scale[2] = z;
    }

    virtual Vector2f vdOnScreenPos() {
        Vector2f vec;
        vec[0] = valueDisplay.position[0]-vdScaleOffset[0]/2;
        vec[1] = valueDisplay.position[1]-vdScaleOffset[1]/2;
        return vec;
    }

    virtual Vector2f vdOnScreenBounds() {
        Vector2f vec;
        vec[0] = valueDisplay.bounds.size[0]*valueDisplay.scale[0];
        vec[1] = valueDisplay.bounds.size[1]*valueDisplay.scale[1];
        return vec;
    }

    float zOffset = .001;

protected:
    virtual void setBounds();

    virtual float calculateValue();

    Vector3f vdp;
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

#include "fillSlider.h"

using namespace Argon::Addons;

FillSlider::FillSlider(): Slider() {
    setSpriteScale(5,.5,.5);
    setLineScale(5,.5,.5);
    setValueDisplayScale(.5, .5, .5);

    setValueDisplayPosition(
        (line.bounds.size[0]*line.scale[0]/3)+(valueDisplay.bounds.size[0]),
        0,
        0
    );

    sprite.value = maxVal > minVal ? maxVal : minVal;
}

FillSlider::FillSlider(float minVal, float maxVal): Slider(x, minVal, maxVal) {
    setSpriteScale(5,.5,.5);
    setLineScale(5,.5,.5);
    setValueDisplayScale(.5, .5, .5);

    setValueDisplayPosition(
        (line.bounds.size[0]*line.scale[0]/3)+(valueDisplay.bounds.size[0]),
        0,
        0
    );

    sprite.value = maxVal > minVal ? maxVal : minVal;
}

FillSlider::FillSlider(Axis axis, float minVal, float maxVal): 
    Slider(axis, minVal, maxVal) {
    setValueDisplayScale(.5, .5, .5);
    if(axis == x) {
        setSpriteScale(5,.5,.5);
        setLineScale(5,.5,.5);

        setValueDisplayPosition(
            (line.bounds.size[0]*line.scale[0]/3)+(valueDisplay.bounds.size[0]),
            0,
            0
        );
    } else {
        setSpriteScale(.5,5,.5);
        setLineScale(.5,5,.5);

        setValueDisplayPosition(
            0,
            (line.bounds.size[1]*line.scale[1]/3)+(valueDisplay.bounds.size[1]),
            0
        );
    }

    sprite.value = maxVal > minVal ? maxVal : minVal;
}

FillSliderBG::FillSliderBG(): 
    FillSlider(),
    marginX(.5),
    marginY(.5)
{
    setBackgroundScale(5+marginX*2,.5+marginY*2,.5);
}

FillSliderBG::FillSliderBG(Axis axis, float minVal, float maxVal):
    FillSlider(axis, minVal, maxVal),
    marginX(.5),
    marginY(.5)
{
    setBackgroundScale(5+marginX*2, .5+marginY*2, .5);
}

void FillSlider::setxPosition(float x) {
    sprite.position[0] = x;
    valueDisplay.position[0] = x + (valueDisplay.position[0]-line.position[0]);
    line.position[0] = x;
}

void FillSliderBG::setxPosition(float x) {
    FillSlider::setxPosition(x);
    if(valueDisplay.position[0] >= line.position[0]+line.bounds.size[0]) {
        background.position[0] = line.position[0]+valueDisplay.bounds.size[0]*valueDisplay.scale[0]/2;
    } else if(valueDisplay.position[0] <= line.position[0]-line.bounds.size[0]) {
        background.position[0] = line.position[0]-valueDisplay.position[0]+marginX/4;
    } else {
        background.position[0] = line.position[0];
    }
}

void FillSlider::setyPosition(float y) {
    sprite.position[1] = y;
    valueDisplay.position[1] = y + (valueDisplay.position[1]-line.position[1]);
    line.position[1] = y;
}

void FillSliderBG::setyPosition(float y) {
    FillSlider::setyPosition(y);
    if(valueDisplay.position[1]+vdScaleOffset[1] >= line.position[1]+line.bounds.size[1]) {
        background.position[1] = line.position[1]+valueDisplay.bounds.size[1]/4;
    } else if(valueDisplay.position[1]+vdScaleOffset[1] <= line.position[1]-line.bounds.size[1]) {
        background.position[1] = line.position[1]-valueDisplay.bounds.size[1]/4;
    } else {
        background.position[1] = line.position[1];
    }
}

void FillSlider::setzPosition(float z) {
    line.position[2] = z;
    sprite.position[2] = z+zOffset;
    valueDisplay.position[2] = z+zOffset;
}

void FillSliderBG::setzPosition(float z) {
    background.position[2] = z;
    line.position[2] = z+zOffset;
    sprite.position[2] = z+(2*zOffset);
    valueDisplay.position[2] = z+(2*zOffset);
}

void FillSlider::setxScale(float x) {
    float scaleOffset = line.scale[0] - sprite.scale[0];
    float labelScaleOffset = valueDisplay.scale[0]/line.scale[0];

    setLinexScale(x);
    setSpritexScale(x - scaleOffset);
    setValueDisplayxScale(x*labelScaleOffset);
    setValueDisplayxPosition((line.bounds.size[0]*line.scale[0]*.37) +
                            (valueDisplay.bounds.size[0]*valueDisplay.scale[0]));
}

void FillSliderBG::setxScale(float x) {
    FillSlider::setxScale(x);
    setBackgroundxScale(x);
}

void FillSlider::setyScale(float y) {
    float scaleOffset = line.scale[1] - sprite.scale[1];
    vdScaleOffset[1] = (valueDisplay.scale[1] - y)*valueDisplay.scale[1]*.9;
    
    setLineyScale(y);
    setSpriteyScale(y - scaleOffset);
    setValueDisplayyScale(y);
}

void FillSliderBG::setyScale(float y) {
    FillSlider::setyScale(y);
    setBackgroundyScale(y);
}

void FillSlider::setzScale(float z) {
    setLinezScale(z);
    setSpritezScale(z);
    valueDisplay.scale[2] = z;
}

void FillSliderBG::setzScale(float z) {
    FillSlider::setzScale(z);
    setBackgroundzScale(z);
}

void FillSlider::setxDimensions(float x) {
    setLinexDimensions(x);
    setSpritexDimensions(x);
    setValueDisplayxDimensions(x);
}

void FillSliderBG::setxDimensions(float x) {
    FillSlider::setxDimensions(x);
    setBackgroundxDimensions(x);
}

void FillSlider::setyDimensions(float y) {
    setLineyDimensions(y);
    setSpriteyDimensions(y);
    setValueDisplayyDimensions(y);
}

void FillSliderBG::setyDimensions(float y) {
    FillSlider::setyDimensions(y);
    setBackgroundyDimensions(y);
}

void FillSlider::setzDimensions(float z) {
    setLinezDimensions(z);
    setSpritezDimensions(z);
    setValueDisplayzDimensions(z);
}

void FillSliderBG::setzDimensions(float z) {
    FillSlider::setzDimensions(z);
    setBackgroundzDimensions(z);
}

void FillSlider::setSpriteScale(float x, float y, float z) {
    setSpritexScale(x);
    setSpriteyScale(y);
    setSpritezScale(z);
}

void FillSlider::setLineScale(float x, float y, float z) {
    setLinexScale(x);
    setLineyScale(y);
    setLinezScale(z);
}

void FillSlider::setLinexScale(float x) {
    line.scale[0] = x;
    setBounds();
}

void FillSlider::setLineyScale(float y) {
    line.scale[1] = y;
    setBounds();
}

void FillSlider::setLinezScale(float z) {
    line.scale[2] = z;
    setBounds();
}

void FillSliderBG::setBackgroundScale(float x, float  y, float z) {
    setBackgroundxScale(x);
    setBackgroundyScale(y);
    setBackgroundzScale(z);
}

void FillSlider::setSpriteDimensions(float x, float y, float z) {
    setSpritexDimensions(x);
    setSpriteyDimensions(y);
    setSpritezDimensions(z);
}

void FillSlider::setLineDimensions(float x, float  y, float z) {
    setLinexDimensions(x);
    setLineyDimensions(y);
    setLinezDimensions(z);
}

void FillSlider::setLinexDimensions(float x) {
    line.dimensions[0] = x;
    setBounds();
}

void FillSlider::setLineyDimensions(float y) {
    line.dimensions[1] = y;
    setBounds();
}

void FillSlider::setLinezDimensions(float z) {
    line.dimensions[2] = z;
    setBounds();
}

void FillSlider::setValueDisplayDimensions(float x, float y, float z) {
    setValueDisplayxDimensions(x);
    setValueDisplayyDimensions(y);
    setValueDisplayzDimensions(z);
}

std::shared_ptr<Argon::Node> FillSlider::animate(float time) {
    setBounds();

    if(mouseable) {
        if(selected) {
            pressed = keys.isPressed("leftClick");
        } else {
            if(!keys.isPressed("leftClick")) {
                pressed = false;
            }
        }
        
        if(pressed) {
            sprite.value = calculateValue();
        }
    }

    if(keyboardable && selected) {
        if(keys.isReleased(inckey) && sprite.value != maxVal) {
            sprite.value += kbnum;
        }
        if(keys.isReleased(deckey) && sprite.value != minVal) {
            sprite.value -= kbnum;
        }
    }

    if(quantized) {
        sprite.value = round(sprite.value);
    }

    calcSpritePos();
    
    if(displayValues) {
        updateValueDisplay(sprite.value, valueDisplayFont);
    }

    return nullptr;
}

void FillSlider::calcSpritePos() {
    if(line.position[axis] == 0) {
        float minPos = 2*minBound/Argon::Screen::ratio();
        sprite.position[axis] = (((sprite.value-minVal)/(maxVal-minVal)))*(-minPos)+minPos;
        sprite.scale[axis] = ((sprite.value-minVal)/(maxVal-minVal))*line.scale[axis];
    } else {
        float minPos = 2*minBound/Argon::Screen::ratio();
        sprite.position[axis] = (((sprite.value-minVal)/(maxVal-minVal))*(line.position[axis]))*(1-(minPos/line.position[axis]))+minPos;
        sprite.scale[axis] = ((sprite.value-minVal)/(maxVal-minVal))*line.scale[axis];
    }
}

void FillSlider::render(VirtualResource lineTexture,
                        VirtualResource spriteTexture) {
    line.texture = lineTexture;
    spriteTexture = spriteTexture;
    displayValues = false;
    valueDisplay.scale.set_all(0);
    valueDisplay.position = line.position;
}

void FillSlider::render(VirtualResource lineTexture,
                        VirtualResource spriteTexture,
                        VirtualResource labelFont,
                        LineStyle labelStyle) {
    line.texture = lineTexture;
    sprite.texture = spriteTexture;
    valueDisplayFont = labelFont;
    lineStyle = labelStyle;
    updateValueDisplay(sprite.value, labelFont);
    setBounds();
}

void FillSliderBG::render(VirtualResource lineTexture,
                          VirtualResource spriteTexture,
                          VirtualResource bgTexture) {
    line.texture = lineTexture;
    sprite.texture = spriteTexture;
    background.texture = bgTexture;
    displayValues = false;
    valueDisplay.scale.set_all(0);
    valueDisplay.position = line.position;
}

void FillSliderBG::render(VirtualResource lineTexture,
                          VirtualResource spriteTexture,
                          VirtualResource bgTexture,
                          VirtualResource labelFont,
                          LineStyle labelStyle) {
    line.texture = lineTexture;
    sprite.texture = spriteTexture;
    background.texture = bgTexture;
    valueDisplayFont = labelFont;
    lineStyle = labelStyle;
    updateValueDisplay(sprite.value, labelFont);
    setBounds();
}

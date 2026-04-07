#include "sliderUtils.h"

using namespace Argon::Addons;

Slider::Slider(Axis axis, float minVal, float maxVal): 
    minVal(minVal), 
    maxVal(maxVal), 
    axis(axis), 
    displayPrecision(6), 
    quantized(true),
    mouseable(true),
    keyboardable(true),
    kbnum(1)
{
    if(axis == x) {
        inckey = "right";
        deckey = "left";
    } else {
        inckey = "up";
        deckey = "down";
    }
}

Slider::Slider(float minVal, float maxVal): 
    minVal(minVal), 
    maxVal(maxVal), 
    displayPrecision(6), 
    quantized(true),
    mouseable(true),
    keyboardable(true),
    kbnum(1),
    inckey("right"),
    deckey("left")
{}

Slider::Slider(Axis axis): 
    minVal(0), 
    maxVal(100), 
    axis(axis), 
    displayPrecision(6), 
    quantized(true),
    mouseable(true),
    keyboardable(true),
    kbnum(1)
{
    if(axis == x) {
        inckey = "right";
        deckey = "left";
    } else {
        inckey = "up";
        deckey = "down";
    }
}

Slider::Slider(): 
    minVal(0), 
    maxVal(100), 
    axis(x), 
    displayPrecision(6),
    quantized(true),
    mouseable(true),
    keyboardable(true),
    kbnum(1),
    inckey("right"),
    deckey("left")
{}

FillSlider::FillSlider(): Slider() {
    setSpriteScale(5,.5,.5);
    setLineScale(5,.5,.5);

    sprite.value = maxVal;
}

FillSlider::FillSlider(float minVal, float maxVal): Slider(x, minVal, maxVal) {
    setSpriteScale(5,.5,.5);
    setLineScale(5,.5,.5);

    sprite.value = maxVal;
}

void FillSlider::setxPosition(float x) {
    sprite.position[0] = x;
    valueDisplay.position[0] = x + (valueDisplay.position[0]-line.position[0]);
    line.position[0] = x;
}

void FillSlider::setyPosition(float y) {
    sprite.position[1] = y;
    valueDisplay.position[1] = y + (valueDisplay.position[1]-line.position[1]);
    line.position[1] = y;
}

void FillSlider::setzPosition(float z) {
    line.position[2] = z;
    sprite.position[2] = z+zOffset;
    valueDisplay.position[2] = z+zOffset;
}

void FillSlider::setxScale(float x) {
    float scaleOffset = line.scale[0] - sprite.scale[0];

    setLinexScale(x);
    setSpritexScale(x - scaleOffset);
    valueDisplay.scale[0] = x;
}

void FillSlider::setyScale(float y) {
    float scaleOffset = line.scale[1] - sprite.scale[1];
    
    setLineyScale(y);
    setSpriteyScale(y - scaleOffset);
    valueDisplay.scale[1] = y;
}

void FillSlider::setzScale(float z) {
    setLinezScale(z);
    setSpritezScale(z);
    valueDisplay.scale[2] = z;
}

void FillSlider::setSpriteScale(float x, float y, float z) {
    setSpritexScale(x);
    setSpriteyScale(y);
    setSpritezScale(z);
}

void FillSlider::setSpritexScale(float x) {
    sprite.scale[0] = x;
}

void FillSlider::setSpriteyScale(float y) {
    sprite.scale[1] = y;
}

void FillSlider::setSpritezScale(float z) {
    sprite.scale[2] = z;
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

void Slider::setValueDisplayPosition(float x, float y, float z) {
    setValueDisplayxPosition(x);
    setValueDisplayyPosition(y);
    setValueDisplayzPosition(z);
}

void Slider::setValueDisplayxPosition(float x) {
    valueDisplay.position[0] = x;
}

void Slider::setValueDisplayyPosition(float y) {
    valueDisplay.position[1] = y;
}

void Slider::setValueDisplayzPosition(float z) {
    valueDisplay.position[2] = z;
}

bool FillSlider::overlaps_screen_coord(Vector2f coord) {
    return line.overlaps_screen_coord(coord);
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
        if(keys.isReleased(inckey)) {
            sprite.value += kbnum;
        }
        if(keys.isReleased(deckey)) {
            sprite.value -= kbnum;
        }
    }

    if(quantized) {
        sprite.value = round(sprite.value);
    }

    calcSpritePos();

    updateValueDisplay(sprite.value, valueDisplayFont);

    return nullptr;
}

float Slider::calculateValue() {
    Vector2f mousePos(keys.magnitude("mousex"),
                      keys.magnitude("mousey"));

    mousePos = mousePos * std::abs(line.position[2])/2;

    float value = minVal;

    if(mousePos[axis]<=minBound) {
        value = minVal;
    } else if(mousePos[axis]>=maxBound) {
        value = maxVal;
    } else if (maxVal == 0) {
        value = (((mousePos[axis]-minBound)/(maxBound-minBound)))*(-minVal)+minVal;
    } else {
        value = (((mousePos[axis]-minBound)/(maxBound-minBound))*maxVal)*(1-(minVal/maxVal))+minVal;
    }
    return value;
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

void Slider::updateValueDisplay(float value, VirtualResource labelFont) {
    if(displayPrecision+2>8) {
        displayPrecision = 6;
    }
    if(!quantized) {
        std::string str = std::to_string(value);
        valueDisplay.render_str(str.substr(0, str.find_first_of(".")+displayPrecision+1).c_str(),
                                labelFont,lineStyle);
    } else {
        valueDisplay.render_str(std::to_string((int)value).c_str(),
                                labelFont,lineStyle);
    }
}

void Slider::setBounds() {
    float ratio = Argon::Screen::ratio()/2;
    minBound = ratio*line.position[axis]-(line.bounds.size[axis]/2)*line.scale[axis]*ratio;
    maxBound = ratio*line.position[axis]+(line.bounds.size[axis]/2)*line.scale[axis]*ratio;
}

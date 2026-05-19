#include "slider.h"

using namespace Argon::Addons;

Slider::Slider(Axis axis, float minVal, float maxVal): 
    minVal(minVal), 
    maxVal(maxVal), 
    axis(axis), 
    displayPrecision(6), 
    quantized(true),
    mouseable(true),
    keyboardable(true),
    kbnum(1),
    vdScaleOffset({0,0}),
    displayValues(true)
{
    if(axis == x) {
        inckey = "right";
        deckey = "left";
    } else {
        inckey = "up";
        deckey = "down";
    }

    setBounds();
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
    deckey("left"),
    vdScaleOffset({0,0}),
    displayValues(true)
{
    setBounds();
}

Slider::Slider(Axis axis): 
    minVal(0), 
    maxVal(100), 
    axis(axis), 
    displayPrecision(6), 
    quantized(true),
    mouseable(true),
    keyboardable(true),
    kbnum(1),
    vdScaleOffset({0,0}),
    displayValues(true)
{
    if(axis == x) {
        inckey = "right";
        deckey = "left";
    } else {
        inckey = "up";
        deckey = "down";
    }

    setBounds();
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
    deckey("left"),
    vdScaleOffset({0,0}),
    displayValues(true)
{
    setBounds();
}



void Slider::setValueDisplayPosition(float x, float y, float z) {
    setValueDisplayxPosition(x);
    setValueDisplayyPosition(y);
    setValueDisplayzPosition(z);
}

void Slider::setValueDisplayScale(float x, float y, float z) {
    setValueDisplayxScale(x);
    setValueDisplayyScale(y);
    setValueDisplayzScale(z);
}

float Slider::calculateValue() {
    Vector2f mousePos(keys.magnitude("mousex"),
                      keys.magnitude("mousey"));

    mousePos = mousePos * std::abs(line.position[2])/2;

    float value = minVal;

    float mp = axis == x ? mousePos[axis] : mousePos[1]*Screen::ratio();

    if(mp<=minBound) {
        value = minVal;
    } else if(mp>=maxBound) {
        value = maxVal;
    } else if (maxVal == 0) {
        value = (((mp-minBound)/(maxBound-minBound)))*(-minVal)+minVal;
    } else {
        value = (((mp-minBound)/(maxBound-minBound))*maxVal)*(1-(minVal/maxVal))+minVal;
    }

    return value;
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

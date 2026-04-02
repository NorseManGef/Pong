#include "sliderUtils.h"

using namespace Argon::Addons;

Slider::Slider(float minVal, float maxVal): minVal(minVal), maxVal(maxVal) {}

Slider::Slider(): minVal(0), maxVal(100) {}

FillSlider::FillSlider(): Slider() {}

FillSlider::FillSlider(float minVal, float maxVal): Slider(minVal, maxVal) {}

void FillSlider::setPosition(float x, float y, float z) {
    setxPosition(x);
    setyPosition(y);
    setzPosition(z);
}

void FillSlider::setxPosition(float x) {

}

void FillSlider::setyPosition(float y) {

}

void FillSlider::setzPosition(float z) {

}

void FillSlider::setxScale(float x) {

}

void FillSlider::setyScale(float y) {
    
}

void FillSlider::setzScale(float z) {

}

bool FillSlider::overlaps_screen_coord(Vector2f coord) {
    return sprite.overlaps_screen_coord(coord);
}

std::shared_ptr<Argon::Node> FillSlider::animate(float time) {
    return nullptr;
}

void FillSlider::render(VirtualResource lineTexture,
                        VirtualResource spriteTexture,
                        VirtualResource labelFont) {
    line.texture = lineTexture;
    sprite.texture = spriteTexture;
    valueDisplay.render_str(std::to_string(sprite.value).c_str(),labelFont,kLineCenter);
}

void FillSlider::updateValueDisplay(float value, VirtualResource labelFont) {
    valueDisplay.render_str(std::to_string(sprite.value).c_str(),labelFont,kLineCenter);
}

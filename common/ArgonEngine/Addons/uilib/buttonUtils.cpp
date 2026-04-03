#include "buttonUtils.h"

using namespace Argon::Addons;

Button::Button(std::vector<std::string> keybinds,
               std::function<std::shared_ptr<Argon::Node>()> sendTo):
    button(),
    keybinds(keybinds),
    sendTo(sendTo)
{};

std::shared_ptr<Argon::Node> Button::animate(float time) {
    for(auto &i : keybinds) {
        if(keys.isReleased(i)) {
            return sendTo();
        }
    }
    return nullptr;
}

GrowButton::GrowButton(std::vector<std::string> keybinds,
                       std::function<std::shared_ptr<Argon::Node>()> sendTo,
                       Argon::Vector2f scaleMin,
                       Argon::Vector2f scaleMax,
                       float alpha): 
    Button(keybinds, sendTo),
    x_min(scaleMin[0]),
    x_max(scaleMax[0]),
    y_min(scaleMin[1]),
    y_max(scaleMax[1]),
    alpha(alpha) {};

std::shared_ptr<Argon::Node> GrowButton::animate(float time) {
    if(selected) {
        bool pressed = false;
        for(auto &i : keybinds) {
            if(keys.isReleased(i)) {
                return sendTo();
            } else if(keys.isPressed(i)) {
                pressed = true;
            }
        }
        if(!pressed){
            setxScale(button.Label::scale[0] * alpha + x_max * (1-alpha));
            setyScale(button.Label::scale[1] * alpha + y_max * (1-alpha));
        } else {
           setxScale(button.Label::scale[0] * alpha + (x_min*1.1) * (1-alpha));
           setyScale(button.Label::scale[1] * alpha + (y_min*1.1) * (1-alpha));
        }
    } else {
        setxScale(button.Label::scale[0] * alpha + x_min * (1-alpha));
        setyScale(button.Label::scale[1] * alpha + y_min * (1-alpha));
    }

    return nullptr;
}

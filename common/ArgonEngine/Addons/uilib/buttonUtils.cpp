#include "buttonUtils.h"

using namespace Argon::Addons;

Button::Button(std::vector<std::string> keybinds,
               std::function<std::shared_ptr<Argon::Node>()> sendTo):
    BorderedLabel(),
    keybinds(keybinds),
    sendTo(sendTo),
    willHide(true),
    selected(false)
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
        setxScale(BorderedLabel::Label::scale[0] * alpha + x_max * (1-alpha));
        setyScale(BorderedLabel::Label::scale[1] * alpha + y_max * (1-alpha));
        for(auto &i : keybinds) {
            if(keys.isReleased(i)) {
                return sendTo();
            }
        }
    } else {
         setxScale(BorderedLabel::Label::scale[0] * alpha + x_min * (1-alpha));
         setyScale(BorderedLabel::Label::scale[1] * alpha + y_min * (1-alpha));
    }

    return nullptr;
}

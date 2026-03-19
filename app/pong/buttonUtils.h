#ifndef BUTTONUTILS
#define BUTTONUTILS

#include <ArgonEngine/BorderedLabel.h>
#include <ArgonEngine/Node.h>
#include "ButtonInterface.h"
#include <vector>
#include <functional>

struct GrowButton : public Argon::Addons::BorderedLabel {
    bool selected;
    bool willHide;
    std::vector<std::string> keybinds;
    std::function<std::shared_ptr<Argon::Node>()> sendTo;
    ButtonInterface& keys = ButtonInterface::instance();

    float x_min;
    float x_max;
    
    float y_min;
    float y_max;

    float alpha;
  
    /// @param keybinds a vector of strings containing all 
    /// keybinds for which the button will be pressed.
    /// @param sendTo a function, returning a shared_ptr to an argon node, which
    /// is to be run upon the pressing of the button.
    /// @param scaleMin the scale when the button is not selected
    /// @param scaleMax the scame when the button is selected
    /// @param alpha a constant in the animation equation that probably does something
    GrowButton(std::vector<std::string> keybinds,
               std::function<std::shared_ptr<Argon::Node>()> sendTo,
               Argon::Vector2f scaleMin,
               Argon::Vector2f scaleMax,
               float alpha = .7): 
        BorderedLabel(),
        keybinds(keybinds),
        sendTo(sendTo),
        x_min(scaleMin[0]),
        x_max(scaleMax[0]),
        y_min(scaleMin[1]),
        y_max(scaleMax[1]),
        alpha(alpha),
        willHide(true),
        selected(false) {};

    std::shared_ptr<Argon::Node>animate(float time) {

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
};

#endif

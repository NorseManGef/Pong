#ifndef BUTTONUTILS
#define BUTTONUTILS

#include <ArgonEngine/Addons/BorderedLabel.h>
#include <ArgonEngine/Node.h>
#include "iointerface.h"
#include <vector>
#include <functional>

namespace Argon {
namespace Addons {

struct Button : public Argon::Addons::BorderedLabel {
    bool selected;
    bool willHide;

    std::vector<std::string> keybinds;
    std::function<std::shared_ptr<Argon::Node>()> sendTo;
    IOInterface& keys = IOInterface::instance();

    Button(std::vector<std::string> keybinds,
           std::function<std::shared_ptr<Argon::Node>()> sendTo);

    virtual std::shared_ptr<Argon::Node> animate(float time);
};

struct GrowButton : public Button {
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
               float alpha = .7);

    GrowButton() = delete;

    std::shared_ptr<Argon::Node> animate(float time);
};

}
}

#endif

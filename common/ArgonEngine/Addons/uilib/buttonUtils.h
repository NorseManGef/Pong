#ifndef BUTTONUTILS
#define BUTTONUTILS

#include <ArgonEngine/Addons/BorderedLabel.h>
#include <ArgonEngine/Node.h>
#include "iointerface.h"
#include "selectable.h"
#include <vector>
#include <functional>

namespace Argon {
namespace Addons {

struct Button : public Selectable {
    BorderedLabel button;

    std::vector<std::string> keybinds;
    std::function<std::shared_ptr<Argon::Node>()> sendTo;
    IOInterface& keys = IOInterface::instance();

    Button(std::vector<std::string> keybinds,
           std::function<std::shared_ptr<Argon::Node>()> sendTo);

    void setPosition(float x, float y, float z) { button.setPosition(x,y,z); }

    void setxPosition(float x) { button.setxPosition(x); }

    void setyPosition(float y) { button.setyPosition(y); }

    void setzPosition(float z) { button.setzPosition(z); }

    void setxScale(float x) { button.setxScale(x); }

    void setyScale(float y) { button.setyScale(y); }

    void setzScale(float z) { button.setzScale(z); }

    float xPosition() { return button.xPosition(); }

    float yPosition() { return button.yPosition(); }

    float zPosition() { return button.zPosition(); }

    bool overlaps_screen_coord(Vector2f coord) {
        return button.Sprite::overlaps_screen_coord(coord);
    }

    void render(const char* string,
                VirtualResource font,
                VirtualResource bgTexture,
                LineStyle style = kLineCenter,
                float marginX = 0.5,
                float marginY = 0.5) {
        button.render(string,font,bgTexture,style,marginX,marginY);
    }

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

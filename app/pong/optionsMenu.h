#ifndef OPTIONS_MENU
#define OPTIONS_MENU

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "wall.h"
#include "ButtonInterface.h"

struct OptionsMenu : Argon::Node {
    Wall outterTop;
    Wall outterBottom;
    Wall outterLeft;
    Wall outterRight;

    Wall innerLeft;

    Argon::Sprite back;
    Argon::Sprite controls;
    Argon::Sprite video;
    Argon::Sprite audio;

    Argon::Input input;

    Argon::Vector2f mousePosOld;

    ButtonInterface& buttons = ButtonInterface::instance();

    int selection;
    int menu;
    bool useSelection;

    bool mouseMoved;

    bool changed;

    OptionsMenu(std::shared_ptr<Argon::Node> prevNode) {
        selection = 0;
        useSelection = false;
        changed = false;

        back.texture = "resource://Back.png";
        controls.texture = "resource://Controls.png";
        video.texture = "resource://Video.png";
        audio.texture = "resource://Audio.png";
    }

    std::shared_ptr<Argon::Node> animate(float time) {
        Argon::Vector2f mousePos(input[Argon::kInputIDMouseX].value,
                                 input[Argon::kInputIDMouseY].value);
        
        mouseMoved = mousePos!=mousePosOld;

        mousePosOld = mousePos;

        if(selection < 0 && (buttons.isReleased("up")     || 
                             buttons.isReleased("down")   ||
                             buttons.isReleased("left")   ||
                             buttons.isReleased("right")  ||
                             buttons.isReleased("select") ||
                             buttons.isReleased("pause"))) {
            selection = 0;
        } else if(mouseMoved) {
            selection = -1;
        }

        if(menu == 0) {

        }

        if(menu == 1) {

        }

        return nullptr;
    }
};

#endif

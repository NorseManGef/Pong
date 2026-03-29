#include "menu.h"

using namespace Argon::Addons;

Menu::Menu():
    selection(-1),
    mouseMoved(false),
    willHide(false),
    incKey("down"),
    decKey("up"),
    mousePosOld(keys.magnitude("mousex"),
                keys.magnitude("mousey"))
{}

Menu::Menu(std::vector<Button*> menuButtons):
    selection(-1),
    mouseMoved(false),
    willHide(false),
    incKey("down"),
    decKey("up"),
    mousePosOld(keys.magnitude("mousex"),
                keys.magnitude("mousey")),
    menuButtons(menuButtons)
{}

void Menu::addButton(Button* button) {
    menuButtons.push_back(button);
}

void Menu::incSelection() {
    menuButtons[selection]->selected = false;
    selection += 1;
    if(selection >= menuButtons.size()) {
        selection = 0;
    }

    menuButtons[selection]->selected = true;
}

void Menu::decSelection() {
    menuButtons[selection]->selected = false;
    selection -= 1;
    if(selection < 0) {
        selection = menuButtons.size()-1;
    }

    menuButtons[selection]->selected = true;
}

void Menu::hide() {
    for(auto &i : menuButtons) {
        i->setzPosition(0);
    }
}

std::shared_ptr<Argon::Node> Menu::buttonHover(Button& button, Argon::Vector2f mp, float time) {
    if(button.Sprite::overlaps_screen_coord(mp)) {
        button.selected = true;
    } else {
        button.selected = false;
    }

    return button.animate(time);
}

std::shared_ptr<Argon::Node> Menu::animate(float time) {
    std::shared_ptr<Argon::Node> sendTo = nullptr;

    Argon::Vector2d mousePos(keys.magnitude("mousex"),
                             keys.magnitude("mousey"));

    mouseMoved = mousePos!=mousePosOld;

    mousePosOld = mousePos;

    if(!(selection<0)){
        if(keys.isReleased(incKey)) {
            incSelection();
        }

        if(keys.isReleased(decKey)) {
            decSelection();
        }
    } else if(keys.isReleased(incKey) || 
              keys.isReleased(decKey) || 
              keys.isReleased("select") &&
              selection < 0) {
        selection = 0;
    }

    if(mouseMoved) {
        for(auto &i : menuButtons) {
            auto x = buttonHover(*i, mousePos*mousePosCorrection, time);
            if(x!=nullptr) {
                sendTo = x;
                willHide = i->willHide;
            }
        }
    } else {
        for(auto &i : menuButtons) {
            auto x = i->animate(time);
            if(x!=nullptr) {
                sendTo = x;
                willHide = i->willHide;
            }
        }
    }

    if(willHide)hide();

    return sendTo;
}

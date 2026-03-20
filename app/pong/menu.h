#ifndef MENU
#define MENU

#include <vector>
#include "buttonUtils.h"
#include "constants.h"
#include <iostream>

/*! 
    \brief A menu library to abstract all the annoying logic behind a menu
    into buttons, and what happens when you press them.
*/
struct Menu {
    std::vector<GrowButton*> menuButtons;
    int selection;

    /*! \brief the key which, when pressed, will increment the selection */
    std::string incKey;
    /*! \brief the key which, when pressed, will decrement the selection */
    std::string decKey;

    ButtonInterface& keys = ButtonInterface::instance();
    Argon::Vector2f mousePosOld;
    bool mouseMoved;
    bool willHide;

    float mousePosCorrection = 10;

    /*! \brief Constructor for the Menu object */
    Menu():
        selection(-1),
        mouseMoved(false),
        willHide(false),
        incKey("down"),
        decKey("up")
    {}

    /*! 
        \brief Constructor for the Menu object
        \param menuButtons an std::vector<GrowButton*> of buttons in the menu 
    */
    Menu(std::vector<GrowButton*> menuButtons):
        selection(-1),
        mouseMoved(false),
        willHide(false),
        incKey("down"),
        decKey("up"),
        menuButtons(menuButtons)
    {}

    /*! 
        \brief adds buttons to the menu
        \param button GrowButton* of the button to add
    */
    void addButton(GrowButton* button) {
        menuButtons.push_back(button);
    }

    /*! \brief increments the selection */
    void incSelection() {
        menuButtons[selection]->selected = false;
        selection += 1;
        if(selection >= menuButtons.size()) {
            selection = 0;
        }

        menuButtons[selection]->selected = true;
    }

    /*! @brief decrements the selection */
    void decSelection() {
        menuButtons[selection]->selected = false;
        selection -= 1;
        if(selection < 0) {
            selection = menuButtons.size()-1;
        }

        menuButtons[selection]->selected = true;
    }

    /*! @brief hides the menu by moving all buttons in the menu out of view */
    void hide() {
        for(auto &i : menuButtons) {
            i->setzPosition(0);
        }
    }

    /*! @brief checks if a button is being hovered over by the mouse */
    std::shared_ptr<Argon::Node> buttonHover(GrowButton& button, Vector2f mp, float time) {
        if(button.Sprite::overlaps_screen_coord(mp)) {
            button.selected = true;
        } else {
            button.selected = false;
        }

        return button.animate(time);
    }

    /*! 
        \brief iterates through all buttons, and checks if they're selected.
    
        Only one button can be selected at a time. If the mouse has moved this frame, 
        it checks for button selection based on the mouse, otherwise the selection can be
        incremented via incKey and decKey.

        \param time to keep the argon style
    */
    std::shared_ptr<Argon::Node> animate(float time) {
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
};

#endif

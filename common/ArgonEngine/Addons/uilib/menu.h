#ifndef MENU
#define MENU

#include <vector>
#include "buttonUtils.h"
#include "selectable.h"
#include "sliders/sliderUtils.h"
#include "iointerface.h"
#include <iostream>

namespace Argon {
namespace Addons {

/*! 
    \brief A menu library to abstract all the annoying logic behind a menu
    into buttons, and what happens when you press them.
*/
struct Menu {
    std::vector<Selectable*> menuItems;
    int selection;

    /*! \brief the key which, when pressed, will increment the selection */
    std::string incKey;
    /*! \brief the key which, when pressed, will decrement the selection */
    std::string decKey;

    IOInterface& keys = IOInterface::instance();
    Argon::Vector2f mousePosOld;
    bool mouseMoved;
    bool willHide;

    /*! \brief Constructor for the Menu object */
    Menu();

    /*! 
        \brief Constructor for the Menu object
        \param menuItems an std::vector<GrowButton*> of buttons in the menu 
    */
    Menu(std::vector<Selectable*> menuItems);

    /*! 
        \brief adds buttons to the menu
        \param button GrowButton* of the button to add
    */
    void addItem(Selectable* Item);

    /*! \brief increments the selection */
    void incSelection();

    /*! @brief decrements the selection */
    void decSelection();

    /*! @brief hides the menu by moving all buttons in the menu out of view */
    void hide();

    /*! @brief checks if a button is being hovered over by the mouse */
    std::shared_ptr<Argon::Node> itemHover(Selectable& item, Argon::Vector2f mp, float time);

    /*! 
        \brief iterates through all buttons, and checks if they're selected.
    
        Only one button can be selected at a time. If the mouse has moved this frame, 
        it checks for button selection based on the mouse, otherwise the selection can be
        incremented via incKey and decKey.

        \param time to keep the argon style
    */
    std::shared_ptr<Argon::Node> animate(float time);
};

}
}

#endif

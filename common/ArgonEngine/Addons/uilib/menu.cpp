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

Menu::Menu(std::vector<Selectable*> menuItems):
    selection(-1),
    mouseMoved(false),
    willHide(false),
    incKey("down"),
    decKey("up"),
    mousePosOld(keys.magnitude("mousex"),
                keys.magnitude("mousey")),
    menuItems(menuItems)
{}

void Menu::addItem(Selectable* item) {
    menuItems.push_back(item);
}

void Menu::incSelection() {
    if(menuItems.size()>0){
        menuItems[selection]->selected = false;
        selection += 1;
        if(selection >= menuItems.size()) {
            selection = 0;
        }

        menuItems[selection]->selected = true;
    }
}

void Menu::decSelection() {
    if(menuItems.size()>0) {
        menuItems[selection]->selected = false;
        selection -= 1;
        if(selection < 0) {
            selection = menuItems.size()-1;
        }

        menuItems[selection]->selected = true;
    }
}

void Menu::hide() {
    for(auto &i : menuItems) {
        i->setzPosition(0);
    }
}

std::shared_ptr<Argon::Node> Menu::itemHover(Selectable& item, Argon::Vector2f mp, float time) {
    if(item.overlaps_screen_coord(mp)) {
        item.selected = true;
    } else {
        item.selected = false;
    }

    return item.animate(time);
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
        for(auto &i : menuItems) {
            auto x = itemHover(*i, mousePos*std::abs(i->zPosition()), time);
            if(x!=nullptr) {
                sendTo = x;
                willHide = i->willHide;
            }
        }
    } else {
        for(auto &i : menuItems) {
            auto x = i->animate(time);
            if(x!=nullptr) {
                sendTo = x;
                willHide = i->willHide;
            }
        }
    }

    keys.reset();

    if(willHide)hide();

    return sendTo;
}

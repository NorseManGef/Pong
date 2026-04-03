#include "iointerface.h"

Key::Key(): _isPressed(false) {}
Key::Key(uint32_t keybind): _keybind(keybind), _isPressed(false) {}

void Key::reset() { _isPressed = false; }

bool Key::isReleased(Argon::Input& input) {
    if(input[_keybind]) {
        _isPressed = true;
    }
    if(_isPressed && !input[_keybind]) {
        _isPressed = false;
        return true;
    }
    return false;
}

double Key::magnitude(Argon::Input& input) { return input[_keybind].value; }

bool Key::isPressed(Argon::Input& input) { return input[_keybind]; }

uint32_t Key::keybind() { return _keybind; }


void IOInterface::addButton(std::string name, uint32_t keybind) {
    Key button(keybind);
    std::vector<Key> buttonVec;
    buttonVec.push_back(button);

    if(!buttons.emplace(name, buttonVec).second) {
        buttons[name].push_back(button);
    }
}

void IOInterface::removebutton(std::string name) {
    if(buttons[name].size() < 2) {
        buttons.erase(name);
    } else {
        buttons[name].pop_back();
    }
}

bool IOInterface::isReleased(std::string name) {
    auto it = buttons.find(name);
    if(it == buttons.end()) return false;

    for(auto &i : buttons.find(name)->second) {
        if(i.isReleased(input)) {
            return true;
        }
    } 
    return false;
}

bool IOInterface::isPressed(std::string name) {
    for(auto &i : buttons[name]) {
        if(i.isPressed(input)) {
            return true;
        }
    }
    return false;
}

double IOInterface::magnitude(std::string name) {
    double value = 0;

    for(auto &i : buttons[name]) {
        value += i.magnitude(input);
    }
    return value;
}

std::vector<uint32_t> IOInterface::keybind(std::string name) {
    std::vector<uint32_t> vec;

    for(auto &i : buttons[name]) {
        vec.push_back(i.keybind());
    }
    return vec;
}

void IOInterface::reset() {
    for(auto &i : buttons) {
        for(int x = 0; x < i.second.size(); ++x) {
            i.second[x].isReleased(input);
        }
    }
}

void IOInterface::clear() {
    buttons.clear();
}

IOInterface IOInterface::_instance;

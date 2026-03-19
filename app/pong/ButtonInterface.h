#ifndef MENUINTERFACE
#define MENUINTERFACE

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "options.h"

#define optkey Options::getInstance().keybinds

class Button {
private:
    bool _isPressed;
    uint32_t _keybind; 

public:
    Button(): _isPressed(false) {}
    Button(uint32_t keybind): _keybind(keybind), _isPressed(false) {}

    void reset() {
        _isPressed = false;
    }

    bool isReleased(Argon::Input& input) {
        if(input[_keybind]) {
            _isPressed = true;
        }
        if(_isPressed && !input[_keybind]) {
            _isPressed = false;
            return true;
        }
        return false;
    }

    double magnitude(Argon::Input& input) {
        return input[_keybind].value;
    }

    bool isPressed(Argon::Input& input) {
        return input[_keybind];
    }

    uint32_t keybind() {
        return _keybind;
    }
};

/// @brief The interface through which a set of Buttons is managed
/// for most use cases, you need only call isReleased(), or isPressed()
/// for a list of valid keys, see initilize()
class ButtonInterface {
public:   
    /// @brief Adds a button
    /// @param name the name of the button to be added
    /// @param keybind the button itself
    void addButton(std::string name, uint32_t keybind) {
        Button button(keybind);
        std::vector<Button> buttonVec;
        buttonVec.push_back(button);

        if(!buttons.emplace(name, buttonVec).second) {
            buttons[name].push_back(button);
        }
    }

    /// @brief Removes a button
    /// @param name the name of the button to be removed
    void removeButton(std::string name) {
        if(buttons[name].size() < 2) {
            buttons.erase(name);
        } else {
            buttons[name].pop_back();
        }
    }

    /// @brief checks whether a button has been released this frame
    /// @param name which button to check
    /// @return bool whether the button has been released
    bool isReleased(std::string name) {
        for(auto &i : buttons[name]) {
            if(i.isReleased(input)) {
                return true;
            }
        } 
        return false;
    }
    
    /// @brief checks whether a button is currently being pressed
    /// @param name which button to check
    /// @return bool whether the button is being pressed
    bool isPressed(std::string name) {
        for(auto &i : buttons[name]) {
            if(i.isPressed(input)) {
                return true;
            }
        }
        return false;
    }

    double magnitude(std::string name) {
        double value = 0;

        for(auto &i : buttons[name]) {
            value += i.magnitude(input);
        }
        return value;
    }

    /// @brief returns all the buttons mapped to a control
    /// @param name which buttons to check
    /// @return std::vector<uint32_t> a list of all buttons mapped to the control
    std::vector<uint32_t> keybind(std::string name) {
        std::vector<uint32_t> vec;

        for(auto &i : buttons[name]) {
            vec.push_back(i.keybind());
        }
        return vec;
    }

    /// @brief resets the buttons to be unpressed
    void reset() {
        for(auto &i : buttons) {
            for(auto x : i.second) {
                x.reset();
            }
        }
    }

    /// @brief wipes all buttons from the interface
    void clear() {
        buttons.clear();
    }

    static ButtonInterface& instance() {
        return _instance;
    }

    /// @brief initializes the interface with buttons from options.h
    void initialize() {
        initHelper("pause", optkey.getPause());
        
        initHelper("leftClick", optkey.getLeftClick());
        initHelper("mousex", optkey.getMouseX());
        initHelper("mousey", optkey.getMouseY());

        initHelper("up", optkey.getMenuUp());
        initHelper("down", optkey.getMenuDown());
        initHelper("left", optkey.getMenuLeft());
        initHelper("right", optkey.getMenuRight());
        initHelper("select", optkey.getSelect());

        initHelper("paddleUp", optkey.getPaddleUp());
        initHelper("paddleDown", optkey.getPaddleDown());
        initHelper("holdBall", optkey.getHoldBall());
    }

private:
    std::unordered_map<std::string, std::vector<Button>> buttons;
    Argon::Input input;

    ButtonInterface() {}

    static ButtonInterface _instance;

    void initHelper(std::string name, const std::vector<uint32_t> keys) {
        for(auto i : keys) {
            addButton(name, i);
        }
    }
};

#endif

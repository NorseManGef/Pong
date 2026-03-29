#ifndef IOINTERFACE
#define IOINTERFACE

#include <ArgonEngine/Node.h>
#include <ArgonEngine/Sprite.h>
#include <ArgonEngine/Hardware.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "keynames.h"

/*! \brief A helper class for IOInterface */
class Key {
private:
    bool _isPressed;
    uint32_t _keybind; 

public:
    Key();
    Key(uint32_t keybind);

    void reset();

    bool isReleased(Argon::Input& input);

    double magnitude(Argon::Input& input);

    bool isPressed(Argon::Input& input);

    uint32_t keybind();
};

/// @brief The interface through which a set of Buttons is managed
/// for most use cases, you need only call isReleased(), or isPressed()
/// for a list of valid keys, see initilize()
class IOInterface {
public:   
    /// @brief Adds a button
    /// @param name the name of the button to be added
    /// @param keybind the button itself
    void addButton(std::string name, uint32_t keybind);

    /// @brief Removes a button
    /// @param name the name of the button to be removed
    void removebutton(std::string name);

    /// @brief checks whether a button has been released this frame
    /// @param name which button to check
    /// @return bool whether the button has been released
    bool isReleased(std::string name);

    /// @brief checks whether a button is currently being pressed
    /// @param name which button to check
    /// @return bool whether the button is being pressed
    bool isPressed(std::string name);

    /*!
        \brief returns the combined magnitude of all inputs bound to the button
        \param name the button to check
        \return double the combined magnitude of all inputs to the button
    */
    double magnitude(std::string name);

    /// @brief returns all the buttons mapped to a control
    /// @param name which buttons to check
    /// @return std::vector<uint32_t> a list of all buttons mapped to the control
    std::vector<uint32_t> keybind(std::string name);

    /// @brief resets the buttons to be unpressed
    void reset();

    /// @brief wipes all buttons from the interface
    void clear();

    static IOInterface& instance() {
        return _instance;
    }

    /// @brief initializes the interface with buttons from options.h
    void initialize(std::unordered_map<std::string, 
                    std::vector<Argon::StringIntern>> inputs) {
        for(auto &i : inputs) {
            initHelper(i.first, Argon::Addons::Keynames::getCode(i.second));
        }
    }

private:
    std::unordered_map<std::string, std::vector<Key>> buttons;
    Argon::Input input;

    IOInterface() {}

    static IOInterface _instance;

    void initHelper(std::string name, const std::vector<uint32_t> &keys) {
        for(auto i : keys) {
            addButton(name, i);
        }
    }
};

#endif

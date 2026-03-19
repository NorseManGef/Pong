#ifndef OPTIONS
#define OPTIONS

#include <ArgonEngine/VirtualResource.h>
#include <ArgonEngine/Hardware.h>
#include <unordered_map>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "constants.h"

using namespace Argon;

enum class resolution { // UW = ultrawide
    SD = 1,
    SDUW = 2,
    HD = 3,
    HDUW = 4,
    FHD = 6,
    FHDUW = 7,
    UHD = 8,
    UHDUW = 9,
}; 

struct Keynames {
    static bool populated;
    static std::unordered_map<std::string, uint32_t> map;

    static uint32_t getKey(const std::string& keyname) {
        if(!populated) {
            populate();
        }

        return map[keyname];
    }

    static uint32_t getKey(const Argon::StringIntern& keyname) {
        return getKey(keyname.str());
    }

    static void populate() {
        #include "keypop_intern.inc"        
        populated = true;
    }
};

struct Keybinds : public Argon::ReflectionBase {
    using bindSet = std::vector<Argon::StringIntern>;
    using codeSet = std::vector<uint32_t>;

    bindSet pause;
    bindSet leftClick;
    bindSet mouseX;
    bindSet mouseY;

    bindSet menuUp;
    bindSet menuDown;
    bindSet menuLeft;
    bindSet menuRight;
    bindSet select;

    bindSet paddleUp;
    bindSet paddleDown;
    bindSet holdBall;

    const codeSet getPause() const {
        codeSet result(pause.size());
        std::transform(pause.begin(), pause.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }

    const codeSet getLeftClick() const {
        codeSet result(leftClick.size());
        std::transform(leftClick.begin(), leftClick.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }

    const codeSet getMouseX() const {
        codeSet result(mouseX.size());
        std::transform(mouseX.begin(), mouseX.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }

    const codeSet getMouseY() const {
        codeSet result(mouseY.size());
        std::transform(mouseY.begin(), mouseY.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }

    const codeSet getMenuUp() const {
        codeSet result(menuUp.size());
        std::transform(menuUp.begin(), menuUp.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }

    const codeSet getMenuDown() const {
        codeSet result(menuDown.size());
        std::transform(menuDown.begin(), menuDown.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }

    const codeSet getMenuLeft() const {
        codeSet result(menuLeft.size());
        std::transform(menuLeft.begin(), menuLeft.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }

    const codeSet getMenuRight() const {
        codeSet result(menuRight.size());
        std::transform(menuRight.begin(), menuRight.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }

    const codeSet getSelect() const {
        codeSet result(select.size());
        std::transform(select.begin(), select.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }

    const codeSet getPaddleUp() const {
        codeSet result(paddleUp.size());
        std::transform(paddleUp.begin(), paddleUp.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }

    const codeSet getPaddleDown() const {
        codeSet result(paddleDown.size());
        std::transform(paddleDown.begin(), paddleDown.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }

    const codeSet getHoldBall() const {
        codeSet result(holdBall.size());
        std::transform(holdBall.begin(), holdBall.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return Keynames::getKey(s);
                       });
        return result;
    }



    //MAKE_VISIT_HEAD(Keybinds);
};


struct Options : Argon::ReflectionBase {
    // Audio
    float masterVolume;
    float musicVolume;
    float sfxVolume;

    // Video
    float uiScale;
    bool particles;

    // Controls
    Keybinds keybinds;

    void save() {
        write(constants::OPTIONS_PATH);
    }

    void load() {
        read(constants::OPTIONS_PATH);
    }

    static Options& getInstance() {
        return options;
    }
    
    static void initialize() {
        options = Options();
        std::ifstream file(constants::OPTIONS_PATH);
        if(!file.good()){
            options.setDefaults();
            file.close();
        } else {
            file.close();
            options.load();
        } 
    }

    void setDefaults() {
        masterVolume = .5;
        musicVolume = 1;
        sfxVolume = 1;

        uiScale = 1;

        particles = true;

        keybinds.pause.push_back("escape");
        keybinds.pause.push_back("menu");

        keybinds.leftClick.push_back("mouseleft");
        keybinds.mouseX.push_back("mousex");
        keybinds.mouseY.push_back("mousey");

        keybinds.menuUp.push_back("up");
        keybinds.menuUp.push_back("k");

        keybinds.menuDown.push_back("down");
        keybinds.menuDown.push_back("j");

        keybinds.menuLeft.push_back("left");
        keybinds.menuLeft.push_back("h");

        keybinds.menuRight.push_back("right");
        keybinds.menuRight.push_back("l");

        keybinds.select.push_back("enter");
        keybinds.select.push_back(" ");

        keybinds.paddleUp.push_back("up");
        keybinds.paddleUp.push_back("k");

        keybinds.paddleDown.push_back("down");
        keybinds.paddleDown.push_back("j");

        keybinds.holdBall.push_back("space");
    }

private:
    static Options options;

    Options& operator=(const Options& other) = delete;
    Options& operator=(Options&& other) = default;

public:
    //MAKE_VISIT_HEAD(Options);
};


//MAKE_VISIT_IMPL(Options, {
//    ADD_VAR(masterVolume);
//    ADD_VAR(musicVolume);
//    ADD_VAR(sfxVolume);
//    ADD_VAR(uiScale);
//    ADD_VAR(particles);
//    ADD_VAR(keybinds);
//});

#endif

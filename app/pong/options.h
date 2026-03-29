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
#include <ArgonEngine/Addons/uilib/ui.h>

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


struct Options : Argon::ReflectionBase {
    // Audio
    float masterVolume;
    float musicVolume;
    float sfxVolume;

    // Video
    float uiScale;
    bool particles;
    resolution res = resolution::FHD;


    // Keybinds
    std::unordered_map<std::string, std::vector<Argon::StringIntern>> keymap;

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
        
        keymap["pause"] = {"escape", "menu"};
        keymap["leftClick"] = {"mouseleft"};
        keymap["mousex"] = {"mousex"};
        keymap["mousey"] = {"mousey"};
        keymap["up"] = {"up", "k"};
        keymap["down"] = {"down", "j"};
        keymap["left"] = {"left", "h"};
        keymap["right"] = {"right", "l"};
        keymap["select"] = {"enter", " "};
        keymap["paddleUp"] = {"up", "k"};
        keymap["paddleDown"] = {"down", "j"};
        keymap["holdBall"] = {" "};

        IOInterface::instance().initialize(keymap);
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

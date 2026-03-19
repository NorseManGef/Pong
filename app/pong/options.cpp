#include "options.h"
#include <unordered_map>

Options Options::options;

bool Keynames::populated = false;

std::unordered_map<std::string, uint32_t> Keynames::map;

//MAKE_VISIT_IMPL(Options, {
//    ADD_VAR(masterVolume);
//    ADD_VAR(musicVolume);
//    ADD_VAR(sfxVolume);
//    ADD_VAR(uiScale);
//    ADD_VAR(particles);
//    ADD_VAR(keybinds);
//});

//MAKE_VISIT_IMPL(Keybinds, {
//    ADD_VAR(pause);
//    ADD_VAR(leftClick);
//    ADD_VAR(menuUp);
//    ADD_VAR(menuDown);
//    ADD_VAR(menuLeft);
//    ADD_VAR(menuRight);
//    ADD_VAR(select);
//    ADD_VAR(paddleUp);
//    ADD_VAR(paddleDown);
//    ADD_VAR(holdBall);
//});

#ifndef KEYNAMES
#define KEYNAMES

#include <ArgonEngine/VirtualResource.h>
#include <ArgonEngine/Hardware.h>
#include <unordered_map>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iostream>

namespace Argon {
namespace Addons {

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

    static std::vector<uint32_t> getCode(std::vector<Argon::StringIntern> input) {
        std::vector<uint32_t> result(input.size());
        std::transform(input.begin(), input.end(), result.begin(), 
                       [](const Argon::StringIntern& s) {
                            return getKey(s);
                       });
        return result;
    }
};

}
}

#endif

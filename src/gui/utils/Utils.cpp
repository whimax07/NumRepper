//
// Created by max on 01/11/22.
//

#include "Utils.h"

namespace repper {

std::string Utils::removeFormatPrefix(const std::string &inString, int base) {
    if (inString.length() == 0 || inString.length() == 1) {
        return {inString};
    }

    switch (base) {
        case 2: {
            auto pattern = std::regex("^0[bB].*");
            if (std::regex_match(inString, pattern)) {
                return inString.substr(2);
            }
            return {inString};
        }

        case 10:
            return {inString};

        case 16: {
            auto pattern = std::regex("^0[xX].*");
            if (std::regex_match(inString, pattern)) {
                return inString.substr(2);
            }
            return {inString};
        }

        default:
            throw std::logic_error("Base is not supported." + std::to_string(base));
    }
}

} // repper

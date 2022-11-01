//
// Created by max on 01/11/22.
//

#ifndef NUMREPRESENTATION_UTILS_H
#define NUMREPRESENTATION_UTILS_H

#include <string>
#include <c++/9/stdexcept>
#include <regex>

namespace repper {

class Utils {

public:
    static std::string removeFormatPrefix(const std::string &inString, int base);

};

} // repper

#endif //NUMREPRESENTATION_UTILS_H

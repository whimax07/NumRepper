//
// Created by max on 23/04/22.
//

#include <iostream>

#include "BinaryEditor.h"


void BinaryEditor::valueUpdated(const int bitPosChanged, const bool high) {
    std::cout << "Bit pos = " << bitPosChanged << " to " << high << std::endl;
}

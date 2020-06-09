#include "AssertError.h"
#include <iostream>

void AssertError::assert(bool test, const std::string& errMsg) {
    if (!test) {
        std::cerr << errMsg << "\n";
        throw errMsg;
    }
}

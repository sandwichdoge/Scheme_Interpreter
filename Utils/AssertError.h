#ifndef INCLUDE_ASSERT_ERROR_H
#define INCLUDE_ASSERT_ERROR_H

#include <string>

class AssertError {
    public:
    static void assert(bool, const std::string& errMsg);
};

#define eassert(b, s) { \
    AssertError::assert(b, s); \
}

#endif
#ifndef INCLUDE_DEBUG_H
#define INCLUDE_DEBUG_H
#include <iostream>

#ifdef DEBUG
#define db(str) { \
                    std::cout << str << "\n"; \
                }
#else
#define db(str) {}
#endif

#endif
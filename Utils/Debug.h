#ifndef INCLUDE_DEBUG_H
#define INCLUDE_DEBUG_H
#include <iostream>

#ifdef DEBUG
#define db(str) { \
                    std::cout << __FILE__ << ":" << __LINE__ << "\t" << str << "\n"; \
                }
    #define print_vector(v) { \
        for (auto _db_v_it : v) { \
            std::cout << _db_v_it << ","; \
        } \
        std::cout << "\n"; \
    }
#else
#define db(str) {}
#define print_vector(v) {}
#endif

#endif

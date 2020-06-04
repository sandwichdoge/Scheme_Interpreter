#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_
#include <iostream>
#include <string>
#include <vector>

class StringUtils {
   public:
    static bool replace(std::string& s, std::string sub_old, std::string sub_new);
    static void split(const std::string& str, const std::string& delim, std::vector<std::string>& out);
    static bool isValidNumberString(const std::string& s);
    static bool stringToDouble(std::string s, double& out);
};

#endif
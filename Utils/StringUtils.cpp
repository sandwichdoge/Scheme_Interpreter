#include "StringUtils.h"

void StringUtils::split(const std::string& str, const std::string& delim, std::vector<std::string>& out) {
    out.clear();
    size_t cp, fp;  // current position, found position
    const size_t dsize = delim.size();
    for (cp = 0; (fp = str.find(delim, cp)) != std::string::npos; cp = fp + dsize) {
        out.emplace_back(std::string(str, cp, fp - cp));
    }
    out.emplace_back(std::string(str, cp, str.size() - cp));
}

bool StringUtils::replace(std::string& s, std::string sub_old, std::string sub_new) {
    if (sub_old == sub_new || sub_old.empty()) return false;

    size_t old_pos = 0;

    while (1) {
        old_pos = s.find(sub_old, old_pos);
        if (old_pos == std::string::npos) break;

        s.replace(old_pos, sub_old.length(), sub_new);
        old_pos += sub_new.length();
    }

    return true;
}

bool StringUtils::stringToDouble(std::string s, double& out) {
    if (!isValidNumberString(s)) {
        return false;
    }

    int total = sscanf(s.c_str(), "%lf", &out);
    if (total <= 0) {
        return false;
    }

    return true;
}

bool StringUtils::isValidNumberString(const std::string& s) {
    if (s.empty()) return false;
    
    int start = 0;
    if (s[0] == '-' || s[0] == '+') start++;

    for (int i = start; s[i]; i++) {
        if (s[i] != '.' && (s[i] < '0' || s[i] > '9')) {
            return false;
        }
    }

    return true;
}

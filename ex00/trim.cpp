#include "main.hpp"

std::string trim(const std::string &toTrim, const char c) {
    std::string trimmedString;
    int i = 0;
    int j = 0;

    while (toTrim.at(i) == c) {
        i++;
    }

    while (toTrim.size() > static_cast<size_t>(i + j) && toTrim.at(i + j) != c) {
        j++;
    }

    trimmedString = toTrim.substr(i, j);
    return (trimmedString);
}

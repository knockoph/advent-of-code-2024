#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include <string>
#include <sstream>
#include <vector>


std::vector<std::string> split(const std::string& s, char token = ' ', bool skip_empty = false) {
    std::vector<std::string> result {};
    std::istringstream stream {s};
    std::string part;

    while(std::getline(stream, part, token)) {
        if (skip_empty && part.size() == 0) {
            continue;
        }
        result.push_back(part);
    }

    return result;
}

#endif  // UTILS_STRING_H

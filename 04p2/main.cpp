#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <vector>
#include <filesystem>
#include "../utils/container.h"


int match_right_down(const std::vector<std::vector<char>>& v, const std::string& w, int x, int y) {
    --x;
    --y;
    if (x < 0 || y < 0) return 0;

    int w_size {w.size()};
    int v_horizontal_size {v.at(y).size()};
    int v_vertical_size {v.size()};
    if (x + w_size > v_horizontal_size) return 0;
    if (y + w_size > v_vertical_size) return 0;

    for (auto c: w) {
        if (c != v.at(y++).at(x++)) return 0;
    }
    return 1;
}


int match_right_up(const std::vector<std::vector<char>>& v, const std::string& w, int x, int y) {
    --x;
    y++;
    int v_vertical_size {v.size()};
    if (x < 0) return 0;
    if (y >= v_vertical_size) return 0;

    int w_size {w.size()};
    int v_horizontal_size {v.at(y).size()};
    if (x + w_size > v_horizontal_size) return 0;
    if (y + 1 - w_size < 0) return 0;

    for (auto c: w) {
        if (c != v.at(y--).at(x++)) return 0;
    }
    return 1;
}


int match_left_down(const std::vector<std::vector<char>>& v, const std::string& w, int x, int y) {
    ++x;
    --y;
    if (y < 0) return 0;
    int v_horizontal_size {v.at(y).size()};
    if (x >= v_horizontal_size) return 0;

    int w_size {w.size()};
    int v_vertical_size {v.size()};
    if (x + 1 - w_size < 0) return 0;
    if (y + w_size > v_vertical_size) return 0;

    for (auto c: w) {
        if (c != v.at(y++).at(x--)) return 0;
    }
    return 1;
}


int match_left_up(const std::vector<std::vector<char>>& v, const std::string& w, int x, int y) {
    ++x;
    ++y;
    int v_vertical_size {v.size()};
    if (y >= v_vertical_size) return 0;
    int v_horizontal_size {v.at(y).size()};
    if (x >= v_horizontal_size) return 0;

    int w_size {w.size()};
    if (x + 1 - w_size < 0) return 0;
    if (y + 1 - w_size < 0) return 0;

    for (auto c: w) {
        if (c != v.at(y--).at(x--)) return 0;
    }
    return 1;
}


int main() {
    const std::string w = "MAS";

    std::filesystem::path f {"input_data/input.txt"};
    assert(exists(f));
    assert(is_regular_file(f));
    std::ifstream ifs {f};

    std::string line;
    std::vector<std::vector<char>> v {};

    while(getline(ifs, line)) {
        std::vector<char> vl {};
        for (auto c: line) {
            vl.push_back(c);
        }
        v.push_back(vl);
        print_container(vl, "");
    }

    int x = 0;
    int y = 0;
    int sum = 0;

    for (const auto& vl: v) {
        for (auto c: vl) {
            if (c == 'A') {
                if(match_right_down(v, w, x, y) == 1) {
                    if (match_right_up(v, w, x, y) == 1 || match_left_down(v, w, x, y) == 1) sum++;
                } else if (match_left_up(v, w, x, y) == 1) {
                    if (match_right_up(v, w, x, y) == 1 || match_left_down(v, w, x, y) == 1) sum++;
                }
            }
            ++x;
        }
        x = 0;
        ++y;
    }

    std::cout << sum << "\n";

    return 0;
}

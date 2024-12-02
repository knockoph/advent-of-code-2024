#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>
#include <assert.h>


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


auto zip(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::vector<std::tuple<int,int>> result;
    int size = std::min(v1.size(), v2.size());
    for (int i = 0; i < size; i++) {
        result.emplace_back(v1.at(i), v2.at(i));
    }
    return result;
}


void print_vec(const std::vector<int>& v) {
    for (auto i: v) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}


void print_map(const std::map<int,int>& m, char space = ' ') {
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << space << it->second << "\n";
    }
}


int main() {
    std::filesystem::path f {"input_data/input.txt"};
    assert(exists(f));
    assert(is_regular_file(f));
    std::ifstream ifs {f};
    std::string line;

    std::vector<int> l1;
    std::vector<int> l2;

    while(std::getline(ifs, line)) {
        auto parts = split(line, ' ', true);
        assert(parts.size() == 2);
        int first = std::stoi(parts.at(0));
        int second = std::stoi(parts.at(1));
        l1.push_back(first);
        l2.push_back(second);
    }

    std::map<int,int> scores {};

    for (auto second: l2) {
        scores[second] += 1;
    }

    print_map(scores);

    int sum = 0;

    for (auto first: l1) {
        int score = first * scores[first];
        sum += score;
    }

    std::cout << sum << "\n";

    return 0;
}

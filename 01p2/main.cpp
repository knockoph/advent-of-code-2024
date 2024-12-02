#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <concepts>
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


template<typename C>
concept Container = requires(C c) {
    { c.begin() } -> std::same_as<typename C::iterator>;
    { c.end() } -> std::same_as<typename C::iterator>;
    typename C::value_type;
};


template<typename C1, typename C2>
requires Container<C1> && Container<C2>
auto zip(const C1& c1, const C2& c2) {
    using T1 = std::decay_t<typename C1::value_type>;
    using T2 = std::decay_t<typename C2::value_type>;

    std::vector<std::pair<T1, T2>> result;
    result.reserve(std::min(c1.size(), c2.size()));

    auto it1 = std::begin(c1);
    auto it2 = std::begin(c2);
    auto end1 = std::end(c1);
    auto end2 = std::end(c2);
    
    for (; it1 != end1 && it2 != end2; ++it1, ++it2) {
        result.emplace_back(*it1, *it2);
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

#ifndef UTILS_CONTAINER_H
#define UTILS_CONTAINER_H


#include <map>
#include <iostream>
#include <concepts>
#include <vector>
#include <string>


template<typename C>
concept Container = requires(C c) {
    { c.begin() } -> std::same_as<typename C::iterator>;
    { c.end() } -> std::same_as<typename C::iterator>;
    { c.size() } -> std::same_as<typename C::size_type>;
    std::is_same_v<decltype(*c.begin()), typename C::value_type&>;
};


template<typename C1, typename C2>
requires Container<C1> && Container<C2>
auto zip(const C1& c1, const C2& c2, int offset = 0) {
    using T1 = std::decay_t<typename C1::value_type>;
    using T2 = std::decay_t<typename C2::value_type>;

    std::vector<std::pair<T1, T2>> result;
    result.reserve(std::min(c1.size() - offset, c2.size() - offset));

    auto it1 = c1.begin();
    auto it2 = c2.begin() + offset;
    auto end1 = c1.end() - offset;
    auto end2 = c2.end();
    
    for (; it1 != end1 && it2 != end2; ++it1, ++it2) {
        result.emplace_back(*it1, *it2);
    }

    return result;
}


template<typename C>
requires Container<C>
auto all_stoi(const C& c) {
    std::vector<int> result;
    result.reserve(c.size());
    for (const auto& e: c) {
        result.emplace_back(std::stoi(e));
    }
    return result;
}


template<typename C>
requires Container<C>
void print_container(const C& c, const std::string& sep = " ", const std::string& end = "\n") {
    for (const auto& e: c) {
        std::cout << e << sep;
    }
    std::cout << end;
}


template<typename T1, typename T2>
void print_map(const std::map<T1,T2>& m, const std::string& element_sep = ":", const std::string& tuple_sep = "\n", const std::string& end = "") {
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << element_sep << it->second << tuple_sep;
    }
    std::cout << end;
}

#endif  // UTILS_CONTAINER_H

#ifndef UTILS_CONTAINER_H
#define UTILS_CONTAINER_H


#include <map>
#include <iostream>
#include <concepts>
#include <vector>


template<typename C>
concept Container = requires(C c) {
    { c.begin() } -> std::same_as<typename C::iterator>;
    { c.end() } -> std::same_as<typename C::iterator>;
    { c.size() } -> std::same_as<typename C::size_type>;
    typename C::value_type;
};


template<typename C1, typename C2>
requires Container<C1> && Container<C2>
auto zip(const C1& c1, const C2& c2) {
    using T1 = std::decay_t<typename C1::value_type>;
    using T2 = std::decay_t<typename C2::value_type>;

    std::vector<std::pair<T1, T2>> result;
    result.reserve(std::min(c1.size(), c2.size()));

    auto it1 = c1.begin();
    auto it2 = c2.begin();
    auto end1 = c1.end();
    auto end2 = c2.end();
    
    for (; it1 != end1 && it2 != end2; ++it1, ++it2) {
        result.emplace_back(*it1, *it2);
    }

    return result;
}


template<typename C>
requires Container<C>
void print_container(const C& c, char separator = ' ') {
    auto it = c.begin();
    auto end = c.end();
    for (; it != end; it++) {
        std::cout << *it << separator;
    }
    std::cout << "\n";
}


template<typename T1, typename T2>
void print_map(const std::map<T1,T2>& m, char separator = ':') {
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << separator << it->second << "\n";
    }
}

#endif  // UTILS_CONTAINER_H

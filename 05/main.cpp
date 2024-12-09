#include <iostream>
#include <filesystem>
#include <assert.h>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
#include <set>
#include "../utils/string.h"
#include "../utils/container.h"


std::pair<int,int> parse_ordering(const std::string& line) {
    auto v = all_stoi(split(line, '|', false));
    return {v.at(0), v.at(1)};
}


std::vector<int> parse_update(const std::string& line) {
    return all_stoi(split(line, ',', false));
}


int get_middle_if_valid_update(const std::vector<int>& v, std::map<int,std::set<int>> orderings) {
    std::set<int> s {};
    for (auto i: v) {
        if(!orderings.contains(i)) {
            s.insert(i);
            continue;
        }
        for(auto j: orderings[i]) {
            if (s.contains(j)) {
                return 0;
            }
        }
        s.insert(i);
    }
    int middle_pos = v.size() / 2;
    return v[middle_pos];
}



int main() {
    std::filesystem::path f {"input_data/input.txt"};
    assert(exists(f));
    assert(is_regular_file(f));
    std::ifstream ifs {f};

    std::string line;
    bool parsed_orderings = false;

    std::map<int,std::set<int>> orderings {};
    std::vector<std::vector<int>> updates {};

    while(getline(ifs, line)) {
        if(empty(line)) {
            parsed_orderings = true;
            continue;
        }
        if(!parsed_orderings) {
            auto ordering = parse_ordering(line);
            if(!orderings.contains(ordering.first)) {
                std::set<int> s {};
                orderings[ordering.first] = s;
            }
            orderings[ordering.first].insert(ordering.second);
            continue;
        }
        updates.push_back(parse_update(line));
    }

    for (const auto& e: orderings) {
        std::cout << e.first << ": ";
        print_container(e.second);
    }

    std::cout << "\n";

    int sum = 0;

    for (auto const& u: updates) {
        auto middle_value = get_middle_if_valid_update(u, orderings);
        std::cout << middle_value << ": ";
        print_container(u);
        sum += middle_value;
    }

    std::cout << "\n" << sum << "\n";

    return 0;
}

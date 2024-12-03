#include <fstream>
#include <filesystem>
#include <assert.h>
#include "../utils/string.h"
#include "../utils/container.h"


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

    print_container(l1);

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

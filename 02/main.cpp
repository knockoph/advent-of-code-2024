#include <iostream>
#include <fstream>
#include <filesystem>
#include <assert.h>
#include "../utils/string.h"
#include "../utils/container.h"


int check_sequence(const std::vector<int>& numbers) {
    int prev_delta = 0;

    for (auto const& [first, second]: zip(numbers, numbers, 1)) {
        std::cout << first << " " << second << "\n";
        int delta = second - first;
        if (abs(delta) > 3 || abs(delta) < 1) return 0;
        if ((prev_delta < 0 && delta > 0) || (prev_delta > 0 && delta < 0)) return 0;
        prev_delta = delta;
    }
    return 1;
}


int main() {
    std::filesystem::path f {"input_data/input.txt"};
    assert(exists(f));
    assert(is_regular_file(f));
    std::ifstream ifs {f};

    std::string line;

    int count_safe = 0;

    while(getline(ifs, line)) {
        std::cout << line << "\n";
        auto tokens = split(line);
        auto numbers = all_stoi(tokens);

        count_safe += check_sequence(numbers);
    }

    std::cout << count_safe << "\n";
}

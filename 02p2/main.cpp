#include <iostream>
#include <fstream>
#include <filesystem>
#include <assert.h>
#include "../utils/string.h"
#include "../utils/container.h"


int check_sequence(const std::vector<int>& numbers, bool recursed = false) {
    int prev_delta = 0;
    bool removed_one_bad = false;
    int pos = 0;

    for (auto const& [first, second]: zip(numbers, numbers, 1)) {
        int delta = second - first;
        bool is_bad = false;
        if (abs(delta) > 3 || abs(delta) < 1) is_bad = true;
        else if ((prev_delta < 0 && delta > 0) || (prev_delta > 0 && delta < 0)) is_bad = true;
        if (is_bad) {
            if (recursed) return 0;
            std::vector<int> numbers_mut {numbers};
            numbers_mut.erase(numbers_mut.begin() + pos);
            auto result = check_sequence(numbers_mut, true);
            if (result == 1) {
                print_container(numbers_mut, " ", " ||  ");
                print_container(numbers);
                return 1;
            }
            if (pos < numbers.size()-1) {
                std::vector<int> numbers_mut {numbers};
                numbers_mut.erase(numbers_mut.begin() + (pos+1));
                auto result = check_sequence(numbers_mut, true);
                if (result == 1) {
                    print_container(numbers_mut, " ", " ||  ");
                    print_container(numbers);
                    return 1;
                }
            }
            if (pos > 0) {
                std::vector<int> numbers_mut {numbers};
                numbers_mut.erase(numbers_mut.begin() + (pos-1));
                auto result = check_sequence(numbers_mut, true);
                if (result == 1) {
                    print_container(numbers_mut, " ", " ||  ");
                    print_container(numbers);
                    return 1;
                }
            }

            return 0;
        }
        prev_delta = delta;
        pos++;
    }
    if (!recursed) print_container(numbers);
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
        auto tokens = split(line, ' ', false);
        auto numbers = all_stoi(tokens);

        count_safe += check_sequence(numbers);
    }

    std::cout << count_safe << "\n";
}

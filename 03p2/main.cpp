#include <fstream>
#include <iostream>
#include <filesystem>
#include <assert.h>
#include <regex>
#include <string>
#include "../utils/string.h"
#include "../utils/container.h"

int main() {
    std::filesystem::path f {"input_data/input.txt"};
    assert(exists(f));
    assert(is_regular_file(f));
    std::ifstream ifs {f};

    std::string line;

    std::regex pat {R"(mul\(\d{1,3},\d{1,3}\)|do\(\)|don't\(\))"};
    std::smatch matches;

    int sum = 0;
    bool enabled = true;

    while(getline(ifs, line)) {
        for (std::sregex_iterator p{line.begin(), line.end(), pat}; p != std::sregex_iterator{}; ++p) {
            std::string instruction = (*p)[0];
            if (instruction == "do()") {
                std::cout << "do()\n";
                enabled = true;
                continue;
            }
            if (instruction == "don't()") {
                std::cout << "don't()\n";
                enabled = false;
                continue;
            }
            if(!enabled) continue;
            std::string sub_instruction {instruction.begin() + 4, instruction.end() - 1};
            std::cout << instruction << " " << sub_instruction << "\n";
            auto split_instruction = split(sub_instruction, ',');
            auto numbers = all_stoi(split_instruction);
            sum += numbers.at(0) * numbers.at(1);
        }
    }

    std::cout << sum << "\n";

    return 0;
}

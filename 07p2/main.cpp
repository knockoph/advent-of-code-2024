#include <filesystem>
#include <assert.h>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "../utils/string.h"
#include "../utils/container.h"


unsigned long long add(unsigned long long a, unsigned long long b) {
    return a + b;
}


unsigned long long mul(unsigned long long a, unsigned long long b) {
    return a * b;
}


unsigned long long cat(unsigned long long a, unsigned long long b) {
    return std::stoll(std::to_string(a) + std::to_string(b));
}


using FuncPtr = unsigned long long(*)(unsigned long long, unsigned long long);


std::vector<FuncPtr> funcs {add, mul, cat};


class Permutations {
private:
    int n_;
    int m_;
    std::vector<int> p_;

public:
    Permutations(int n, int m): n_{n}, m_{m}, p_(n, 0) {}

    std::vector<int> get() {
        return p_;
    }

    std::vector<int> next() {
        for(int i = 0; i < p_.size(); ++i) {
            p_.at(i) += 1;
            if (p_.at(i) < m_) break;
            else p_.at(i) = 0;
        }
        return p_;
    }
};


unsigned long long calculate(unsigned long long target, const std::vector<unsigned long long>& v) {
    assert(v.size() > 1);
    int n = v.size() - 1;
    int m = funcs.size();

    Permutations permutations {n, m};
    auto p = permutations.get();
    for (int i = 0; i < pow(funcs.size(), v.size() - 1); ++i) {
        auto v_it = v.begin();
        auto p_it = p.begin();
        unsigned long long result {*v_it};
        for (++v_it; v_it != v.end(), p_it != p.end(); ++v_it, ++p_it) {
            result = funcs[*p_it](result, *v_it);
        }
        if (result == target) {
            return result;
        }
        p = permutations.next();
    }
    return 0;
}


int main() {
    std::filesystem::path f {"input_data/input.txt"};
    assert(exists(f));
    assert(is_regular_file(f));
    std::ifstream ifs {f};

    unsigned long long sum = 0;

    std::string line;
    while(getline(ifs, line)) {
        auto split_line = split(line, ':', false);
        assert(split_line.size() == 2);
        auto target = stoull(split_line.at(0));
        auto values = all_stoull(split(split_line.at(1), ' ', true));
        unsigned long long result = calculate(target, values);
        std::cout << result << "\n";
        sum += result;
    }

    std::cout << sum << "\n";

    // std::string s {"77502824880"};
    // auto ll = stoll(s);
    // std::cout << ll;

    return 0;
}

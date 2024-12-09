#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <assert.h>
#include <map>
#include <set>


enum class Direction {
    Up,
    Down,
    Left,
    Right,
    Unknown,
    Out,
};


struct Movement {
    int x;
    int y;
    Direction d;

    friend std::ostream& operator<<(std::ostream& os, const Movement& m) {
        os << "X: " << m.x << ", Y: " << m.y << ", D: ";
        switch (m.d) {
            case Direction::Up:
                std::cout << "^";
                break;
            case Direction::Down:
                std::cout << "v";
                break;
            case Direction::Left:
                std::cout << "<";
                break;
            case Direction::Right:
                std::cout << ">";
                break;
            case Direction::Unknown:
                std::cout << "?";
                break;
            case Direction::Out:
                std::cout << "!";
                break;
        }
        return os;
    }
};


Movement detect_movement(const std::string& s, int y) {
    int x = 0;
    for (auto c: s) {
        switch (c) {
            case '^':
                return {x, y, Direction::Up};
            case 'v':
                return {x, y, Direction::Down};
            case '<':
                return {x, y, Direction::Left};
            case '>':
                return {x, y, Direction::Right};
        }
        ++x;
    }
    return {-1, -1, Direction::Unknown};
}


Movement advance_movement(Movement current, const std::vector<std::string>& m) {
    int next_x = current.x;
    int next_y = current.y;
    switch (current.d) {
        case Direction::Up:
            next_y = current.y - 1;
            if (next_y < 0) return {next_x, next_y, Direction::Out};
            if (m.at(next_y).at(next_x) == '#') return {current.x, current.y, Direction::Right};
            return {next_x, next_y, Direction::Up};
        case Direction::Down:
            next_y = current.y + 1;
            if (next_y >= m.size()) return {next_x, next_y, Direction::Out};
            if (m.at(next_y).at(next_x) == '#') return {current.x, current.y, Direction::Left};
            return {next_x, next_y, Direction::Down};
        case Direction::Left:
            next_x = current.x - 1;
            if (next_x < 0) return {next_x, next_y, Direction::Out};
            if (m.at(next_y).at(next_x) == '#') return {current.x, current.y, Direction::Up};
            return {next_x, next_y, Direction::Left};
        case Direction::Right:
            next_x = current.x + 1;
            if (next_x >= m.at(next_y).size()) return {next_x, next_y, Direction::Out};
            if (m.at(next_y).at(next_x) == '#') return {current.x, current.y, Direction::Down};
            return {next_x, next_y, Direction::Right};
        default:
            assert(false);
    }
}


int count_x(const std::vector<std::string>& m) {
    int result = 0;
    for (const auto& s: m) {
        for (auto c: s) {
            if (c == 'X') ++result;
        }
    }
    return result;
}


std::pair<bool, std::vector<std::string>> run_simulation(const std::vector<std::string>& m, const Movement& start) {
    std::vector<std::string> result {m};

    std::map<std::pair<int,int>, std::set<Direction>> visits {};
    Movement current {start};

    while(true) {
        result.at(current.y).at(current.x) = 'X';
        std::pair<int, int> key {current.x, current.y};
        if (visits[key].contains(current.d)) {
            return {true, result};
        }
        visits[key].insert(current.d);

        auto next = advance_movement(current, result);
        if (next.d == Direction::Out) {
            return {false, result};
        }
        current = next;
    }
}


int main() {
    std::filesystem::path f {"input_data/input.txt"};
    assert(exists(f));
    assert(is_regular_file(f));
    std::ifstream ifs {f};

    std::vector<std::string> m {};

    Movement start {-1, -1, Direction::Unknown};

    int y = 0;
    std::string line;
    
    while(getline(ifs, line)) {
        if (start.d != Direction::Unknown) {
            m.push_back(line);
            ++y;
            continue;
        }

        auto detected = detect_movement(line, y);
        if (detected.d != Direction::Unknown) {
            start = detected;
            line.at(start.x) = '.';
        }

        m.push_back(line);
        ++y;
    }

    for (auto s: m) {
        std::cout << s << "\n";
    }

    std::cout << "\n" << start << "\n";

    
    int count_loop_positions = 0;

    auto [exploration_is_loop, exploration_m] = run_simulation(m, start);

    for (int y = 0; y < m.size(); ++y) {
        std::cout << y << "\n";
        for (int x = 0; x < m.at(y).size(); ++x) {
            if (y == start.y && x == start.x) continue;
            if (exploration_m.at(y).at(x) != 'X') continue;
            
            // alter map
            m.at(y).at(x) = '#';

            auto [is_loop, result] = run_simulation(m, start);
            if (is_loop) count_loop_positions++;
            
            // restore map
            m.at(y).at(x) = '.';
        }
    }

    std::cout << "Result: " << count_loop_positions << "\n";

    return 0;
}

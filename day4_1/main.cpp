#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/Utils.hpp"

const std::string pattern = "MAS";

inline bool check_letter(std::vector<std::string>& lines, int i, int j, char target) {
    if (j < 0 || i < 0 || i >= lines.size()) return false;
    auto& line = lines.at(i);
    if (j >= line.size()) return false;
    return line.at(j) == target;
}

bool check_direction(std::vector<std::string>& lines, int i, int j, std::pair<int, int>& direction) {
    for (auto& letter : pattern) {
        i += direction.first;
        j += direction.second;
        if (!check_letter(lines, i, j, letter)) return false;
    }
    return true;
}

int main() {
    std::ifstream file("../day4_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    int result = 0;
    std::string line;
    std::vector<std::string> lines;
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},
        {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
    };
    while (std::getline(file, line)) {
        lines.push_back(std::move(line));
    }
    for (int i = 0; i < lines.size(); ++i) {
        auto& line = lines.at(i);
        for (int j = 0; j < line.size(); ++j) {
            if (line.at(j) != 'X') continue;
            for (auto& direction : directions) {
                if (check_direction(lines, i, j, direction)) ++result;
            }
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
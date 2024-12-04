#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/Utils.hpp"

inline bool check_letter(std::vector<std::string>& lines, int i, int j, char target) {
    if (j < 0 || i < 0 || i >= lines.size()) return false;
    auto& line = lines.at(i);
    if (j >= line.size()) return false;
    return line.at(j) == target;
}

bool check_direction(std::vector<std::string>& lines, int i, int j, std::pair<int, int>& direction, std::string& pattern) {
    for (auto& letter : pattern) {
        i += direction.first;
        j += direction.second;
        if (!check_letter(lines, i, j, letter)) return false;
    }
    return true;
}

int main() {
    std::ifstream file("../day4_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    std::string pattern1 = "AS";
    std::string pattern2 = "AM";
    std::pair<int, int> right = {1, 1};
    std::pair<int, int> left = {1, -1};
    int result = 0;
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(std::move(line));
    }
    auto get_pattern = [&pattern1, &pattern2](char& symbol) -> std::string* {
        return symbol == 'M' ? &pattern1 : symbol == 'S' ? &pattern2 : nullptr;
    };
    for (int i = 0; i < lines.size() - 2; ++i) {
        auto& line = lines.at(i);
        for (int j = 0; j < line.size() - 2; ++j) {
            std::string* pattern = get_pattern(line.at(j));
            if (pattern == nullptr) continue;
            if (!check_direction(lines, i, j, right, *pattern)) continue;
            pattern = get_pattern(line.at(j + 2));
            if (pattern == nullptr) continue;
            if (check_direction(lines, i, j + 2, left, *pattern)) ++result;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
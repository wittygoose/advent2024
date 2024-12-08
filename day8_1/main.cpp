#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day8_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::map<char, std::vector<std::pair<int, int>>> antennas;
    std::vector<std::string> field;
    std::set<int> added;
    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        for (int x = 0; x < line.size(); ++x) {
            char letter = line[x];
            if (letter == '.') continue;
            antennas[letter].push_back(std::make_pair(x, y));
        }
        field.push_back(std::move(line));
        ++y;
    }
    int width = field.at(0).size();
    for (auto& pair : antennas) {
        if (pair.second.size() <= 1) continue;
        for (int i = 0; i < pair.second.size(); ++i) {
            auto& left = pair.second.at(i);
            for (int j = i + 1; j < pair.second.size(); ++j) {
                auto& right = pair.second.at(j);
                int left_x = left.first + (left.first - right.first);
                int left_y = left.second + (left.second - right.second);
                if (utils::is_valid_pos(left_x, left_y, field, width)) {
                    added.insert(utils::get_index(left_x, left_y, width));
                }
                int right_x = right.first + (right.first - left.first);
                int right_y = right.second + (right.second - left.second);
                if (utils::is_valid_pos(right_x, right_y, field, width)) {
                    added.insert(utils::get_index(right_x, right_y, width));
                }
            }
        }
    }
    result = added.size();
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
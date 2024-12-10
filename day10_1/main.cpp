#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "../include/Utils.hpp"

std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

void process(int& x, int& y, std::vector<std::vector<int>>& field, std::set<int>& added, int& width) {
    int target = field.at(y).at(x) + 1;
    for (auto& dir : directions) {
        int new_x = x + dir.first;
        int new_y = y + dir.second;
        if (!utils::is_valid_pos(new_x, new_y, field, width)) continue;
        int& next = field.at(new_y).at(new_x);
        if (next == target) {
            if (next == 9) added.insert(utils::get_index(new_x, new_y, width));
            else process(new_x, new_y, field, added, width);
        }
    }
}

int main() {
    std::ifstream file("../day10_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    int64_t result = 0;
    std::string line;
    std::vector<std::vector<int>> field;
    std::vector<std::pair<int, int>> heads;
    int y = 0;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (int x = 0; x < line.size(); ++x) {
            int digit = utils::char_to_int(line[x]);
            if (digit == 0) heads.push_back(std::make_pair(x, y));
            row.push_back(digit);
        }
        field.push_back(std::move(row));
        ++y;
    }
    int width = field.at(0).size();
    for (auto& pair : heads) {
        std::set<int> added;
        process(pair.first, pair.second, field, added, width);
        result += added.size();
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
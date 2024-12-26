#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "../include/Utils.hpp"

std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

inline bool is_opposite(std::pair<int, int>& left, std::pair<int, int>& right) {
    return left.first + right.first == 0 && left.second + right.second == 0;
}

void process(char& type, int x, int y, int& area, int& perimeter, std::vector<std::string>& field, int& width, std::set<int>& local, std::set<int>& global) {
    for (auto& dir : directions) {
        int new_x = x + dir.first;
        int new_y = y + dir.second;
        if (!utils::is_valid_pos(new_x, new_y, field, width)) continue;
        int index = utils::get_index(new_x, new_y, width);
        if (global.find(index) != global.end()) continue;
        if (field.at(new_y).at(new_x) != type) continue;
        ++area;
        perimeter += 2;
        global.insert(index);
        for (auto& dir2 : directions) {
            if (is_opposite(dir, dir2)) continue;
            int neighbor_x = new_x + dir2.first;
            int neighbor_y = new_y + dir2.second;
            int neighbor_index = utils::get_index(neighbor_x, neighbor_y, width);
            if (local.find(neighbor_index) == local.end()) continue;
            perimeter -= 2;
        }
        local.insert(index);
        process(type, new_x, new_y, area, perimeter, field, width, local, global);
    }
}

int main() {
    std::ifstream file("../day12_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::vector<std::string> field;
    std::set<int> global;
    std::string line;
    while (std::getline(file, line)) {
        field.push_back(std::move(line));
    }
    int width = field.at(0).size();
    for (int y = 0; y < field.size(); ++y) {
        std::string& row = field.at(y);
        for (int x = 0; x < row.size(); ++x) {
            int index = utils::get_index(x, y, width);
            if (global.find(index) != global.end()) continue;
            char type = row.at(x);
            std::set<int> local;
            global.insert(index);
            local.insert(index);
            int area = 1;
            int perimeter = 4;
            process(type, x, y, area, perimeter, field, width, local, global);
            result += area * perimeter;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
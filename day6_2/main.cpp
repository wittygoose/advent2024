#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "../include/Utils.hpp"

std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

inline int get_index(int x, int y, int width) {
    return y * width + x;
}

bool is_valid_pos(int x, int y, std::vector<std::string>& field, int width) {
    return x >= 0 && y >= 0 && x < width && y < field.size();
}

bool is_looped(std::pair<int, int> position, int index, std::vector<std::string>& field, int width) {
    std::set<int> visited;
    while (true) {
        auto& dir = directions.at(index);
        int xNew = position.first + dir.first;
        int yNew = position.second + dir.second;
        if (is_valid_pos(xNew, yNew, field, width)) {
            char& letter = field.at(yNew).at(xNew);
            if (letter == '#') {
                ++index;
                if (index >= directions.size()) index = 0;
            } else {
                position.first = xNew;
                position.second = yNew;
                auto insert = visited.insert(get_index(position.first, position.second, width) + index * 1000000);
                if (!insert.second) {
                    return true;
                }
            }
        } else {
            break;
        }
    }
    return false;
}

int main() {
    std::ifstream file("../day6_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    int result = 0;
    std::vector<std::string> field;
    std::pair<int, int> position;
    std::set<int> visited;
    bool found = false;
    int index = 0;
    int width;
    int y = 0;
    std::string line;
    while (std::getline(file, line)) {
        if (!found) {
            for (int i = 0; i < line.size(); ++i) {
                char& letter = line.at(i);
                if (letter == '^') {
                    position.first = i;
                    position.second = y;
                    width = line.size();
                    visited.insert(get_index(position.first, position.second, width));
                    found = true;
                    break;
                }
            }
        }
        field.push_back(std::move(line));
        ++y;
    }
    while (true) {
        auto& dir = directions.at(index);
        int xNew = position.first + dir.first;
        int yNew = position.second + dir.second;
        if (is_valid_pos(xNew, yNew, field, width)) {
            char& letter = field.at(yNew).at(xNew);
            if (letter == '#') {
                ++index;
                if (index >= directions.size()) index = 0;
            } else {
                auto insert = visited.insert(get_index(xNew, yNew, width));
                if (insert.second) {
                    field.at(yNew).at(xNew) = '#';
                    if (is_looped(position, index, field, width)) ++result;
                    field.at(yNew).at(xNew) = '.';
                }
                position.first = xNew;
                position.second = yNew;
            }
        } else {
            break;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
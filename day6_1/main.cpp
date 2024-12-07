#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "../include/Utils.hpp"

inline int get_index(int x, int y, int width) {
    return y * width + x;
}

int main() {
    std::ifstream file("../day6_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    int result = 0;
    std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::set<int> visited;
    std::vector<std::string> field;
    std::pair<int, int> position;
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
                    visited.insert(get_index(i, y, width));
                    found = true;
                    break;
                }
            }
        }
        field.push_back(std::move(line));
        ++y;
    }
    while (true) {
        std::pair<int, int>& dir = directions.at(index);
        int xNew = position.first + dir.first;
        int yNew = position.second + dir.second;
        if (xNew >= 0 && yNew >= 0 && xNew < width && yNew < field.size()) {
            char& letter = field.at(yNew).at(xNew);
            if (letter == '#') {
                ++index;
                if (index >= directions.size()) index = 0;
            } else {
                position.first = xNew;
                position.second = yNew;
                visited.insert(get_index(xNew, yNew, width));
            }
        } else {
            break;
        }
    }
    file.close();
    result = visited.size();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
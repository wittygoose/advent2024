#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "../include/Utils.hpp"

bool add_antinodes(std::pair<int, int>& pos, int x_dif, int y_dif, std::set<int>& added, std::vector<std::string>& field, int& width) {
    pos.first += x_dif;
    pos.second += y_dif;
    if (utils::is_valid_pos(pos.first, pos.second, field, width)) {
        added.insert(utils::get_index(pos.first, pos.second, width));
        return true;
    }
    return false;
}

int main() {
    std::ifstream file("../day8_2/input.txt");
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
            added.insert(utils::get_index(x, y, line.size()));
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
                int x_dif = left.first - right.first;
                int y_dif = left.second - right.second;
                std::pair<int, int> pos = left;
                while (add_antinodes(pos, x_dif, y_dif, added, field, width));
                x_dif = right.first - left.first;
                y_dif = right.second - left.second;
                pos = right;
                while (add_antinodes(pos, x_dif, y_dif, added, field, width));
            }
        }
    }
    result = added.size();
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
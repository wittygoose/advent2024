#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "../include/Utils.hpp"

std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

inline bool is_used(int x, int y, std::vector<std::vector<int>>& field_result) {
    return field_result.at(y).at(x) != 0;
}

void process(char& type, int x, int y, int& area, int id, std::vector<std::string>& field, int& width, std::vector<std::vector<int>>& field_result, Range& x_range, Range& y_range) {
    for (auto& dir : directions) {
        int new_x = x + dir.first;
        int new_y = y + dir.second;
        if (!utils::is_valid_pos(new_x, new_y, field, width)) continue;
        if (is_used(new_x, new_y, field_result)) continue;
        if (field.at(new_y).at(new_x) != type) continue;
        ++area;
        field_result.at(new_y).at(new_x) = id;
        x_range.update(new_x);
        y_range.update(new_y);
        process(type, new_x, new_y, area, id, field, width, field_result, x_range, y_range);
    }
}

bool continues_side(std::map<int, std::map<int, bool>>& data, int pos1, int pos2, bool inside) {
    auto it1 = data.find(pos1 - 1);
    if (it1 == data.end()) return false;
    auto& data2 = (*it1).second;
    auto it2 = data2.find(pos2);
    if (it2 == data2.end()) return false;
    return (*it2).second == inside;
}

int calculate_sides(int id, std::vector<std::vector<int>>& field_result, Range& x_range, Range& y_range, int width) {
    int result = 0;
    std::map<int, std::map<int, bool>> prev_y_by_x;
    std::map<int, std::map<int, bool>> prev_x_by_y;
    bool inside = false;
    // vertical
    for (int x = x_range.min; x <= x_range.max + 1; ++x) {
        for (int y = y_range.min; y <= y_range.max + 1; ++y) {
            bool is_inside = utils::is_valid_pos(x, y, field_result, width) && field_result.at(y).at(x) == id;
            if (is_inside) {
                if (!inside) {
                    inside = true;
                    if (!continues_side(prev_y_by_x, x, y, true)) ++result;
                    prev_y_by_x[x][y] = true;
                }
            } else {
                if (inside) {
                    inside = false;
                    if (!continues_side(prev_y_by_x, x, y, false)) ++result;
                    prev_y_by_x[x][y] = false;
                }
            }
        }
    }
    inside = false;
    // horizontal
    for (int y = y_range.min; y <= y_range.max + 1; ++y) {
        for (int x = x_range.min; x <= x_range.max + 1; ++x) {
            bool is_inside = utils::is_valid_pos(x, y, field_result, width) && field_result.at(y).at(x) == id;
            if (is_inside) {
                if (!inside) {
                    inside = true;
                    if (!continues_side(prev_x_by_y, y, x, true)) ++result;
                    prev_x_by_y[y][x] = true;
                }
            } else {
                if (inside) {
                    inside = false;
                    if (!continues_side(prev_x_by_y, y, x, false)) ++result;
                    prev_x_by_y[y][x] = false;
                }
            }
        }
    }
    return result;
}

int main() {
    std::ifstream file("../day12_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::vector<std::string> field;
    std::vector<std::vector<int>> field_result;
    std::string line;
    while (std::getline(file, line)) {
        field_result.push_back(std::vector<int>(line.size(), 0));
        field.push_back(std::move(line));
    }
    int width = field.at(0).size();
    int id = 1;
    for (int y = 0; y < field.size(); ++y) {
        std::string& row = field.at(y);
        for (int x = 0; x < row.size(); ++x) {
            if (is_used(x, y, field_result)) continue;
            char type = row.at(x);
            field_result.at(y).at(x) = id;
            Range x_range;
            x_range.update(x);
            Range y_range;
            y_range.update(y);
            int area = 1;
            process(type, x, y, area, id, field, width, field_result, x_range, y_range);
            int sides = calculate_sides(id, field_result, x_range, y_range, width);
            result += area * sides;
            ++id;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
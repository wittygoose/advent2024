#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day1_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint32_t digit = 0;
    bool digit_finished = false;
    bool right = false;
    int total_lines = 0;
    std::vector<uint32_t> left_values;
    std::vector<uint32_t> right_values;
    std::string line;
    while (std::getline(file, line)) {
        ++total_lines;
        right = false;
        for (int i = 0; i < line.size(); ++i) {
            char letter = line[i];
            if (std::isdigit(letter)) {
                utils::accumulate_digit(digit, letter);
                if (i + 1 == line.size()) digit_finished = true;
            } else {
                digit_finished = true;
                i += 2; // skip separator
            }
            if (digit_finished) {
                if (!right) left_values.push_back(digit);
                else right_values.push_back(digit);
                right = !right;
                digit = 0;
                digit_finished = false;
            }
        }
    }
    std::sort(left_values.begin(), left_values.end());
    std::sort(right_values.begin(), right_values.end());
    uint32_t result = 0;
    for (int i = 0; i < total_lines; ++i) {
        uint32_t& left = left_values.at(i);
        uint32_t& right = right_values.at(i);
        uint32_t distance = left > right ? left - right : right - left;
        result += distance;
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
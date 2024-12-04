#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day1_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint32_t result = 0;
    std::vector<uint32_t> left_values;
    std::map<uint32_t, uint32_t> right_values_count;
    uint32_t digit = 0;
    bool digit_finished = false;
    bool right = false;
    std::string line;
    while (std::getline(file, line)) {
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
                else right_values_count[digit]++;
                right = !right;
                digit = 0;
                digit_finished = false;
            }
        }
    }
    for (uint32_t& value : left_values) {
        result += value * right_values_count[value];
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include "../include/Utils.hpp"

const int max_dif = 3;

bool validate_digits(int& left, int& right, int& current_pattern, int& pattern) {
    pattern = right > left ? 1 : right < left ? -1 : 0;
    if (pattern == 0 || (current_pattern != 0 && current_pattern != pattern)) {
        return false;
    }
    int dif = pattern > 0 ? right - left : left - right;
    if (dif > max_dif) { 
        return false;
    }
    if (current_pattern == 0) current_pattern = pattern;
    return true;
}

int main() {
    std::ifstream file("../day2_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    int result = 0;
    int digit = 0;
    int prev_digit = 0;
    int current_pattern = 0;
    bool digit_finished = false;
    bool is_first_digit = false;
    bool fail = false;
    std::string line;
    while (std::getline(file, line)) {
        digit_finished = false;
        digit = 0;
        prev_digit = 0;
        current_pattern = 0;
        is_first_digit = true;
        fail = false;
        for (int i = 0; i < line.size(); ++i) {
            char letter = line[i];
            if (std::isdigit(letter)) {
                utils::accumulate_digit(digit, letter);
                if (i + 1 == line.size()) digit_finished = true;
            } else {
                digit_finished = true;
            }
            if (digit_finished) {
                digit_finished = false;
                if (is_first_digit) {
                    is_first_digit = false;
                    prev_digit = digit;
                    digit = 0;
                } else {
                    int pattern;
                    if (!validate_digits(prev_digit, digit, current_pattern, pattern)) {
                        fail = true;
                        break;
                    }
                    prev_digit = digit;
                    digit = 0;
                }
            }
        }
        if (!fail) ++result;
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
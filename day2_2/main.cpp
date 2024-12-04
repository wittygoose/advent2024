#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

int process_digits(std::vector<int>& digits, int ignore_index) {
    int prev_digit = -1;
    int current_pattern = 0;
    int pattern;
    for (int i = 0; i < digits.size(); ++i) {
        if (ignore_index == i) continue;
        int& digit = digits.at(i);
        if (prev_digit < 0) {
            prev_digit = digit;
            continue;
        }
        if (!validate_digits(prev_digit, digit, current_pattern, pattern)) {
            return i;
        }
        prev_digit = digit;
    }
    return -1;
}

int main() {
    std::ifstream file("../day2_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    int result = 0;
    int digit = 0;
    bool digit_finished = false;
    std::string line;
    while (std::getline(file, line)) {
        digit_finished = false;
        digit = 0;
        std::vector<int> digits;
        for (int i = 0; i < line.size(); ++i) {
            char letter = line[i];
            if (std::isdigit(letter)) {
                utils::accumulate_digit(digit, letter);
                if (i + 1 == line.size()) digit_finished = true;
            } else {
                digit_finished = true;
            }
            if (digit_finished) {
                digits.push_back(digit);
                digit_finished = false;
                digit = 0;
            }
        }
        int failed_index = process_digits(digits, -1);
        if (failed_index == -1 
            || process_digits(digits, failed_index) == -1 
            || process_digits(digits, failed_index - 1) == -1
            || (failed_index == 2 && process_digits(digits, 0) == -1)) {
            ++result;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include "../include/Utils.hpp"

uint64_t concat_digits(uint64_t first, uint64_t second) {
    std::string first_str = std::to_string(first);
    std::string second_str = std::to_string(second);
    return std::stoull(first_str + second_str);
}

bool is_valid(uint64_t start, uint64_t result, std::vector<uint64_t>& digits, int index) {
    if (start > result) return false;
    if (index >= digits.size()) return result == start;
    return is_valid(start + digits[index], result, digits, index + 1) || is_valid(start * digits[index], result, digits, index + 1)
            || is_valid(concat_digits(start, digits[index]), result, digits, index + 1);
}

int main() {
    std::ifstream file("../day7_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    uint64_t sum = 0;
    uint64_t digit = 0;
    bool digit_finished = false;
    bool digit_started = false;
    std::string line;
    while (std::getline(file, line)) {
        bool colon_found = false;
        std::vector<uint64_t> digits;
        for (int i = 0; i < line.size(); ++i) {
            char letter = line[i];
            if (std::isdigit(letter)) {
                digit_started = true;
                utils::accumulate_digit(digit, letter);
                if (i + 1 == line.size()) digit_finished = true;
            } else {
                if (!colon_found && letter == ':') colon_found = true;
                if (digit_started) digit_finished = true;
            }
            if (digit_finished) {
                if (colon_found) {
                    sum = digit;
                    colon_found = false;
                } else {
                    digits.push_back(digit);
                }
                digit = 0;
                digit_started = digit_finished = false;
            }
        }
        uint64_t first = digits[0];
        uint64_t second = digits[1];
        if (is_valid(first + second, sum, digits, 2) || is_valid(first * second, sum, digits, 2)
            || is_valid(concat_digits(first, second), sum, digits, 2)) {
            result += sum;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
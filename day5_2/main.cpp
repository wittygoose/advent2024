#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "../include/Utils.hpp"

std::vector<int> collect_digits(std::string& line) {
    std::vector<int> result;
    int digit = 0;
    bool digit_finished = false;
    for (int i = 0; i < line.size(); ++i) {
        char letter = line[i];
        if (std::isdigit(letter)) {
            utils::accumulate_digit(digit, letter);
            if (i + 1 == line.size()) digit_finished = true;
        } else {
            digit_finished = true;
        }
        if (digit_finished) {
            result.push_back(digit);
            digit = 0;
            digit_finished = false;
        }
    }
    return result;
}

int main() {
    std::ifstream file("../day5_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    int result = 0;
    bool updates = false;
    std::string line;
    std::map<int, std::vector<int>> after_by_digit;
    while (std::getline(file, line)) {
        if (line.size() == 0) {
            updates = true;
            continue;
        }
        std::vector<int> digits = collect_digits(line);
        if (!updates) {
            after_by_digit[digits[0]].push_back(digits[1]);
        } else {
            bool correct = true;
            for (int i = 0; i < digits.size() - 1; ++i) {
                std::vector<int>& after = after_by_digit[digits[i]];
                if (std::find(after.begin(), after.end(), digits[i + 1]) == after.end()) {
                    std::swap(digits[i], digits[i + 1]);
                    correct = false;
                    i = -1;
                }
            }
            if (!correct) result += digits[(digits.size() - 1) / 2];
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day3_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    int result = 0;
    const std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::string line;
    while (std::getline(file, line)) {
        auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto end = std::sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            const std::smatch& match = *it;
            int left = std::stoi(match[1].str());
            int right = std::stoi(match[2].str());
            result += left * right;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
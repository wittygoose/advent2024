#include <iostream>
#include <fstream>
#include <vector>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day9_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    int64_t result = 0;
    std::string line;
    bool is_file = true;
    int id = 0;
    while (std::getline(file, line)) {
        std::vector<int> layout;
        for (int x = 0; x < line.size(); ++x) {
            int digit = utils::char_to_int(line[x]);
            int value = is_file ? id++ : -1;
            is_file = !is_file;
            while (digit-- > 0) layout.push_back(value);
        }
        int left = 0;
        int right = layout.size() - 1;
        while (left != right) {
            int& rvalue = layout.at(right);
            if (rvalue != -1) {
                int& lvalue = layout.at(left);
                if (lvalue == -1) {
                    std::swap(rvalue, lvalue);
                    --right;
                }
                ++left;
            } else {
                --right;
            }
        }
        for (int i = 0; i < layout.size(); ++i) {
            int& value = layout.at(i);
            if (value < 0) break;
            result += value * i;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
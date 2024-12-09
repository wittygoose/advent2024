#include <iostream>
#include <fstream>
#include <vector>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day9_2/input.txt");
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
        int right_block = 0;
        int right_block_start = -1;
        int left_block_start = -1;
        bool search = false;
        while (right > 0) {
            if (!search) {
                int& rvalue = layout.at(right);
                if (rvalue != -1) {
                    if (right_block_start == -1) {
                        right_block_start = right;
                        right_block = rvalue;
                        --right;
                    } else if (right_block == rvalue) {
                        --right;
                    } else {
                        search = true;
                    }
                } else {
                    if (right_block_start != -1) search = true;
                    else --right;
                }
            } else {
                if (left_block_start != -1 
                    && (left - left_block_start == right_block_start - right || left_block_start >= right)) {
                    if (left - left_block_start == right_block_start - right && left_block_start < right) {
                        while (right_block_start != right) {
                            std::swap(layout.at(right_block_start), layout.at(left_block_start));
                            --right_block_start;
                            ++left_block_start;
                        }
                    }
                    left = 0;
                    left_block_start = right_block_start = -1;
                    search = false;
                } else {
                    if (left > right) {
                        left = 0;
                        left_block_start = right_block_start = -1;
                        search = false;
                    } else {
                        int& lvalue = layout.at(left);
                        if (lvalue == -1) {
                            if (left_block_start == -1) left_block_start = left;
                            ++left;
                        } else {
                            left_block_start = -1;
                            ++left;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < layout.size(); ++i) {
            int& value = layout.at(i);
            if (value < 0) continue;
            result += value * i;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
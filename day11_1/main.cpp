#include <iostream>
#include <fstream>
#include <list>
#include "../include/Utils.hpp"

const uint64_t mult = 2024;

inline std::string multiply(std::string& str) {    
    return std::to_string(std::stoull(str) * mult);
}

int main() {
    std::ifstream file("../day11_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::string word;
    std::list<std::string> stones;
    while (file >> word) {
        stones.push_back(word);
    }
    int blinks = 25;
    while (blinks--) {
        for (auto it = stones.begin(); it != stones.end();) {
            auto& str = *it;
            if (str.size() == 1) {
                if (str.at(0) == '0') str = '1';
                else str = multiply(str);
            } else if (str.size() % 2 == 0) {
                int mid = str.size() / 2;
                std::string left = str.substr(0, mid);
                std::string right = std::to_string(std::stoull(str.substr(mid, mid)));
                str = right;
                stones.insert(it, left);
            } else {
                str = multiply(str);
            }
            ++it;
        }
    }
    result = stones.size();
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
#include <iostream>
#include <fstream>
#include <map>
#include "../include/Utils.hpp"

const uint64_t mult = 2024;

inline std::string multiply(std::string& str) {    
    return std::to_string(std::stoull(str) * mult);
}

int main() {
    std::ifstream file("../day11_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::string word;
    std::map<std::string, int64_t> first;
    std::map<std::string, int64_t> second;
    bool use_first = true;
    while (file >> word) {
        first[word]++;
    }
    int blinks = 75;
    while (blinks--) {
        auto& current_map = use_first ? first : second;
        auto& next_map = use_first ? second : first;
        next_map.clear();
        use_first = !use_first;
        for (auto it = current_map.begin(); it != current_map.end(); ++it) {
            auto& pair = *it;
            auto str = pair.first;
            if (str.size() == 1) {
                if (str.at(0) == '0') next_map["1"] += pair.second;
                else next_map[multiply(str)] += pair.second;
            } else if (str.size() % 2 == 0) {
                int mid = str.size() / 2;
                std::string left = str.substr(0, mid);
                next_map[left] += pair.second;
                std::string right = std::to_string(std::stoull(str.substr(mid, mid)));
                next_map[right] += pair.second;
            } else {
                next_map[multiply(str)] += pair.second;
            }
        }
    }
    auto& result_map = use_first ? first : second;
    for (auto it = result_map.begin(); it != result_map.end(); ++it) {
        auto pair = *it;
        result += pair.second;
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}
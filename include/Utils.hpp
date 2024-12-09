#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <vector>

struct Performance {
    Performance() {}

    ~Performance() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<float>(end - start).count();
        std::cout << "time: " << std::to_string(duration) << " seconds" << std::endl;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
};

namespace utils {
    template<typename T>
    void accumulate_digit(T& digit, char ch) {
        static_assert(std::is_integral<T>::value, "accumulate_digit can only be used with integral types");
        digit = digit * 10 + (ch - '0');
    }

    int char_to_int(char ch) {
        return ch - '0';
    }

    // unique index in 2d vector
    inline int get_index(int x, int y, int width) {
        return y * width + x;
    }

    // x y in bounds of 2d vector
    template<typename T>
    bool is_valid_pos(int x, int y, std::vector<T>& field, int width) {
        return x >= 0 && y >= 0 && x < width && y < field.size();
    }

    void print_field(std::vector<std::string>& field) {
        for (auto& line : field) {
            std::cout << line;
            std::cout << std::endl;
        }
    }
}
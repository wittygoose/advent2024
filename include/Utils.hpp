#pragma once

#include <iostream>
#include <string>
#include <chrono>

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
}
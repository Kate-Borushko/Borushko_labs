#pragma once
#include <iostream>
#include <cstdint>

template <typename T>
T getCorrect(T& x)
{
    while ((std::cin >> x).fail() || x <= 0)
    {
        std::cout << "Try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}

uint32_t getInRange(uint8_t x1, uint8_t x2);
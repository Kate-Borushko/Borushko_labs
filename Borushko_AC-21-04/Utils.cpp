#include "Station.h"
#include <iostream>
#include "Utils.h"



uint32_t getInRange(uint8_t x1, uint8_t x2)
{
    uint32_t x;
    while ((std::cin >> x).fail() || x1 > x || x > x2)
    {
        std::cout << "Try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}
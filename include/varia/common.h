/*
Dependencies, containers, and helper functions common to most code in Varia.
*/
#pragma once
#include <iostream>
#include <vector>
#include <cmath>

namespace varia {

//////////////////////////////////////////////////

template <class T>
void print(T const& obj) {
    std::cout << obj << std::endl;
}

//////////////////////////////////////////////////

} // namespace varia

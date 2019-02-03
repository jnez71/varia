/*
Description.
*/
#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

namespace varia {

//////////////////////////////////////////////////

using Idx = uint;
using Real = double;
using Str = std::string;

template <class T>
using Seq = std::vector<T>;

template <class T>
using Dict = std::map<Str, T>;

//////////////////////////////////////////////////

template <class T>
void print(T const& obj) {
    std::cout << obj << std::endl;
}

//////////////////////////////////////////////////

} // namespace varia

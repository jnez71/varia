/*
Dependencies, aliases, constants, containers, and simple functions common to this C++ code-base.
*/
#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <chrono>
#include <random>

namespace varia {

////////////////////////////////////////////////// ALIASES / CONSTANTS

using Real = double;

/////

static Real constexpr INF = std::numeric_limits<Real>::infinity();
static Real constexpr EPS = std::numeric_limits<Real>::epsilon();

////////////////////////////////////////////////// SIMPLE FUNCTIONS

template <class T>
inline void print(T const& obj) {
    std::cout << obj << std::endl;
}

/////////////////////////

inline Real query_realtime() {
    return 1e-6*std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

/////////////////////////

inline Real random_uniform() {
    static std::default_random_engine random_engine(1e6*query_realtime());
    static std::uniform_real_distribution<Real> uniform(-1.0, 1.0);
    return uniform(random_engine);
}

//////////////////////////////////////////////////

} // namespace varia

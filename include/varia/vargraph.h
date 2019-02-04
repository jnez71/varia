/*
Description.
*/
#pragma once
#include <varia/common.h>

namespace varia {
class Var;

//////////////////////////////////////////////////

class VarGraph {
private:
    friend class Var;

    struct Dep {
        uint const arity;
        uint const x;
        double const d_dx;
        uint const y;
        double const d_dy;
        Dep(uint arity, uint x, double d_dx, uint y, double d_dy) :
            arity(arity), x(x), d_dx(d_dx), y(y), d_dy(d_dy) {};
    };
    std::vector<Dep> deps;

    uint new_nullary();
    uint new_unary(uint x, double d_dx);
    uint new_binary(uint x, double d_dx, uint y, double d_dy);

public:
    VarGraph() =default;
};

//////////////////////////////////////////////////

} // namespace varia

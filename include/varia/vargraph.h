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
        Idx const x;
        Real const d_dx;
        Idx const y;
        Real const d_dy;
        Dep(Idx x, Real d_dx, Idx y, Real d_dy) :
            x(x), d_dx(d_dx), y(y), d_dy(d_dy) {};
    };
    Seq<Dep> deps;

    Idx new_nullary();
    Idx new_unary(Idx x, Real d_dx);
    Idx new_binary(Idx x, Real d_dx, Idx y, Real d_dy);

public:
    VarGraph() =default;
};

//////////////////////////////////////////////////

} // namespace varia

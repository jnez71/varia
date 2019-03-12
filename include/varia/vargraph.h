/*
Class for storing the graph of dependencies between various Var objects.
The graph is stored as a dynamic array of index-"pointers". The graph
is manipulated by private methods called from the Var class.
*/
#pragma once
#include <varia/common.h>

namespace varia {
class Var;

//////////////////////////////////////////////////

class VarGraph {
private:
    friend class Var;
    static uint expected_size;

    struct Dep {
        uint const arity;
        uint const x;
        double const d_dx;
        uint const y;
        double const d_dy;
    };
    std::vector<Dep> deps;

    uint new_nullary();
    uint new_unary(uint x, double d_dx);
    uint new_binary(uint x, double d_dx, uint y, double d_dy);

public:
    VarGraph();
    ~VarGraph();
    static void expect_size(uint n) {expected_size = n;}
    inline uint size() const {return deps.size();}
};

//////////////////////////////////////////////////

} // namespace varia

/*
Implementation of vargraph.h
*/
#include <varia/vargraph.h>

namespace varia {

//////////////////////////////////////////////////

uint VarGraph::new_nullary() {
    uint n = deps.size();
    deps.push_back(Dep(n, 0, n, 0));
    return n;
}

////

uint VarGraph::new_unary(uint x, double d_dx) {
    uint n = deps.size();
    deps.push_back(Dep(x, d_dx, n, 0));
    return n;
}

////

uint VarGraph::new_binary(uint x, double d_dx, uint y, double d_dy) {
    uint n = deps.size();
    deps.push_back(Dep(x, d_dx, y, d_dy));
    return n;
}

//////////////////////////////////////////////////

} // namespace varia

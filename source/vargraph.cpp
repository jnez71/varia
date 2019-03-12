/*
Implementation of vargraph.h
*/
#include <varia/vargraph.h>

namespace varia {

//////////////////////////////////////////////////

uint VarGraph::expected_size = 2;

////

VarGraph::VarGraph() {
    deps.reserve(expected_size);
}

////

VarGraph::~VarGraph() {
    if(deps.size() > expected_size)
        expected_size = deps.size();
}

//////////////////////////////////////////////////

uint VarGraph::new_nullary() {
    uint n = deps.size();
    deps.push_back(Dep{0, n, 0.0, n, 0.0});
    return n;
}

////

uint VarGraph::new_unary(uint x, double d_dx) {
    uint n = deps.size();
    deps.push_back(Dep{1, x, d_dx, n, 0.0});
    return n;
}

////

uint VarGraph::new_binary(uint x, double d_dx, uint y, double d_dy) {
    uint n = deps.size();
    deps.push_back(Dep{2, x, d_dx, y, d_dy});
    return n;
}

//////////////////////////////////////////////////

} // namespace varia

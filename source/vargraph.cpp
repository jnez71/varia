/*
Implementation of vargraph.h
*/
#include <varia/vargraph.h>

namespace varia {

//////////////////////////////////////////////////

Idx VarGraph::new_nullary() {
    Idx n = deps.size();
    deps.push_back(Dep(n, 0, n, 0));
    return n;
}

////

Idx VarGraph::new_unary(Idx x, Real d_dx) {
    Idx n = deps.size();
    deps.push_back(Dep(x, d_dx, n, 0));
    return n;
}

////

Idx VarGraph::new_binary(Idx x, Real d_dx, Idx y, Real d_dy) {
    Idx n = deps.size();
    deps.push_back(Dep(x, d_dx, y, d_dy));
    return n;
}

//////////////////////////////////////////////////

} // namespace varia

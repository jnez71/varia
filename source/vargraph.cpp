/*
Implementation of vargraph.h
*/
#include <varia/vargraph.h>

namespace varia {

//////////////////////////////////////////////////

std::vector<std::vector<VarGraph::Dep>> VarGraph::objpool;

////

VarGraph::VarGraph() {
    if(objpool.size()) {
        deps = std::move(objpool.back());
        objpool.pop_back();
    }
}

////

VarGraph::~VarGraph() {
    deps.clear();
    objpool.emplace_back(std::move(deps));
}

//////////////////////////////////////////////////

uint VarGraph::new_nullary() {
    uint n = deps.size();
    deps.emplace_back(0, n, 0.0, n, 0.0);
    return n;
}

////

uint VarGraph::new_unary(uint x, double d_dx) {
    uint n = deps.size();
    deps.emplace_back(1, x, d_dx, n, 0.0);
    return n;
}

////

uint VarGraph::new_binary(uint x, double d_dx, uint y, double d_dy) {
    uint n = deps.size();
    deps.emplace_back(2, x, d_dx, y, d_dy);
    return n;
}

//////////////////////////////////////////////////

void VarGraph::diagnose() {
    std::cout << "====================" << std::endl;
    std::cout << "VarGraph Diagnostics" << std::endl;
    std::cout << "objpool: [";
    for(uint i=0; i<objpool.size(); ++i) {
        std::cout << objpool[i].capacity();
        if(i < objpool.size()-1) {
            std::cout << " | ";
        }
    }
    std::cout << ']' << std::endl;
    std::cout << "====================" << std::endl;
}

//////////////////////////////////////////////////

} // namespace varia

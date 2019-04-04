/*
Class for storing the graph of dependencies between various Var objects.
The graph is stored as a dynamic array of index-"pointers". The graph
is manipulated by private methods called from the Var class.
*/
#pragma once
#include "varia/common.h"

namespace varia {

////////////////////////////////////////////////// DECLARATIONS

class VarGraph {
private:
    friend class Var;

    struct Dep {
        uint const arity;
        uint const x;
        Real const d_dx;
        uint const y;
        Real const d_dy;
        Dep(uint arity, uint x, Real d_dx, uint y, Real d_dy) :
            arity(arity), x(x), d_dx(d_dx), y(y), d_dy(d_dy) {}
    };

    static std::vector<std::vector<Dep>> objpool;
    std::vector<Dep> deps;

    uint new_nullary();
    uint new_unary(uint x, Real d_dx);
    uint new_binary(uint x, Real d_dx, uint y, Real d_dy);

public:
    VarGraph();
    ~VarGraph();
    static void diagnose();
    uint size() const {return deps.size();}
};

////////////////////////////////////////////////// DEFINITIONS

inline std::vector<std::vector<VarGraph::Dep>> VarGraph::objpool;

/////

inline VarGraph::VarGraph() {
    if(objpool.size()) {
        deps = std::move(objpool.back());
        objpool.pop_back();
    }
}

/////

inline VarGraph::~VarGraph() {
    deps.clear();
    objpool.emplace_back(std::move(deps));
}

/////////////////////////

inline uint VarGraph::new_nullary() {
    uint n = deps.size();
    deps.emplace_back(0, n, 0.0, n, 0.0);
    return n;
}

/////

inline uint VarGraph::new_unary(uint x, Real d_dx) {
    uint n = deps.size();
    deps.emplace_back(1, x, d_dx, n, 0.0);
    return n;
}

/////

inline uint VarGraph::new_binary(uint x, Real d_dx, uint y, Real d_dy) {
    uint n = deps.size();
    deps.emplace_back(2, x, d_dx, y, d_dy);
    return n;
}

/////////////////////////

inline void VarGraph::diagnose() {
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

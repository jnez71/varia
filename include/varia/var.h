/*
Description.
*/
#pragma once
#include <varia/common.h>
#include <varia/vargraph.h>

namespace varia {

//////////////////////////////////////////////////

class Var {
private:
    VarGraph* vgp;
    Idx idx;
    Real val;

    Var(VarGraph* vgp, Idx idx, Real val);

public:
    Var(VarGraph* vgp, Real val);
    Var(Var const& other);
    Var& operator=(Var const& other);

    inline Real value() const {return val;}
    Real derivative() const;

    Var sin() const;
    Var exp() const;

    Var operator+(Var const& other) const;
    Var operator*(Var const& other) const;
};

//////////////////////////////////////////////////

} // namespace varia

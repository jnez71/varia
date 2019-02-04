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
    uint idx;
    double val;

    Var(VarGraph* vgp, uint idx, double val);

public:
    Var(VarGraph* vgp, double val);
    Var(Var const& other);
    Var& operator=(Var const& other);

    inline double value() const {return val;}
    double derivative() const;

    Var sin() const;
    Var exp() const;

    Var operator+(Var const& other) const;
    Var operator*(Var const& other) const;
};

//////////////////////////////////////////////////

} // namespace varia

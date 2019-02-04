/*
Implementation of var.h
*/
#include <varia/var.h>

namespace varia {

//////////////////////////////////////////////////

Var::Var(VarGraph* vgp, uint idx, double val) :
    vgp(vgp),
    idx(idx),
    val(val) {
}

//////////////////////////////////////////////////

Var::Var(VarGraph* vgp, double val) :
    vgp(vgp),
    idx(vgp->new_nullary()),
    val(val) {
}

////

Var::Var(Var const& other) {
    vgp = other.vgp;
    idx = other.idx;
    val = other.val;
}

////

Var& Var::operator=(Var const& other) {
    vgp = other.vgp;
    idx = other.idx;
    val = other.val;
}

//////////////////////////////////////////////////

std::map<Var const*, double> Var::gradient() const {
    std::map<Var const*, double> g;
    g[this] = 1;
    return g;//???
}

//////////////////////////////////////////////////

Var Var::sin() const {
    return Var(vgp,
               vgp->new_unary(idx, std::cos(val)),
               std::sin(val));
}

////

Var Var::exp() const {
    double exp_val = std::exp(val);
    return Var(vgp,
               vgp->new_unary(idx, exp_val),
               exp_val);
}

//////////////////////////////////////////////////

Var Var::operator+(Var const& other) const {
    return Var(vgp,
               vgp->new_binary(this->idx, 1,
                               other.idx, 1),
               this->val + other.val);
}

////

Var Var::operator*(Var const& other) const {
    return Var(vgp,
               vgp->new_binary(this->idx, other.val,
                               other.idx, this->val),
               this->val * other.val);
}

//////////////////////////////////////////////////

Var Var::operator*(double k) const {
    return Var(vgp,
               vgp->new_unary(idx, k),
               k * val);
}

//////////////////////////////////////////////////

} // namespace varia

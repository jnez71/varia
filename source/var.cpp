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

Var::Var(Var const& other, double val) :
    vgp(other.vgp),
    idx(vgp->new_nullary()),
    val(val) {
}

//////////////////////////////////////////////////

Var::Grad Var::gradient() const {
    Grad grad(vgp->size());
    grad.g[idx] = 1.0;
    for(int i=idx; i>-1; --i) {
        auto const& dep = vgp->deps[i];
        if(dep.arity > 0)
            grad.g[dep.x] += dep.d_dx * grad.g[i];
        if(dep.arity > 1)
            grad.g[dep.y] += dep.d_dy * grad.g[i];
    }
    return grad;
}

//////////////////////////////////////////////////

Var Var::sin() const {
    return Var(vgp,
               vgp->new_unary(idx, std::cos(val)),
               std::sin(val));
}

////

Var Var::cos() const {
    return Var(vgp,
               vgp->new_unary(idx, -std::sin(val)),
               std::cos(val));
}

////

Var Var::tan() const {
    double cos_val = std::cos(val);
    return Var(vgp,
               vgp->new_unary(idx, 1.0/(cos_val*cos_val)),
               std::tan(val));
}

////

Var Var::exp() const {
    double exp_val = std::exp(val);
    return Var(vgp,
               vgp->new_unary(idx, exp_val),
               exp_val);
}

////

Var Var::log() const {
    return Var(vgp,
               vgp->new_unary(idx, 1.0/val),
               std::log(val));
}

////

Var Var::tanh() const {
    double tanh_val = std::tanh(val);
    return Var(vgp,
               vgp->new_unary(idx, 1.0-tanh_val*tanh_val),
               tanh_val);
}

////

Var Var::logistic() const {
    double z = 1 / (1 + std::exp(-val));
    return Var(vgp,
               vgp->new_unary(idx, z*(1-z)),
               z);
}

////

Var Var::relu() const {
    return Var(vgp,
               vgp->new_unary(idx, val>0.0 ? 1.0 : 0.0),
               val>0.0 ? val : 0.0);
}

////

Var Var::abs() const {
    return Var(vgp,
               vgp->new_unary(idx, val<0.0 ? -1.0 : 1.0),
               std::abs(val));
}

////

Var Var::pow(double k) const {
    double pow_k_1_val = std::pow(val, k-1);
    return Var(vgp,
               vgp->new_unary(idx, k*pow_k_1_val),
               val*pow_k_1_val);
}

////

Var Var::pow2() const {
    return Var(vgp,
               vgp->new_unary(idx, 2.0*val),
               val*val);
}

////

Var Var::sqrt() const {
    double sqrt_val = std::sqrt(val);
    return Var(vgp,
               vgp->new_unary(idx, 1.0/(2.0*sqrt_val)),
               sqrt_val);
}

////

Var Var::inv() const {
    return Var(vgp,
               vgp->new_unary(idx, -1.0/(val*val)),
               1.0/val);
}

//////////////////////////////////////////////////

Var Var::operator+(Var const& other) const {
    return Var(vgp,
               vgp->new_binary(this->idx, 1.0,
                               other.idx, 1.0),
               this->val + other.val);
}

////

Var Var::operator-(Var const& other) const {
    return Var(vgp,
               vgp->new_binary(this->idx, 1.0,
                               other.idx, -1.0),
               this->val - other.val);
}

////

Var Var::operator*(Var const& other) const {
    return Var(vgp,
               vgp->new_binary(this->idx, other.val,
                               other.idx, this->val),
               this->val * other.val);
}

////

Var Var::operator/(Var const& other) const {
    return Var(vgp,
               vgp->new_binary(this->idx, 1.0/other.val,
                               other.idx, -this->val/(other.val*other.val)),
               this->val / other.val);
}

//////////////////////////////////////////////////

Var Var::operator+(double k) const {
    return Var(vgp,
               vgp->new_unary(idx, 1.0),
               val + k);
}

////

Var Var::operator-(double k) const {
    return Var(vgp,
               vgp->new_unary(idx, 1.0),
               val - k);
}

////

Var Var::rminus(double k) const {
    return Var(vgp,
               vgp->new_unary(idx, -1.0),
               k - val);
}

////

Var Var::operator-() const {
    return Var(vgp,
               vgp->new_unary(idx, -1.0),
               -val);
}

////

Var Var::operator*(double k) const {
    return Var(vgp,
               vgp->new_unary(idx, k),
               k * val);
}

////

Var Var::operator/(double k) const {
    return Var(vgp,
               vgp->new_unary(idx, 1.0/k),
               val / k);
}

////

Var Var::rdivide(double k) const {
    return Var(vgp,
               vgp->new_unary(idx, -k/(val*val)),
               k / val);
}

//////////////////////////////////////////////////

} // namespace varia

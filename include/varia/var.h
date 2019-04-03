/*
Class for a scalar variable that connects to a VarGraph
in order to record dependencies for automatic differentiation.
*/
#pragma once
#include "varia/common.h"
#include "varia/vargraph.h"

namespace varia {

////////////////////////////////////////////////// DECLARATIONS

class Var {
private:
    VarGraph* vgp = nullptr;
    uint idx;
    Real val;

    Var(VarGraph* vgp, uint idx, Real val);

public:
    Var() =default;
    Var(VarGraph* vgp, Real val);
    Var(Var const& other, Real val);

    class Grad {
    private:
        friend class Var;
        std::vector<Real> g;
        Grad(uint n) : g(n, 0.0) {}
    public:
        Real d(Var const& x) const {return g[x.idx];}
    };

    Real value() const {return val;}
    Grad gradient() const;

    Var sin() const;
    Var cos() const;
    Var tan() const;
    Var exp() const;
    Var log() const;
    Var tanh() const;
    Var logistic() const;
    Var relu() const;
    Var abs() const;
    Var pow(Real k) const;
    Var pow2() const;
    Var sqrt() const;
    Var inv() const;

    Var operator+(Var const& other) const;
    Var operator-(Var const& other) const;
    Var operator*(Var const& other) const;
    Var operator/(Var const& other) const;

    Var operator+(Real k) const;
    Var operator-(Real k) const;
    Var rminus(Real k) const;
    Var operator-() const;
    Var operator*(Real k) const;
    Var operator/(Real k) const;
    Var rdivide(Real k) const;

    VarGraph* get_vgp() const {return vgp;}
};

////////////////////////////////////////////////// DEFINITIONS

inline Var sin(Var const& x) {return x.sin();}
inline Var cos(Var const& x) {return x.cos();}
inline Var tan(Var const& x) {return x.tan();}
inline Var exp(Var const& x) {return x.exp();}
inline Var log(Var const& x) {return x.log();}
inline Var tanh(Var const& x) {return x.tanh();}
inline Var logistic(Var const& x) {return x.logistic();}
inline Var relu(Var const& x) {return x.relu();}
inline Var abs(Var const& x) {return x.abs();}
inline Var pow(Var const& x, Real k) {return x.pow(k);}
inline Var pow2(Var const& x) {return x.pow2();}
inline Var sqrt(Var const& x) {return x.sqrt();}
inline Var inv(Var const& x) {return x.inv();}

inline Var operator+(Real k, Var const& x) {return x+k;}
inline Var operator-(Real k, Var const& x) {return x.rminus(k);}
inline Var operator*(Real k, Var const& x) {return x*k;}
inline Var operator/(Real k, Var const& x) {return x.rdivide(k);}

/////////////////////////

inline Var::Var(VarGraph* vgp, uint idx, Real val) :
    vgp(vgp),
    idx(idx),
    val(val) {
}

/////////////////////////

inline Var::Var(VarGraph* vgp, Real val) :
    vgp(vgp),
    idx(vgp->new_nullary()),
    val(val) {
}

/////

inline Var::Var(Var const& other, Real val) :
    vgp(other.vgp),
    idx(vgp->new_nullary()),
    val(val) {
}

/////////////////////////

inline Var::Grad Var::gradient() const {
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

/////////////////////////

inline Var Var::sin() const {
    return Var(vgp,
               vgp->new_unary(idx, std::cos(val)),
               std::sin(val));
}

/////

inline Var Var::cos() const {
    return Var(vgp,
               vgp->new_unary(idx, -std::sin(val)),
               std::cos(val));
}

/////

inline Var Var::tan() const {
    Real cos_val = std::cos(val);
    return Var(vgp,
               vgp->new_unary(idx, 1.0/(cos_val*cos_val)),
               std::tan(val));
}

/////

inline Var Var::exp() const {
    Real exp_val = std::exp(val);
    return Var(vgp,
               vgp->new_unary(idx, exp_val),
               exp_val);
}

/////

inline Var Var::log() const {
    return Var(vgp,
               vgp->new_unary(idx, 1.0/val),
               std::log(val));
}

/////

inline Var Var::tanh() const {
    Real tanh_val = std::tanh(val);
    return Var(vgp,
               vgp->new_unary(idx, 1.0-tanh_val*tanh_val),
               tanh_val);
}

/////

inline Var Var::logistic() const {
    Real z = 1 / (1 + std::exp(-val));
    return Var(vgp,
               vgp->new_unary(idx, z*(1-z)),
               z);
}

/////

inline Var Var::relu() const {
    return Var(vgp,
               vgp->new_unary(idx, val>0.0 ? 1.0 : 0.0),
               val>0.0 ? val : 0.0);
}

/////

inline Var Var::abs() const {
    return Var(vgp,
               vgp->new_unary(idx, val<0.0 ? -1.0 : 1.0),
               std::abs(val));
}

/////

inline Var Var::pow(Real k) const {
    Real pow_k_1_val = std::pow(val, k-1);
    return Var(vgp,
               vgp->new_unary(idx, k*pow_k_1_val),
               val*pow_k_1_val);
}

/////

inline Var Var::pow2() const {
    return Var(vgp,
               vgp->new_unary(idx, 2.0*val),
               val*val);
}

/////

inline Var Var::sqrt() const {
    Real sqrt_val = std::sqrt(val);
    return Var(vgp,
               vgp->new_unary(idx, 1.0/(2.0*sqrt_val)),
               sqrt_val);
}

/////

inline Var Var::inv() const {
    return Var(vgp,
               vgp->new_unary(idx, -1.0/(val*val)),
               1.0/val);
}

/////////////////////////

inline Var Var::operator+(Var const& other) const {
    return Var(vgp,
               vgp->new_binary(this->idx, 1.0,
                               other.idx, 1.0),
               this->val + other.val);
}

/////

inline Var Var::operator-(Var const& other) const {
    return Var(vgp,
               vgp->new_binary(this->idx, 1.0,
                               other.idx, -1.0),
               this->val - other.val);
}

/////

inline Var Var::operator*(Var const& other) const {
    return Var(vgp,
               vgp->new_binary(this->idx, other.val,
                               other.idx, this->val),
               this->val * other.val);
}

/////

inline Var Var::operator/(Var const& other) const {
    return Var(vgp,
               vgp->new_binary(this->idx, 1.0/other.val,
                               other.idx, -this->val/(other.val*other.val)),
               this->val / other.val);
}

/////////////////////////

inline Var Var::operator+(Real k) const {
    return Var(vgp,
               vgp->new_unary(idx, 1.0),
               val + k);
}

/////

inline Var Var::operator-(Real k) const {
    return Var(vgp,
               vgp->new_unary(idx, 1.0),
               val - k);
}

/////

inline Var Var::rminus(Real k) const {
    return Var(vgp,
               vgp->new_unary(idx, -1.0),
               k - val);
}

/////

inline Var Var::operator-() const {
    return Var(vgp,
               vgp->new_unary(idx, -1.0),
               -val);
}

/////

inline Var Var::operator*(Real k) const {
    return Var(vgp,
               vgp->new_unary(idx, k),
               k * val);
}

/////

inline Var Var::operator/(Real k) const {
    return Var(vgp,
               vgp->new_unary(idx, 1.0/k),
               val / k);
}

/////

inline Var Var::rdivide(Real k) const {
    return Var(vgp,
               vgp->new_unary(idx, -k/(val*val)),
               k / val);
}

//////////////////////////////////////////////////

} // namespace varia

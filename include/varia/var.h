/*
Class for a scalar variable that connects to a VarGraph
in order to record dependencies for automatic differentiation.
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

    class Grad {
    private:
        friend class Var;
        std::vector<double> g;
        Grad(uint n) : g(n, 0.0) {}
    public:
        inline double d(Var const& x) const {return g[x.idx];}
    };

    inline double value() const {return val;}
    Grad gradient() const;

    Var sin() const;
    // Var cos() const;
    // Var tan() const;
    Var exp() const;
    // Var log() const;
    // Var tanh() const;
    // Var abs() const;
    // Var pow(double k) const;
    // Var pow2() const;
    // Var sqrt() const;
    // Var inv() const;

    Var operator+(Var const& other) const;
    // Var operator-(Var const& other) const;
    // Var operator-() const;
    Var operator*(Var const& other) const;
    // Var operator/(Var const& other) const;

    // Var operator+(double k) const;
    // Var operator-(double k) const;
    // Var rminus(double k) const;
    Var operator*(double k) const;
    // Var operator/(double k) const;
    // Var rdivide(double k) const;
};

//////////////////////////////////////////////////

inline Var sin(Var const& x) {return x.sin();}
// inline Var cos(Var const& x) {return x.cos();}
// inline Var tan(Var const& x) {return x.tan();}
inline Var exp(Var const& x) {return x.exp();}
// inline Var log(Var const& x) {return x.log();}
// inline Var tanh(Var const& x) {return x.tanh();}
// inline Var abs(Var const& x) {return x.abs();}
// inline Var pow(Var const& x, double k) {return x.pow(k);}
// inline Var pow2(Var const& x) {return x.pow2();}
// inline Var sqrt(Var const& x) {return x.sqrt();}
// inline Var inv(Var const& x) {return x.inv();}

// inline Var operator+(double k, Var const& x) {return x+k;}
// inline Var operator-(double k, Var const& x) {return x.rminus(k);}
inline Var operator*(double k, Var const& x) {return x*k;}
// inline Var operator/(double k, Var const& x) {return x.rdivide(k);}

//////////////////////////////////////////////////

} // namespace varia

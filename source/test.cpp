/*
Just a test.
*/
#include "varia.h"

using namespace varia;

//////////////////////////////////////////////////

struct Cost {
    double val;
    std::vector<double> grad;
};

Cost objective(double x_choice, double y_choice) {
    VarGraph vg;
    Var x(&vg, x_choice);
    Var y(&vg, y_choice);
    Var c = 1 + 3*sqrt(pow(y, 2))*2 + exp(log(exp(sin(x)))) + y*y - abs(y) + tan(inv(y/x))*cos(-x/-y)/sin(x*(1/y)) + relu(logistic(1e5*x));
    Var q = sin(1/c + 5);
    Var w;
    w = q;
    w = w + 1;
    w.reset(123);
    Var::Grad dc = c.gradient();
    return Cost{c.value(),
                {dc.d(x), dc.d(y)}};
}

//////////////////////////////////////////////////

int main(int argc, char** argv) {
    Cost c = objective(1, 1);
    c = objective(3.14159, -2); // 18, -1, -9
    std::cout << "    c: " << c.val << std::endl;
    std::cout << "dc/dx: " << c.grad[0] << std::endl;
    std::cout << "dc/dy: " << c.grad[1] << std::endl;
    return 0;
}

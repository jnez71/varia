/*
Description.
*/
#include <varia/var.h>

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
    Var c = 3*y*2 + exp(sin(x)) + y*y;
    Var q = sin(c);
    Var::Grad dc = c.gradient();
    return Cost{c.value(),
                {dc.d(x), dc.d(y)}};
}

//////////////////////////////////////////////////

int main(int argc, char** argv) {
    Cost c = objective(3.14159, -2);
    std::cout << "    c: " << c.val << std::endl;
    std::cout << "dc/dx: " << c.grad[0] << std::endl;
    std::cout << "dc/dy: " << c.grad[1] << std::endl;
    return 0;
}

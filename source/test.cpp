/*
Description.
*/
#include <varia/var.h>

using namespace varia;

//////////////////////////////////////////////////


//////////////////////////////////////////////////

int main(int argc, char** argv) {
    VarGraph vg;
    Var x(&vg, 3.14159);
    Var y(&vg, -2);
    Var z = 3*y*2 + exp(sin(x));
    print(z.value());
    print(z.gradient()[&z]);
    return 0;
}

/*
Description.
*/
#include <varia/var.h>

using namespace varia;

//////////////////////////////////////////////////


//////////////////////////////////////////////////

int main(int argc, char** argv) {
    VarGraph vg;
    Var x(&vg, 1.5);
    Var y(&vg, -2);
    print(y.value());
    return 0;
}

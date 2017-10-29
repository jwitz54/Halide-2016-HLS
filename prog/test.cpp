// The only Halide header file you need is Halide.h. It includes all of Halide.
#include "Halide.h"
//#include "../src/TestTypes.h"
//#include "template.h"

using namespace Halide;

int main(int argc, char **argv) {

    Buffer<test_int> input(10);
    for (int i = 0; i < 10; i++){
        input(i) = 0;
    }

    Var x;
    Func brighter;
    brighter(x) = input(x) + (test_int)1;

    brighter.compile_to_c("brighter.cpp", {}, "brighter");
    //brighter.compile_to_static_library("brighter", {}, "brighter");

    printf("Success!\n");
    return 0;
}

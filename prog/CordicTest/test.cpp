// The only Halide header file you need is Halide.h. It includes all of Halide.
#include "Halide.h"

using namespace Halide;

int main(int argc, char **argv) {

    Buffer<ap_int_halide<32> > input1(10);

    mult.compile_to_c("mult.cpp", {}, "mult");
    mult.compile_to_header("mult.h", {}, "mult");

    printf("Success!\n");
    return 0;

}

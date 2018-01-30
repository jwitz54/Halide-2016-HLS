// The only Halide header file you need is Halide.h. It includes all of Halide.
#include "Halide.h"

using namespace Halide;

int main(int argc, char **argv) {

    Buffer<ap_int_halide<32> > input1(10);
    Buffer<ap_int_halide<32> > input2(10);
    for (int i = 0; i < 10; i++){
        input1(i) = 10;
        input2(i) = 10;
    }

    Var x;
    Func mult;
    //Func toTestInt;
    //toTestInt(x) = cast(TestInt(8), input(x)); 
    //brighter(x) = toTestInt(x) + 1;
    //brighter(x) = cast(TestInt(8), input(x)) + 1;
    mult(x) = input1(x) * input2(x) ;
    //brighter(x) = input(x) + 1;

    mult.compile_to_c("mult.cpp", {}, "mult");
    mult.compile_to_header("mult.h", {}, "mult");
    //mult.compile_to_static_library("mult", {}, "mult");

    printf("Success!\n");
    return 0;

}

// The only Halide header file you need is Halide.h. It includes all of Halide.
#include "Halide.h"

using namespace Halide;

int main(int argc, char **argv) {

    Buffer<int32_t> input(10);
    for (int i = 0; i < 10; i++){
        input(i) = 0;
    }

    Var x;
    Func brighter;
    //Func to16bit;
    //to16bit(x) = cast(UInt(16), input(x)); 
    brighter(x) = input(x) + 1;

    brighter.compile_to_c("brighter.cpp", {}, "brighter");
    brighter.compile_to_header("brighter.h", {}, "brighter");
    //brighter.compile_to_static_library("brighter", {}, "brighter");

    printf("Success!\n");
    return 0;
}

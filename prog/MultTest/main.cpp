#include <iostream>
#include "mult.h"
#include "../src/runtime/HalideBuffer.h"
//#include "../src/Buffer.h"

//static const uint8_t _output_data[] __attribute__ ((aligned (32))) = {
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//};

int main(){
	Halide::Buffer<int32_t> output(10);

	mult(output);
	for (int i = 0; i < 10; i++) {
		std::cout << (int)output(i) << std::endl;
	}
}

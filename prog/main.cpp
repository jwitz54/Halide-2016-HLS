#include <iostream>
#include "brighter.h"
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
	Halide::Buffer<test_int> output(10);
	brighter(output);
	for (int i = 0; i < 10; i++) {
		std::cout << output(i) << std::endl;
	}
}

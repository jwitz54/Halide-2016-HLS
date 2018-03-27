#include <iostream>
#include "lr.h"
#include "../src/runtime/HalideBuffer.h"
//#include "../src/Buffer.h"

#define NUM_FEATURES      1024
#define NUM_SAMPLES       2000

//static const uint8_t _output_data[] __attribute__ ((aligned (32))) = {
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//};

int main(){
	Halide::Buffer<float> output(NUM_FEATURES);

	parameterOut(output);
	for (int i = 0; i < NUM_FEATURES; i++) {
		std::cout << (float)output(i) << std::endl;
	}
}

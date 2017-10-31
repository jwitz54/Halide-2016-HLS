#include <iostream>
#include "brighter.h"
#include "../src/runtime/HalideBuffer.h"
//#include "../src/Buffer.h"

static const uint8_t _output_data[] __attribute__ ((aligned (32))) = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

int main(){

	//static const halide_dimension_t _output_buffer_shape[] = {halide_dimension_t(0, 10, 1)};
	//static halide_buffer_t _output_buffer_ = {0, nullptr, const_cast<uint8_t*>(&_output_data[0]), 0, halide_type_t((halide_type_code_t)(0), 64, 1), 1, const_cast<halide_dimension_t*>(_output_buffer_shape)};
	////Halide::Buffer<uint64_t> output(10);	
	////struct halide_buffer_t *output;
	//brighter(&_output_buffer_);
	Halide::Buffer<int64_t> output(10);
	brighter(output);
	for (int i = 0; i < 10; i++) {
		std::cout << output(i) << std::endl;
	}
}

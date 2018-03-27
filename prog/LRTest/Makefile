#g++ logistic_regression.cpp -g -std=c++11 -lHalide -lpthread `libpng-config --cflags --ldflags` -ldl -o logistic_regression
logistic_regression: logistic_regression.cpp
	g++ logistic_regression.cpp -g -I ../../include -I ../../tools -L ../../bin -lHalide `libpng-config --cflags --ldflags` -ljpeg -lpthread -ldl -o logistic_regression -std=c++11
	LD_LIBRARY_PATH=../../bin ./logistic_regression
	
cmake:
	g++ -o main main.cpp lr.cpp ../../bin/build/runtimes/runtime_host.a -std=c++11 -I .. -I /opt/Xilinx/Vivado_HLS/2015.1/include/ -ldl -lpthread	

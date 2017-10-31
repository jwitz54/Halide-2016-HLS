BIN=../bin
INC=../include

halidemake:
	g++ test.cpp -g -I ../include -I ../tools -L ../bin -lHalide `libpng-config --cflags --ldflags` -ljpeg -lpthread -ldl -o test -std=c++11
	LD_LIBRARY_PATH=../bin ./test

cmake:
	g++ -o main main.cpp brighter.cpp ../bin/build/runtimes/runtime_host.a -std=c++11 -I . -ldl -lpthread	

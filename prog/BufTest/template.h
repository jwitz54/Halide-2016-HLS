#include <iostream>
using namespace std;

template <class T>
class test_int{
private:
	T val;
public:
	test_int(T initVal){
		val = initVal;
	}
	test_int(void){
		val = 0;
	}

	void operator=(T newVal){
		val = newVal;
	}
	T operator+(T addVal){
		return val + addVal;
	}
	T operator-(T subVal){
		return val - subVal;
	}
};

#ifndef TESTTYPES_H
#define TESTTYPES_H

#ifndef COMPILING_HALIDE_RUNTIME
#include <iostream>
#endif

class test_int{
public:
	int64_t val;

	test_int(int64_t initVal){
		val = initVal;
	}
	test_int(void){
		val = 0;
	}

	#ifndef COMPILING_HALIDE_RUNTIME
        friend std::ostream& operator<<(std::ostream& os, const test_int& osVal);
	#endif

	// Casting overloading
	operator int() {
		return (int)val;
	}
	//explicit operator void*() {
	//	return (void*)&val;
	//}
	//explicit operator struct halide_device_interface_t*() {
	//	return (struct halide_device_interface_t*)(int64_t)val;
	//}
};
template <class T> 
class test_int_t{
public:
	T val;
	test_int_t(int64_t initVal){
		val = (T)initVal;
	}

	test_int_t(void){
		val = 0;
	}

	#ifndef COMPILING_HALIDE_RUNTIME
        //friend std::ostream& operator<<(std::ostream& os, const test_int_t& osVal);
	#endif

	// Casting overloading
	operator int() {
		return (int)val;
	}
};

template <int T> 
class ap_int_halide{
public:
	int val;
	ap_int_halide(int initVal){
		val = (int)initVal;
	}

	ap_int_halide(void){
		val = 0;
	}

	// Casting overloading
	operator int() {
		return (int)val;
	}
};

template <int T, int U> 
class ap_fixed_halide{
public:
	float val;
	ap_fixed_halide(float initVal){
		val = (float)initVal;
	}

	ap_fixed_halide(void){
		val = 0;
	}

	// Casting overloading
	operator float() {
		return (float)val;
	}
};

#ifndef COMPILING_HALIDE_RUNTIME
inline std::ostream& operator<<(std::ostream& os, const test_int& osVal){
	os << osVal.val;
	return os;

}
//template <class T>
//inline std::ostream& operator<<(std::ostream& os, const test_int_t<T>& osVal){
//	os << osVal.val;
//	return os;
//}
#endif
#endif

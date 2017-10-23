class test_int{
private:
	int64_t val;
public:
	test_int(int64_t initVal){
		val = initVal;
	}
	//test_int(int initVal){
	//	val = (int64_t)initVal;
	//}
	//test_int(struct halide_buffer_t* buf){
	//	val = (int64_t)buf;		
	//}
	test_int(void){
		val = 0;
	}

	// Operator overloading for int
	//void operator=(int newVal){
	//	val = newVal;
	//}
	//int operator+(int addVal){
	//	return val + addVal;
	//}
	//int operator-(int subVal){
	//	return val - subVal;
	//}
	//bool operator!=(int neqVal){
	//	return val != neqVal;
	//}
	//bool operator<=(int leqVal){
	//	return val <= leqVal;
	//}
	//bool operator>=(int greqVal){
	//	return val >= greqVal;
	//}
	//bool operator==(int eqVal){
	//	return val == eqVal;
	//}
	//bool operator>(int grVal){
	//	return val > grVal;
	//}
	//bool operator<(int lsVal){
	//	return val < lsVal;
	//}

	// Operator overloading for int64_t
	//void operator=(int64_t newVal){
	//	val = newVal;
	//}
	//int64_t operator+(int64_t addVal){
	//	return val + addVal;
	//}
	//int64_t operator-(int64_t subVal){
	//	return val - subVal;
	//}
	//bool operator!=(int64_t neqVal){
	//	return val != neqVal;
	//}
	//bool operator<=(int64_t leqVal){
	//	return val <= leqVal;
	//}
	//bool operator>=(int64_t greqVal){
	//	return val >= greqVal;
	//}
	//bool operator==(int64_t eqVal){
	//	return val == eqVal;
	//}
	//bool operator>(int64_t grVal){
	//	return val > grVal;
	//}
	//bool operator<(int64_t lsVal){
	//	return val < lsVal;
	//}

	//// Operator overloading for test_int64_ts
	//void operator=(test_int newVal){
	//	val = newVal.val;
	//}
	//test_int operator+(test_int addVal){
	//	return val + addVal.val;
	//}
	//test_int operator-(test_int subVal){
	//	return val - subVal.val;
	//}
	//bool operator!=(test_int neqVal){
	//	return val != neqVal.val;
	//}
	//bool operator<=(test_int leqVal){
	//	return val <= leqVal.val;
	//}
	//bool operator>=(test_int greqVal){
	//	return val >= greqVal.val;
	//}
	//bool operator==(test_int eqVal){
	//	return val == eqVal.val;
	//}
	//bool operator>(test_int grVal){
	//	return val > grVal.val;
	//}
	//bool operator<(test_int lsVal){
	//	return val < lsVal.val;
	//}

	// Casting overloading
	operator int() {
		return (int)val;
	}
	//operator bool() {
	//	return (bool)val;
	//}
	//operator uint8_t() {
	//	return (uint8_t)val;
	//}
	//operator int64_t() {
	//	return val;
	//}
	//operator uint64_t() {
	//	return (uint64_t)val;
	//}
	//operator long int() {
	//	return (long int)val;
	//}
	//explicit operator void*() {
	//	return (void*)&val;
	//}
	//explicit operator struct halide_device_interface_t*() {
	//	return (struct halide_device_interface_t*)(int64_t)val;
	//}
};
template <class T> 
class test_int_t{
private:
	T val;
public:
	test_int_t(int64_t initVal){
		val = (T)initVal;
	}
	test_int_t(int initVal){
		val = (T)initVal;
	}
	test_int_t(struct halide_buffer_t* buf){
		val = (T)buf;		
	}
	test_int_t(void){
		val = 0;
	}

	// Operator overloading for int
	//void operator=(int newVal){
	//	val = newVal;
	//}
	//int operator+(int addVal){
	//	return val + addVal;
	//}
	//int operator-(int subVal){
	//	return val - subVal;
	//}
	//bool operator!=(int neqVal){
	//	return val != neqVal;
	//}
	//bool operator<=(int leqVal){
	//	return val <= leqVal;
	//}
	//bool operator>=(int greqVal){
	//	return val >= greqVal;
	//}
	//bool operator==(int eqVal){
	//	return val == eqVal;
	//}
	//bool operator>(int grVal){
	//	return val > grVal;
	//}
	//bool operator<(int lsVal){
	//	return val < lsVal;
	//}

	// Operator overloading for int64_t
	//void operator=(int64_t newVal){
	//	val = newVal;
	//}
	//int64_t operator+(int64_t addVal){
	//	return val + addVal;
	//}
	//int64_t operator-(int64_t subVal){
	//	return val - subVal;
	//}
	//bool operator!=(int64_t neqVal){
	//	return val != neqVal;
	//}
	//bool operator<=(int64_t leqVal){
	//	return val <= leqVal;
	//}
	//bool operator>=(int64_t greqVal){
	//	return val >= greqVal;
	//}
	//bool operator==(int64_t eqVal){
	//	return val == eqVal;
	//}
	//bool operator>(int64_t grVal){
	//	return val > grVal;
	//}
	//bool operator<(int64_t lsVal){
	//	return val < lsVal;
	//}

	//// Operator overloading for test_int64_ts
	//void operator=(test_int newVal){
	//	val = newVal.val;
	//}
	//test_int operator+(test_int addVal){
	//	return val + addVal.val;
	//}
	//test_int operator-(test_int subVal){
	//	return val - subVal.val;
	//}
	//bool operator!=(test_int neqVal){
	//	return val != neqVal.val;
	//}
	//bool operator<=(test_int leqVal){
	//	return val <= leqVal.val;
	//}
	//bool operator>=(test_int greqVal){
	//	return val >= greqVal.val;
	//}
	//bool operator==(test_int eqVal){
	//	return val == eqVal.val;
	//}
	//bool operator>(test_int grVal){
	//	return val > grVal.val;
	//}
	//bool operator<(test_int lsVal){
	//	return val < lsVal.val;
	//}

	// Casting overloading
	operator int() {
		return (int)val;
	}
	//operator bool() {
	//	return (bool)val;
	//}
	//operator uint8_t() {
	//	return (uint8_t)val;
	//}
	//operator int64_t() {
	//	return val;
	//}
	//operator uint64_t() {
	//	return (uint64_t)val;
	//}
	//operator long int() {
	//	return (long int)val;
	//}
	//explicit operator void*() {
	//	return (void*)&val;
	//}
	//explicit operator struct halide_device_interface_t*() {
	//	return (struct halide_device_interface_t*)(int64_t)val;
	//}
};

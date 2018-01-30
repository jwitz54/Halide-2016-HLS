#include <iostream>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "ap_int.h"
#include "../src/TestTypes.h"
#ifndef HALIDE_ATTRIBUTE_ALIGN
  #ifdef _MSC_VER
    #define HALIDE_ATTRIBUTE_ALIGN(x) __declspec(align(x))
  #else
    #define HALIDE_ATTRIBUTE_ALIGN(x) __attribute__((aligned(x)))
  #endif
#endif
#ifndef BUFFER_T_DEFINED
#define BUFFER_T_DEFINED
#include <stdbool.h>
#include <stdint.h>
typedef struct buffer_t {
    uint64_t dev;
    uint8_t* host;
    int32_t extent[4];
    int32_t stride[4];
    int32_t min[4];
    int32_t elem_size;
    HALIDE_ATTRIBUTE_ALIGN(1) bool host_dirty;
    HALIDE_ATTRIBUTE_ALIGN(1) bool dev_dirty;
    HALIDE_ATTRIBUTE_ALIGN(1) uint8_t _padding[10 - sizeof(void *)];
} buffer_t;
#endif
struct halide_filter_metadata_t;
extern "C" {
void *halide_malloc(void *ctx, size_t);
void halide_free(void *ctx, void *ptr);
void *halide_print(void *ctx, const void *str);
void *halide_error(void *ctx, const void *str);
int halide_debug_to_file(void *ctx, const char *filename, int, struct buffer_t *buf);
int halide_start_clock(void *ctx);
int64_t halide_current_time_ns(void *ctx);
void halide_profiler_pipeline_end(void *, void *);
}

#ifdef _WIN32
float roundf(float);
double round(double);
#else
inline float asinh_f32(float x) {return asinhf(x);}
inline float acosh_f32(float x) {return acoshf(x);}
inline float atanh_f32(float x) {return atanhf(x);}
inline double asinh_f64(double x) {return asinh(x);}
inline double acosh_f64(double x) {return acosh(x);}
inline double atanh_f64(double x) {return atanh(x);}
#endif
inline float sqrt_f32(float x) {return sqrtf(x);}
inline float sin_f32(float x) {return sinf(x);}
inline float asin_f32(float x) {return asinf(x);}
inline float cos_f32(float x) {return cosf(x);}
inline float acos_f32(float x) {return acosf(x);}
inline float tan_f32(float x) {return tanf(x);}
inline float atan_f32(float x) {return atanf(x);}
inline float sinh_f32(float x) {return sinhf(x);}
inline float cosh_f32(float x) {return coshf(x);}
inline float tanh_f32(float x) {return tanhf(x);}
inline float hypot_f32(float x, float y) {return hypotf(x, y);}
inline float exp_f32(float x) {return expf(x);}
inline float log_f32(float x) {return logf(x);}
inline float pow_f32(float x, float y) {return powf(x, y);}
inline float floor_f32(float x) {return floorf(x);}
inline float ceil_f32(float x) {return ceilf(x);}
inline float round_f32(float x) {return roundf(x);}

inline double sqrt_f64(double x) {return sqrt(x);}
inline double sin_f64(double x) {return sin(x);}
inline double asin_f64(double x) {return asin(x);}
inline double cos_f64(double x) {return cos(x);}
inline double acos_f64(double x) {return acos(x);}
inline double tan_f64(double x) {return tan(x);}
inline double atan_f64(double x) {return atan(x);}
inline double sinh_f64(double x) {return sinh(x);}
inline double cosh_f64(double x) {return cosh(x);}
inline double tanh_f64(double x) {return tanh(x);}
inline double hypot_f64(double x, double y) {return hypot(x, y);}
inline double exp_f64(double x) {return exp(x);}
inline double log_f64(double x) {return log(x);}
inline double pow_f64(double x, double y) {return pow(x, y);}
inline double floor_f64(double x) {return floor(x);}
inline double ceil_f64(double x) {return ceil(x);}
inline double round_f64(double x) {return round(x);}

inline float nan_f32() {return NAN;}
inline float neg_inf_f32() {return -INFINITY;}
inline float inf_f32() {return INFINITY;}
inline bool is_nan_f32(float x) {return x != x;}
inline bool is_nan_f64(double x) {return x != x;}
inline float float_from_bits(uint32_t bits) {
 union {
  uint32_t as_uint;
  float as_float;
 } u;
 u.as_uint = bits;
 return u.as_float;
}

template<typename T> T max(T a, T b) {if (a > b) return a; return b;}
template<typename T> T min(T a, T b) {if (a < b) return a; return b;}
template<typename A, typename B> A reinterpret(B b) {A a; memcpy(&a, &b, sizeof(a)); return a;}

static bool halide_rewrite_buffer(buffer_t *b, int32_t elem_size,
                           int32_t min0, int32_t extent0, int32_t stride0,
                           int32_t min1, int32_t extent1, int32_t stride1,
                           int32_t min2, int32_t extent2, int32_t stride2,
                           int32_t min3, int32_t extent3, int32_t stride3) {
 b->min[0] = min0;
 b->min[1] = min1;
 b->min[2] = min2;
 b->min[3] = min3;
 b->extent[0] = extent0;
 b->extent[1] = extent1;
 b->extent[2] = extent2;
 b->extent[3] = extent3;
 b->stride[0] = stride0;
 b->stride[1] = stride1;
 b->stride[2] = stride2;
 b->stride[3] = stride3;
 return true;
}
#ifndef HALIDE_FUNCTION_ATTRS
#define HALIDE_FUNCTION_ATTRS
#endif
static uint8_t _b0_data[] __attribute__ ((aligned (32))) = {10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0};
static buffer_t _b0_buffer = {0, &_b0_data[0], {10, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, 4, 0, 0};
static buffer_t *_b0 = &_b0_buffer;
static uint8_t _b1_data[] __attribute__ ((aligned (32))) = {10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0, 10, 0, 0, 0};
static buffer_t _b1_buffer = {0, &_b1_data[0], {10, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, 4, 0, 0};
static buffer_t *_b1 = &_b1_buffer;

#ifdef __cplusplus
extern "C" {
#endif
int32_t  halide_error_access_out_of_bounds(void *, const char *, int32_t , int32_t , int32_t , int32_t , int32_t );
int32_t  halide_error_bad_elem_size(void *, const char *, const char *, int32_t , int32_t );
int32_t  halide_error_buffer_allocation_too_large(void *, const char *, int64_t , int64_t );
int32_t  halide_error_constraint_violated(void *, const char *, int32_t , const char *, int32_t );
int32_t  halide_error_constraints_make_required_region_smaller(void *, const char *, int32_t , int32_t , int32_t , int32_t , int32_t );


static int __mult(buffer_t *_mult_buffer, buffer_t *_b0_buffer, buffer_t *_b1_buffer) HALIDE_FUNCTION_ATTRS {
 ap_int<32> *_mult = (ap_int<32> *)(_mult_buffer->host);
 (void)_mult;
 const bool _mult_host_and_dev_are_null = (_mult_buffer->host == nullptr) && (_mult_buffer->dev == 0);
 (void)_mult_host_and_dev_are_null;
 const int32_t _mult_min_0 = _mult_buffer->min[0];
 (void)_mult_min_0;
 const int32_t _mult_min_1 = _mult_buffer->min[1];
 (void)_mult_min_1;
 const int32_t _mult_min_2 = _mult_buffer->min[2];
 (void)_mult_min_2;
 const int32_t _mult_min_3 = _mult_buffer->min[3];
 (void)_mult_min_3;
 const int32_t _mult_extent_0 = _mult_buffer->extent[0];
 (void)_mult_extent_0;
 const int32_t _mult_extent_1 = _mult_buffer->extent[1];
 (void)_mult_extent_1;
 const int32_t _mult_extent_2 = _mult_buffer->extent[2];
 (void)_mult_extent_2;
 const int32_t _mult_extent_3 = _mult_buffer->extent[3];
 (void)_mult_extent_3;
 const int32_t _mult_stride_0 = _mult_buffer->stride[0];
 (void)_mult_stride_0;
 const int32_t _mult_stride_1 = _mult_buffer->stride[1];
 (void)_mult_stride_1;
 const int32_t _mult_stride_2 = _mult_buffer->stride[2];
 (void)_mult_stride_2;
 const int32_t _mult_stride_3 = _mult_buffer->stride[3];
 (void)_mult_stride_3;
 const int32_t _mult_elem_size = _mult_buffer->elem_size;
 (void)_mult_elem_size;
 ap_int<32> *_b0 = (ap_int<32> *)(_b0_buffer->host);
 (void)_b0;
 const bool _b0_host_and_dev_are_null = (_b0_buffer->host == nullptr) && (_b0_buffer->dev == 0);
 (void)_b0_host_and_dev_are_null;
 const int32_t _b0_min_0 = _b0_buffer->min[0];
 (void)_b0_min_0;
 const int32_t _b0_min_1 = _b0_buffer->min[1];
 (void)_b0_min_1;
 const int32_t _b0_min_2 = _b0_buffer->min[2];
 (void)_b0_min_2;
 const int32_t _b0_min_3 = _b0_buffer->min[3];
 (void)_b0_min_3;
 const int32_t _b0_extent_0 = _b0_buffer->extent[0];
 (void)_b0_extent_0;
 const int32_t _b0_extent_1 = _b0_buffer->extent[1];
 (void)_b0_extent_1;
 const int32_t _b0_extent_2 = _b0_buffer->extent[2];
 (void)_b0_extent_2;
 const int32_t _b0_extent_3 = _b0_buffer->extent[3];
 (void)_b0_extent_3;
 const int32_t _b0_stride_0 = _b0_buffer->stride[0];
 (void)_b0_stride_0;
 const int32_t _b0_stride_1 = _b0_buffer->stride[1];
 (void)_b0_stride_1;
 const int32_t _b0_stride_2 = _b0_buffer->stride[2];
 (void)_b0_stride_2;
 const int32_t _b0_stride_3 = _b0_buffer->stride[3];
 (void)_b0_stride_3;
 const int32_t _b0_elem_size = _b0_buffer->elem_size;
 (void)_b0_elem_size;
 ap_int<32> *_b1 = (ap_int<32> *)(_b1_buffer->host);
 (void)_b1;
 const bool _b1_host_and_dev_are_null = (_b1_buffer->host == nullptr) && (_b1_buffer->dev == 0);
 (void)_b1_host_and_dev_are_null;
 const int32_t _b1_min_0 = _b1_buffer->min[0];
 (void)_b1_min_0;
 const int32_t _b1_min_1 = _b1_buffer->min[1];
 (void)_b1_min_1;
 const int32_t _b1_min_2 = _b1_buffer->min[2];
 (void)_b1_min_2;
 const int32_t _b1_min_3 = _b1_buffer->min[3];
 (void)_b1_min_3;
 const int32_t _b1_extent_0 = _b1_buffer->extent[0];
 (void)_b1_extent_0;
 const int32_t _b1_extent_1 = _b1_buffer->extent[1];
 (void)_b1_extent_1;
 const int32_t _b1_extent_2 = _b1_buffer->extent[2];
 (void)_b1_extent_2;
 const int32_t _b1_extent_3 = _b1_buffer->extent[3];
 (void)_b1_extent_3;
 const int32_t _b1_stride_0 = _b1_buffer->stride[0];
 (void)_b1_stride_0;
 const int32_t _b1_stride_1 = _b1_buffer->stride[1];
 (void)_b1_stride_1;
 const int32_t _b1_stride_2 = _b1_buffer->stride[2];
 (void)_b1_stride_2;
 const int32_t _b1_stride_3 = _b1_buffer->stride[3];
 (void)_b1_stride_3;
 const int32_t _b1_elem_size = _b1_buffer->elem_size;
 (void)_b1_elem_size;
 bool _0 = !(_b0_host_and_dev_are_null);
 bool _1 = 0 <= _mult_min_0;
 int32_t _2 = _mult_min_0 + _mult_extent_0;
 bool _3 = _2 <= 10;
 bool _4 = _1 && _3;
 bool _5 = _0 || _4;
 if (!_5)  {
  int32_t _6 = _mult_min_0 + _mult_extent_0;
  int32_t _7 = _6 + -1;
  int32_t _8 = halide_error_constraints_make_required_region_smaller(nullptr, "Input buffer b0", 0, 0, 9, _mult_min_0, _7);
  return _8;
 }
 bool _9 = !(_b1_host_and_dev_are_null);
 bool _10 = 0 <= _mult_min_0;
 int32_t _11 = _mult_min_0 + _mult_extent_0;
 bool _12 = _11 <= 10;
 bool _13 = _10 && _12;
 bool _14 = _9 || _13;
 if (!_14)  {
  int32_t _15 = _mult_min_0 + _mult_extent_0;
  int32_t _16 = _15 + -1;
  int32_t _17 = halide_error_constraints_make_required_region_smaller(nullptr, "Input buffer b1", 0, 0, 9, _mult_min_0, _16);
  return _17;
 }
 if (_b0_host_and_dev_are_null)
 {
  bool _18 = halide_rewrite_buffer(_b0_buffer, 4, 0, 10, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  (void)_18;
 } // if _b0_host_and_dev_are_null
 if (_b1_host_and_dev_are_null)
 {
  bool _19 = halide_rewrite_buffer(_b1_buffer, 4, 0, 10, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  (void)_19;
 } // if _b1_host_and_dev_are_null
 if (_mult_host_and_dev_are_null)
 {
  bool _20 = halide_rewrite_buffer(_mult_buffer, 4, _mult_min_0, _mult_extent_0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  (void)_20;
 } // if _mult_host_and_dev_are_null
 bool _21 = _b0_host_and_dev_are_null || _b1_host_and_dev_are_null;
 bool _22 = _21 || _mult_host_and_dev_are_null;
 bool _23 = !(_22);
 if (_23)
 {
  bool _24 = _b0_elem_size == 4;
  if (!_24)   {
   int32_t _25 = halide_error_bad_elem_size(nullptr, "Input buffer b0", "ap_int<32>", _b0_elem_size, 4);
   return _25;
  }
  bool _26 = _b1_elem_size == 4;
  if (!_26)   {
   int32_t _27 = halide_error_bad_elem_size(nullptr, "Input buffer b1", "ap_int<32>", _b1_elem_size, 4);
   return _27;
  }
  bool _28 = _mult_elem_size == 4;
  if (!_28)   {
   int32_t _29 = halide_error_bad_elem_size(nullptr, "Output buffer mult", "ap_int<32>", _mult_elem_size, 4);
   return _29;
  }
  bool _30 = _b0_min_0 <= _mult_min_0;
  int32_t _31 = _mult_min_0 + _mult_extent_0;
  int32_t _32 = _31 - _b0_extent_0;
  bool _33 = _32 <= _b0_min_0;
  bool _34 = _30 && _33;
  if (!_34)   {
   int32_t _35 = _mult_min_0 + _mult_extent_0;
   int32_t _36 = _35 + -1;
   int32_t _37 = _b0_min_0 + _b0_extent_0;
   int32_t _38 = _37 + -1;
   int32_t _39 = halide_error_access_out_of_bounds(nullptr, "Input buffer b0", 0, _mult_min_0, _36, _b0_min_0, _38);
   return _39;
  }
  bool _40 = _b1_min_0 <= _mult_min_0;
  int32_t _41 = _mult_min_0 + _mult_extent_0;
  int32_t _42 = _41 - _b1_extent_0;
  bool _43 = _42 <= _b1_min_0;
  bool _44 = _40 && _43;
  if (!_44)   {
   int32_t _45 = _mult_min_0 + _mult_extent_0;
   int32_t _46 = _45 + -1;
   int32_t _47 = _b1_min_0 + _b1_extent_0;
   int32_t _48 = _47 + -1;
   int32_t _49 = halide_error_access_out_of_bounds(nullptr, "Input buffer b1", 0, _mult_min_0, _46, _b1_min_0, _48);
   return _49;
  }
  bool _50 = _b0_stride_0 == 1;
  if (!_50)   {
   int32_t _51 = halide_error_constraint_violated(nullptr, "b0.stride.0", _b0_stride_0, "1", 1);
   return _51;
  }
  bool _52 = _b0_min_0 == 0;
  if (!_52)   {
   int32_t _53 = halide_error_constraint_violated(nullptr, "b0.min.0", _b0_min_0, "0", 0);
   return _53;
  }
  bool _54 = _b0_extent_0 == 10;
  if (!_54)   {
   int32_t _55 = halide_error_constraint_violated(nullptr, "b0.extent.0", _b0_extent_0, "10", 10);
   return _55;
  }
  bool _56 = _b1_stride_0 == 1;
  if (!_56)   {
   int32_t _57 = halide_error_constraint_violated(nullptr, "b1.stride.0", _b1_stride_0, "1", 1);
   return _57;
  }
  bool _58 = _b1_min_0 == 0;
  if (!_58)   {
   int32_t _59 = halide_error_constraint_violated(nullptr, "b1.min.0", _b1_min_0, "0", 0);
   return _59;
  }
  bool _60 = _b1_extent_0 == 10;
  if (!_60)   {
   int32_t _61 = halide_error_constraint_violated(nullptr, "b1.extent.0", _b1_extent_0, "10", 10);
   return _61;
  }
  bool _62 = _mult_stride_0 == 1;
  if (!_62)   {
   int32_t _63 = halide_error_constraint_violated(nullptr, "mult.stride.0", _mult_stride_0, "1", 1);
   return _63;
  }
  int64_t _64 = (int64_t)(_mult_extent_0);
  int64_t _65 = (int64_t)(2147483647);
  bool _66 = _64 <= _65;
  if (!_66)   {
   int64_t _67 = (int64_t)(_mult_extent_0);
   int64_t _68 = (int64_t)(2147483647);
   int32_t _69 = halide_error_buffer_allocation_too_large(nullptr, "mult", _67, _68);
   return _69;
  }
  // produce mult
  for (int _mult_s0_x = _mult_min_0; _mult_s0_x < _mult_min_0 + _mult_extent_0; _mult_s0_x++)
  {
   int32_t _70 = _mult_s0_x - _mult_min_0;
   ap_int<32> _71 = _b1[_mult_s0_x];
   ap_int<32> _72 = _b0[_mult_s0_x];
   ap_int<32> _73 = _71 * _72;
   _mult[_70] = _73;
  } // for _mult_s0_x
 } // if _23
 return 0;
}


int mult(buffer_t *_mult_buffer) HALIDE_FUNCTION_ATTRS {
 ap_int<32> *_mult = (ap_int<32> *)(_mult_buffer->host);
 (void)_mult;
 const bool _mult_host_and_dev_are_null = (_mult_buffer->host == nullptr) && (_mult_buffer->dev == 0);
 (void)_mult_host_and_dev_are_null;
 const int32_t _mult_min_0 = _mult_buffer->min[0];
 (void)_mult_min_0;
 const int32_t _mult_min_1 = _mult_buffer->min[1];
 (void)_mult_min_1;
 const int32_t _mult_min_2 = _mult_buffer->min[2];
 (void)_mult_min_2;
 const int32_t _mult_min_3 = _mult_buffer->min[3];
 (void)_mult_min_3;
 const int32_t _mult_extent_0 = _mult_buffer->extent[0];
 (void)_mult_extent_0;
 const int32_t _mult_extent_1 = _mult_buffer->extent[1];
 (void)_mult_extent_1;
 const int32_t _mult_extent_2 = _mult_buffer->extent[2];
 (void)_mult_extent_2;
 const int32_t _mult_extent_3 = _mult_buffer->extent[3];
 (void)_mult_extent_3;
 const int32_t _mult_stride_0 = _mult_buffer->stride[0];
 (void)_mult_stride_0;
 const int32_t _mult_stride_1 = _mult_buffer->stride[1];
 (void)_mult_stride_1;
 const int32_t _mult_stride_2 = _mult_buffer->stride[2];
 (void)_mult_stride_2;
 const int32_t _mult_stride_3 = _mult_buffer->stride[3];
 (void)_mult_stride_3;
 const int32_t _mult_elem_size = _mult_buffer->elem_size;
 (void)_mult_elem_size;
 int32_t _74 = __mult(_mult_buffer, _b0, _b1);
 bool _75 = _74 == 0;
 if (!_75)  {
  return _74;
 }
 return 0;
}

#ifdef __cplusplus
}  // extern "C"
#endif

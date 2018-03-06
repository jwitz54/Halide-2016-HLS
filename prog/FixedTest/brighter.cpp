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
static uint8_t _b0_data[] __attribute__ ((aligned (32))) = {0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 105, 103, 110, 0, 0, 0, 0, 0, 144, 0};
static buffer_t _b0_buffer = {0, &_b0_data[0], {10, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, 5, 0, 0};
static buffer_t *_b0 = &_b0_buffer;

#ifdef __cplusplus
extern "C" {
#endif
int32_t  halide_error_access_out_of_bounds(void *, const char *, int32_t , int32_t , int32_t , int32_t , int32_t );
int32_t  halide_error_bad_elem_size(void *, const char *, const char *, int32_t , int32_t );
int32_t  halide_error_buffer_allocation_too_large(void *, const char *, int64_t , int64_t );
int32_t  halide_error_constraint_violated(void *, const char *, int32_t , const char *, int32_t );
int32_t  halide_error_constraints_make_required_region_smaller(void *, const char *, int32_t , int32_t , int32_t , int32_t , int32_t );


static int __brighter(buffer_t *_brighter_buffer, buffer_t *_b0_buffer) HALIDE_FUNCTION_ATTRS {
 ap_fixed<12,22> *_brighter = (ap_fixed<12,22> *)(_brighter_buffer->host);
 (void)_brighter;
 const bool _brighter_host_and_dev_are_null = (_brighter_buffer->host == nullptr) && (_brighter_buffer->dev == 0);
 (void)_brighter_host_and_dev_are_null;
 const int32_t _brighter_min_0 = _brighter_buffer->min[0];
 (void)_brighter_min_0;
 const int32_t _brighter_min_1 = _brighter_buffer->min[1];
 (void)_brighter_min_1;
 const int32_t _brighter_min_2 = _brighter_buffer->min[2];
 (void)_brighter_min_2;
 const int32_t _brighter_min_3 = _brighter_buffer->min[3];
 (void)_brighter_min_3;
 const int32_t _brighter_extent_0 = _brighter_buffer->extent[0];
 (void)_brighter_extent_0;
 const int32_t _brighter_extent_1 = _brighter_buffer->extent[1];
 (void)_brighter_extent_1;
 const int32_t _brighter_extent_2 = _brighter_buffer->extent[2];
 (void)_brighter_extent_2;
 const int32_t _brighter_extent_3 = _brighter_buffer->extent[3];
 (void)_brighter_extent_3;
 const int32_t _brighter_stride_0 = _brighter_buffer->stride[0];
 (void)_brighter_stride_0;
 const int32_t _brighter_stride_1 = _brighter_buffer->stride[1];
 (void)_brighter_stride_1;
 const int32_t _brighter_stride_2 = _brighter_buffer->stride[2];
 (void)_brighter_stride_2;
 const int32_t _brighter_stride_3 = _brighter_buffer->stride[3];
 (void)_brighter_stride_3;
 const int32_t _brighter_elem_size = _brighter_buffer->elem_size;
 (void)_brighter_elem_size;
 ap_fixed<12,22> *_b0 = (ap_fixed<12,22> *)(_b0_buffer->host);
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
 bool _0 = !(_b0_host_and_dev_are_null);
 bool _1 = 0 <= _brighter_min_0;
 int32_t _2 = _brighter_min_0 + _brighter_extent_0;
 bool _3 = _2 <= 10;
 bool _4 = _1 && _3;
 bool _5 = _0 || _4;
 if (!_5)  {
  int32_t _6 = _brighter_min_0 + _brighter_extent_0;
  int32_t _7 = _6 + -1;
  int32_t _8 = halide_error_constraints_make_required_region_smaller(nullptr, "Input buffer b0", 0, 0, 9, _brighter_min_0, _7);
  return _8;
 }
 if (_b0_host_and_dev_are_null)
 {
  bool _9 = halide_rewrite_buffer(_b0_buffer, 4, 0, 10, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  (void)_9;
 } // if _b0_host_and_dev_are_null
 if (_brighter_host_and_dev_are_null)
 {
  bool _10 = halide_rewrite_buffer(_brighter_buffer, 4, _brighter_min_0, _brighter_extent_0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  (void)_10;
 } // if _brighter_host_and_dev_are_null
 bool _11 = _b0_host_and_dev_are_null || _brighter_host_and_dev_are_null;
 bool _12 = !(_11);
 if (_12)
 {
  bool _13 = _b0_elem_size == 5;
  if (!_13)   {
   int32_t _14 = halide_error_bad_elem_size(nullptr, "Input buffer b0", "ap_fixed<0,0>34", _b0_elem_size, 5);
   return _14;
  }
  bool _15 = _brighter_elem_size == 5;
  if (!_15)   {
   int32_t _16 = halide_error_bad_elem_size(nullptr, "Output buffer brighter", "ap_fixed<12,22>34", _brighter_elem_size, 5);
   return _16;
  }
  bool _17 = _b0_min_0 <= _brighter_min_0;
  int32_t _18 = _brighter_min_0 + _brighter_extent_0;
  int32_t _19 = _18 - _b0_extent_0;
  bool _20 = _19 <= _b0_min_0;
  bool _21 = _17 && _20;
  if (!_21)   {
   int32_t _22 = _brighter_min_0 + _brighter_extent_0;
   int32_t _23 = _22 + -1;
   int32_t _24 = _b0_min_0 + _b0_extent_0;
   int32_t _25 = _24 + -1;
   int32_t _26 = halide_error_access_out_of_bounds(nullptr, "Input buffer b0", 0, _brighter_min_0, _23, _b0_min_0, _25);
   return _26;
  }
  bool _27 = _b0_stride_0 == 1;
  if (!_27)   {
   int32_t _28 = halide_error_constraint_violated(nullptr, "b0.stride.0", _b0_stride_0, "1", 1);
   return _28;
  }
  bool _29 = _b0_min_0 == 0;
  if (!_29)   {
   int32_t _30 = halide_error_constraint_violated(nullptr, "b0.min.0", _b0_min_0, "0", 0);
   return _30;
  }
  bool _31 = _b0_extent_0 == 10;
  if (!_31)   {
   int32_t _32 = halide_error_constraint_violated(nullptr, "b0.extent.0", _b0_extent_0, "10", 10);
   return _32;
  }
  bool _33 = _brighter_stride_0 == 1;
  if (!_33)   {
   int32_t _34 = halide_error_constraint_violated(nullptr, "brighter.stride.0", _brighter_stride_0, "1", 1);
   return _34;
  }
  int64_t _35 = (int64_t)(_brighter_extent_0);
  int64_t _36 = (int64_t)(2147483647);
  bool _37 = _35 <= _36;
  if (!_37)   {
   int64_t _38 = (int64_t)(_brighter_extent_0);
   int64_t _39 = (int64_t)(2147483647);
   int32_t _40 = halide_error_buffer_allocation_too_large(nullptr, "brighter", _38, _39);
   return _40;
  }
  // produce brighter
  for (int _brighter_s0_x = _brighter_min_0; _brighter_s0_x < _brighter_min_0 + _brighter_extent_0; _brighter_s0_x++)
  {
   int32_t _41 = _brighter_s0_x - _brighter_min_0;
   ap_fixed<0,0> _42 = ((ap_fixed<0,0> *)_b0)[_brighter_s0_x];
   ap_fixed<12,22> _43 = (ap_fixed<12,22>)(_42);
   ap_fixed<12,22> _44 = (ap_fixed<12,22>)(1);
   ap_fixed<12,22> _45 = _43 + _44;
   ap_fixed<0,0> _46 = (ap_fixed<0,0>)(_45);
   ((const ap_fixed<0,0> *)_brighter)[_41] = _46;
  } // for _brighter_s0_x
 } // if _12
 return 0;
}


int brighter(buffer_t *_brighter_buffer) HALIDE_FUNCTION_ATTRS {
 ap_fixed<12,22> *_brighter = (ap_fixed<12,22> *)(_brighter_buffer->host);
 (void)_brighter;
 const bool _brighter_host_and_dev_are_null = (_brighter_buffer->host == nullptr) && (_brighter_buffer->dev == 0);
 (void)_brighter_host_and_dev_are_null;
 const int32_t _brighter_min_0 = _brighter_buffer->min[0];
 (void)_brighter_min_0;
 const int32_t _brighter_min_1 = _brighter_buffer->min[1];
 (void)_brighter_min_1;
 const int32_t _brighter_min_2 = _brighter_buffer->min[2];
 (void)_brighter_min_2;
 const int32_t _brighter_min_3 = _brighter_buffer->min[3];
 (void)_brighter_min_3;
 const int32_t _brighter_extent_0 = _brighter_buffer->extent[0];
 (void)_brighter_extent_0;
 const int32_t _brighter_extent_1 = _brighter_buffer->extent[1];
 (void)_brighter_extent_1;
 const int32_t _brighter_extent_2 = _brighter_buffer->extent[2];
 (void)_brighter_extent_2;
 const int32_t _brighter_extent_3 = _brighter_buffer->extent[3];
 (void)_brighter_extent_3;
 const int32_t _brighter_stride_0 = _brighter_buffer->stride[0];
 (void)_brighter_stride_0;
 const int32_t _brighter_stride_1 = _brighter_buffer->stride[1];
 (void)_brighter_stride_1;
 const int32_t _brighter_stride_2 = _brighter_buffer->stride[2];
 (void)_brighter_stride_2;
 const int32_t _brighter_stride_3 = _brighter_buffer->stride[3];
 (void)_brighter_stride_3;
 const int32_t _brighter_elem_size = _brighter_buffer->elem_size;
 (void)_brighter_elem_size;
 int32_t _47 = __brighter(_brighter_buffer, _b0_buffer);
 bool _48 = _47 == 0;
 if (!_48)  {
  return _47;
 }
 return 0;
}

#ifdef __cplusplus
}  // extern "C"
#endif

#ifndef __VEC4_OPERATIONS_AS_HPP_
#define __VEC4_OPERATIONS_AS_HPP_

#include "vec4.hpp"


extern "C" void add_vec4_serial_as(const vec4* X, const vec4* Y, vec4* Z);
extern "C" void add_vec4_sse_as(const vec4* X, const vec4* Y, vec4* Z);
extern "C" void add_vec4_avx_as(const vec4* X, const vec4* Y, vec4* Z);


#endif//__VEC4_OPERATIONS_AS_HPP_
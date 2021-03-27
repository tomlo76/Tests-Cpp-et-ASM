#ifndef __VEC4_OPERATIONS_ASM_HPP_
#define __VEC4_OPERATIONS_ASM_HPP_

#include "vec4.hpp"


extern "C" void add_vec4_serial_asm(const vec4* X, const vec4* Y, vec4* Z);
extern "C" void add_vec4_sse_asm(const vec4* X, const vec4* Y, vec4* Z);
extern "C" void add_vec4_avx_asm(const vec4* X, const vec4* Y, vec4* Z);


#endif//__VEC4_OPERATIONS_ASM_HPP_
#ifndef __VEC4_OPERATIONS_ASM_WRAPPER_HPP_
#define __VEC4_OPERATIONS_ASM_WRAPPER_HPP_

#include "vec4_operations_asm.hpp"


vec4 add_vec4_serial_asm_wrapper(const vec4& X, const vec4& Y);
vec4 add_vec4_sse_asm_wrapper(const vec4& X, const vec4& Y);
vec4 add_vec4_avx_asm_wrapper(const vec4& X, const vec4& Y);


#endif//__VEC4_OPERATIONS_ASM_WRAPPER_HPP_
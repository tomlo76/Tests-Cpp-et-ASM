#ifndef __VEC4_OPERATIONS_HPP_
#define __VEC4_OPERATIONS_HPP_

#include "vec4.hpp"


vec4 add_compiler(const vec4& X, const vec4& Y);
vec4 add_serial(const vec4& X, const vec4& Y);
vec4 add_sse(const vec4& X, const vec4& Y);
vec4 add_avx(const vec4& X, const vec4& Y);


#endif//__VEC4_OPERATIONS_HPP_
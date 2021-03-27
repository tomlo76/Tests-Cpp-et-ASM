#include "vec4_operations_asm_wrapper.hpp"


vec4 add_vec4_serial_asm_wrapper(const vec4& X, const vec4& Y) {
	vec4 Z;
	
	add_vec4_serial_asm(&X, &Y, &Z);
	
	return Z;
}

vec4 add_vec4_sse_asm_wrapper(const vec4& X, const vec4& Y) {
	vec4 Z;
	
	add_vec4_sse_asm(&X, &Y, &Z);
	
	return Z;
}

vec4 add_vec4_avx_asm_wrapper(const vec4& X, const vec4& Y) {
	vec4 Z;
	
	add_vec4_avx_asm(&X, &Y, &Z);
	
	return Z;
}
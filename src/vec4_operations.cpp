#include "vec4_operations.hpp"



vec4 add_compiler(const vec4& X, const vec4& Y) {
	return { X[0] + Y[0], X[1] + Y[1], X[2] + Y[2], X[3] + Y[3] };
}

/**
 * Addition using serial assembly
 *
 * Use the 128 bits SIMD registers xmm but not the vectorized operation
 */
vec4 add_serial(const vec4& X, const vec4& Y) {
	vec4 Z(0.0, 0.0, 0.0, 0.0);

	vec4* Z_ptr = &Z;
	
	asm volatile (
		"movsd (%[X]), %%xmm0;\n\t"
		"movsd (%[Y]), %%xmm1;\n\t"
		"addsd %%xmm1, %%xmm0;\n\t"
		"movsd %%xmm0, (%[Z]);\n\t"

		"movsd 8(%[X]), %%xmm0;\n\t"
		"movsd 8(%[Y]), %%xmm1;\n\t"
		"addsd %%xmm1, %%xmm0;\n\t"
		"movsd %%xmm0, 8(%[Z]);\n\t"

		"movsd 16(%[X]), %%xmm0;\n\t"
		"movsd 16(%[Y]), %%xmm1;\n\t"
		"addsd %%xmm1, %%xmm0;\n\t"
		"movsd %%xmm0, 16(%[Z]);\n\t"

		"movsd 24(%[X]), %%xmm0;\n\t"
		"movsd 24(%[Y]), %%xmm1;\n\t"
		"addsd %%xmm1, %%xmm0;\n\t"
		"movsd %%xmm0, 24(%[Z]);\n\t"
		: [Z] "+r" (Z_ptr)
		: [X] "r" (&X), [Y] "r" (&Y)
		: "xmm0", "xmm1"
	);
	
	return Z;
}

/**
 * Addition using SSE2 instructions
 * 
 * Use 128 bits xmm registers and vectorized operation
 */
vec4 add_sse(const vec4& X, const vec4& Y) {
	vec4 Z(0.0, 0.0, 0.0, 0.0);

	vec4* Z_ptr = &Z;

	asm volatile (
		"movupd (%[X]), %%xmm0;\n\t"
		"movupd (%[Y]), %%xmm1;\n\t"
		"addpd %%xmm1, %%xmm0;\n\t"
		"movupd %%xmm0, (%[Z]);\n\t"

		"movupd 16(%[X]), %%xmm0;\n\t"
		"movupd 16(%[Y]), %%xmm1;\n\t"
		"addpd %%xmm1, %%xmm0;\n\t"
		"movupd %%xmm0, 16(%[Z]);\n\t"
		: [Z] "+r" (Z_ptr)
		: [X] "r" (&X), [Y] "r" (&Y)
		: "xmm0", "xmm1"
	);

	return Z;	
}

/**
 * Addition using AVX2
 * 
 * Use the 256 bits registers ymm with vectorized operation
 */
vec4 add_avx(const vec4& X, const vec4& Y) {
	vec4 Z(0.0, 0.0, 0.0, 0.0);

	vec4* Z_ptr = &Z;
	
	asm volatile (
		"vmovupd (%[X]), %%ymm1;\n\t"
		"vaddpd (%[Y]), %%ymm1, %%ymm0;\n\t"
		"vmovupd %%ymm0, (%[Z]);\n\t"
		: [Z] "+r" (Z_ptr)
		: [X] "r" (&X), [Y] "r" (&Y)
		: "ymm0", "ymm1"
	);
	
	return Z;
}
#include "vec4.hpp"



vec4::vec4(void) : m_vec{0.0, 0.0, 0.0, 0.0} {}


vec4::vec4(const double vec[4]) : m_vec{vec[0], vec[1], vec[2], vec[3]} {}


vec4::vec4(const double x, const double y, const double z, const double t) : m_vec{x, y, z, t} {}


vec4 add_com(const vec4& X, const vec4& Y) {
	vec4 Z = vec4(X.m_vec[0] + Y.m_vec[0], X.m_vec[1] + Y.m_vec[1], X.m_vec[2] + Y.m_vec[2], X.m_vec[3] + Y.m_vec[3]);
	
	return Z;
}

/**
 * Addition using serial assembly
 *
 * Use the 128 bits SIMD registers xmm but not the vectorized operation
 */
vec4 add_ser(const vec4& X, const vec4& Y) {
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
 * Addition using SSE instructions
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

/**
 * Addition of two vectors
 * 
 * No use of specific assembly code, let the compiler compile
 */
vec4 operator+(const vec4& X, const vec4& Y) {
	return vec4(X.m_vec[0] + Y.m_vec[0], X.m_vec[1] + Y.m_vec[1], X.m_vec[2] + Y.m_vec[2], X.m_vec[3] + Y.m_vec[3]);
}

std::ostream& operator<<(std::ostream& os, const vec4& vec) {
	return os << "(" << vec.m_vec[0] << " ; " << vec.m_vec[1] << " ; " << vec.m_vec[2] << " ; " << vec.m_vec[3] << ")";
}

#ifndef __VEC4_OPERATIONS_HXX__
#define __VEC4_OPERATIONS_HXX__

#include "vec4.hpp"


#define add_vec4_fpu_pp(x, y, z) {                  \
		vec4* Z_ptr = &z;                           \
		asm volatile (                              \
			"fldl (%[X]);               \n\t"       \
			"faddl (%[Y]);              \n\t"       \
			"fstl (%[Z]);               \n\t"       \
			                                        \
			"fldl 8(%[X]);              \n\t"       \
			"faddl 8(%[Y]);             \n\t"       \
			"fstl 8(%[Z]);              \n\t"       \
			                                        \
			"fldl 16(%[X]);             \n\t"       \
			"faddl 16(%[Y]);            \n\t"       \
			"fstl 16(%[Z]);             \n\t"       \
			                                        \
			"fldl 24(%[X]);             \n\t"       \
			"faddl 24(%[Y]);            \n\t"       \
			"fstl 24(%[Z]);             \n\t"       \
			: [Z] "+r" (Z_ptr)                      \
			: [X] "r" (&x), [Y] "r" (&y)            \
			:                                       \
		);                                          \
	}


#define add_vec4_serial_pp(x, y, z) {               \
		vec4* Z_ptr = &z;                           \
		asm volatile (                              \
			"movsd (%[X]), %%xmm0;      \n\t"       \
			"movsd (%[Y]), %%xmm1;      \n\t"       \
			"addsd %%xmm1, %%xmm0;      \n\t"       \
			"movsd %%xmm0, (%[Z]);      \n\t"       \
			                                        \
			"movsd 8(%[X]), %%xmm0;     \n\t"       \
			"movsd 8(%[Y]), %%xmm1;     \n\t"       \
			"addsd %%xmm1, %%xmm0;      \n\t"       \
			"movsd %%xmm0, 8(%[Z]);     \n\t"       \
			                                        \
			"movsd 16(%[X]), %%xmm0;    \n\t"       \
			"movsd 16(%[Y]), %%xmm1;    \n\t"       \
			"addsd %%xmm1, %%xmm0;      \n\t"       \
			"movsd %%xmm0, 16(%[Z]);    \n\t"       \
			                                        \
			"movsd 24(%[X]), %%xmm0;    \n\t"       \
			"movsd 24(%[Y]), %%xmm1;    \n\t"       \
			"addsd %%xmm1, %%xmm0;      \n\t"       \
			"movsd %%xmm0, 24(%[Z]);    \n\t"       \
			: [Z] "+r" (Z_ptr)                      \
			: [X] "r" (&x), [Y] "r" (&y)            \
			: "xmm0", "xmm1"                        \
		);                                          \
	}


#define add_vec4_sse_pp(x, y, z) {                  \
		vec4* Z_ptr = &z;                           \
		asm volatile (                              \
			"movupd (%[X]), %%xmm0;     \n\t"       \
			"movupd (%[Y]), %%xmm1;     \n\t"       \
			"addpd %%xmm1, %%xmm0;      \n\t"       \
			"movupd %%xmm0, (%[Z]);     \n\t"       \
			                                        \
			"movupd 16(%[X]), %%xmm0;   \n\t"       \
			"movupd 16(%[Y]), %%xmm1;   \n\t"       \
			"addpd %%xmm1, %%xmm0;      \n\t"       \
			"movupd %%xmm0, 16(%[Z]);   \n\t"       \
			: [Z] "+r" (Z_ptr)                      \
			: [X] "r" (&x), [Y] "r" (&y)            \
			: "xmm0", "xmm1"                        \
		);                                          \
	}


#define add_vec4_avx_pp(x, y, z) {                  \
		vec4* Z_ptr = &z;                           \
		asm volatile (                              \
			"vmovupd (%[X]), %%ymm1;\n\t"           \
			"vaddpd (%[Y]), %%ymm1, %%ymm0;\n\t"    \
			"vmovupd %%ymm0, (%[Z]);\n\t"           \
			: [Z] "+r" (Z_ptr)                      \
			: [X] "r" (&x), [Y] "r" (&y)            \
			: "ymm0", "ymm1"                        \
		);                                          \
	}


#endif//__VEC4_OPERATIONS_HXX__
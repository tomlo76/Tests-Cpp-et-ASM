	.text

	.globl add_vec4_serial_as
	.globl add_vec4_sse_as
	.globl add_vec4_avx_as

add_vec4_serial_as:
	movsd (%rcx), %xmm0
	movsd (%rdx), %xmm1
	addsd %xmm1, %xmm0
	movsd %xmm0, (%r8)
	
	movsd 8(%rcx), %xmm0
	movsd 8(%rdx), %xmm1
	addsd %xmm1, %xmm0
	movsd %xmm0, 8(%r8)
	
	movsd 16(%rcx), %xmm0
	movsd 16(%rdx), %xmm1
	addsd %xmm1, %xmm0
	movsd %xmm0, 16(%r8)
	
	movsd 24(%rcx), %xmm0
	movsd 24(%rdx), %xmm1
	addsd %xmm1, %xmm0
	movsd %xmm0, 24(%r8)
	
	ret


# void add_vec4_sse_as(const vec4* X, const vec4* Y, const vec4* Z)
#   X -> rcx (rax)
#   Y -> rdx
#   Z -> r8
add_vec4_sse_as:
	movupd (%rcx), %xmm0
	movupd (%rdx), %xmm1
	addpd %xmm1, %xmm0
	movupd %xmm0, (%r8)
	
	movupd 16(%rcx), %xmm0
	movupd 16(%rdx), %xmm1
	addpd %xmm1, %xmm0
	movupd %xmm0, 16(%r8)
	
	ret


# 
add_vec4_avx_as:
	vmovupd (%rcx), %ymm1
	vaddpd (%rdx), %ymm1, %ymm0
	vmovupd %ymm0, (%r8)
	
	ret

	.text

	.globl add_vec4_serial_as
	.globl add_vec4_sse_as
	.globl add_vec4_avx_as

add_vec4_serial_as:
	movsd (%rdi), %xmm0
	movsd (%rsi), %xmm1
	addsd %xmm1, %xmm0
	movsd %xmm0, (%rdx)
	
	movsd 8(%rdi), %xmm0
	movsd 8(%rsi), %xmm1
	addsd %xmm1, %xmm0
	movsd %xmm0, 8(%rdx)
	
	movsd 16(%rdi), %xmm0
	movsd 16(%rsi), %xmm1
	addsd %xmm1, %xmm0
	movsd %xmm0, 16(%rdx)
	
	movsd 24(%rdi), %xmm0
	movsd 24(%rsi), %xmm1
	addsd %xmm1, %xmm0
	movsd %xmm0, 24(%rdx)
	
	ret


# void add_vec4_sse_as(const vec4* X, const vec4* Y, const vec4* Z)
#   X -> rdi (rax)
#   Y -> rsi (rcx)
#   Z -> rdx
add_vec4_sse_as:
	movupd (%rdi), %xmm0
	movupd (%rsi), %xmm1
	addpd %xmm1, %xmm0
	movupd %xmm0, (%rdx)
	
	movupd 16(%rdi), %xmm0
	movupd 16(%rsi), %xmm1
	addpd %xmm1, %xmm0
	movupd %xmm0, 16(%rdx)
	
	ret


# 
add_vec4_avx_as:
	vmovupd (%rdi), %ymm1
	vaddpd (%rsi), %ymm1, %ymm0
	vmovupd %ymm0, (%rdx)
	
	ret

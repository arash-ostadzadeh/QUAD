	.file	"mymath.c"
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.text
.Ltext0:
.globl ldint
	.type	ldint, @function
ldint:
.LFB5:
	.file 1 "mymath.c"
	.loc 1 63 0
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	subq	$24, %rsp
.LCFI2:
	call	mcount
	movl	%edi, -20(%rbp)
	.loc 1 64 0
	movl	$-1, -8(%rbp)
	.loc 1 65 0
	movl	-20(%rbp), %eax
	movl	%eax, -4(%rbp)
	.loc 1 66 0
	jmp	.L2
.L3:
	.loc 1 67 0
	sarl	-4(%rbp)
	.loc 1 68 0
	addl	$1, -8(%rbp)
.L2:
	.loc 1 66 0
	cmpl	$0, -4(%rbp)
	jne	.L3
	.loc 1 71 0
	movl	-8(%rbp), %ecx
	movl	$1, %eax
	sall	%cl, %eax
	cmpl	-20(%rbp), %eax
	jne	.L5
	.loc 1 72 0
	movl	-8(%rbp), %eax
	movl	%eax, -24(%rbp)
	jmp	.L7
.L5:
	.loc 1 74 0
	movl	-8(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
.L7:
	movl	-24(%rbp), %eax
	.loc 1 75 0
	leave
	ret
.LFE5:
	.size	ldint, .-ldint
.globl cadd
	.type	cadd, @function
cadd:
.LFB6:
	.loc 1 79 0
	pushq	%rbp
.LCFI3:
	movq	%rsp, %rbp
.LCFI4:
	subq	$32, %rsp
.LCFI5:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 81 0
	movss	-24(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -16(%rbp)
	.loc 1 82 0
	movss	-20(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 87 0
	movq	-16(%rbp), %rax
	.loc 1 88 0
	movd	%rax, %xmm0
	leave
	ret
.LFE6:
	.size	cadd, .-cadd
.globl csub
	.type	csub, @function
csub:
.LFB7:
	.loc 1 90 0
	pushq	%rbp
.LCFI6:
	movq	%rsp, %rbp
.LCFI7:
	subq	$32, %rsp
.LCFI8:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 92 0
	movss	-24(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	subss	%xmm0, %xmm2
	movaps	%xmm2, %xmm0
	movss	%xmm0, -16(%rbp)
	.loc 1 93 0
	movss	-20(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	subss	%xmm0, %xmm2
	movaps	%xmm2, %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 97 0
	movq	-16(%rbp), %rax
	.loc 1 98 0
	movd	%rax, %xmm0
	leave
	ret
.LFE7:
	.size	csub, .-csub
.globl cmult
	.type	cmult, @function
cmult:
.LFB8:
	.loc 1 100 0
	pushq	%rbp
.LCFI9:
	movq	%rsp, %rbp
.LCFI10:
	subq	$32, %rsp
.LCFI11:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 104 0
	movss	-24(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	.loc 1 105 0
	movss	-20(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 106 0
	movss	-8(%rbp), %xmm0
	subss	-4(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	.loc 1 107 0
	movss	-24(%rbp), %xmm1
	movss	-20(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	addss	%xmm0, %xmm2
	movss	-32(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	addss	%xmm1, %xmm0
	mulss	%xmm2, %xmm0
	subss	-8(%rbp), %xmm0
	subss	-4(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 118 0
	movq	-16(%rbp), %rax
	.loc 1 119 0
	movd	%rax, %xmm0
	leave
	ret
.LFE8:
	.size	cmult, .-cmult
.globl cdiv
	.type	cdiv, @function
cdiv:
.LFB9:
	.loc 1 121 0
	pushq	%rbp
.LCFI12:
	movq	%rsp, %rbp
.LCFI13:
	subq	$32, %rsp
.LCFI14:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 124 0
	movss	-32(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movss	-28(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	addss	%xmm2, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 125 0
	movss	-24(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movss	-20(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	addss	%xmm2, %xmm0
	divss	-4(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	.loc 1 126 0
	movss	-20(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movss	-24(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movaps	%xmm2, %xmm1
	subss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	divss	-4(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 131 0
	movq	-16(%rbp), %rax
	.loc 1 132 0
	movd	%rax, %xmm0
	leave
	ret
.LFE9:
	.size	cdiv, .-cdiv
.globl csmult
	.type	csmult, @function
csmult:
.LFB10:
	.loc 1 134 0
	pushq	%rbp
.LCFI15:
	movq	%rsp, %rbp
.LCFI16:
	subq	$32, %rsp
.LCFI17:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movss	%xmm1, -28(%rbp)
	.loc 1 136 0
	movss	-24(%rbp), %xmm0
	mulss	-28(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	.loc 1 137 0
	movss	-20(%rbp), %xmm0
	mulss	-28(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 141 0
	movq	-16(%rbp), %rax
	.loc 1 142 0
	movd	%rax, %xmm0
	leave
	ret
.LFE10:
	.size	csmult, .-csmult
.globl csdiv
	.type	csdiv, @function
csdiv:
.LFB11:
	.loc 1 144 0
	pushq	%rbp
.LCFI18:
	movq	%rsp, %rbp
.LCFI19:
	subq	$32, %rsp
.LCFI20:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movss	%xmm1, -28(%rbp)
	.loc 1 146 0
	movss	-24(%rbp), %xmm0
	divss	-28(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	.loc 1 147 0
	movss	-20(%rbp), %xmm0
	divss	-28(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 151 0
	movq	-16(%rbp), %rax
	.loc 1 152 0
	movd	%rax, %xmm0
	leave
	ret
.LFE11:
	.size	csdiv, .-csdiv
.globl cmag
	.type	cmag, @function
cmag:
.LFB12:
	.loc 1 154 0
	pushq	%rbp
.LCFI21:
	movq	%rsp, %rbp
.LCFI22:
	subq	$32, %rsp
.LCFI23:
	call	mcount
	movq	%xmm0, -8(%rbp)
	.loc 1 160 0
	movss	-8(%rbp), %xmm1
	movss	-8(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movss	-4(%rbp), %xmm1
	movss	-4(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	addss	%xmm2, %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
	sqrtsd	-16(%rbp), %xmm0
	movsd	%xmm0, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	ucomisd	-24(%rbp), %xmm0
	jp	.L24
	je	.L22
.L24:
	movsd	-16(%rbp), %xmm0
	call	sqrt
	movsd	%xmm0, -24(%rbp)
.L22:
	movsd	-24(%rbp), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -28(%rbp)
	movl	-28(%rbp), %eax
	.loc 1 161 0
	movl	%eax, -28(%rbp)
	movss	-28(%rbp), %xmm0
	leave
	ret
.LFE12:
	.size	cmag, .-cmag
.globl _carg
	.type	_carg, @function
_carg:
.LFB13:
	.loc 1 163 0
	pushq	%rbp
.LCFI24:
	movq	%rsp, %rbp
.LCFI25:
	subq	$16, %rsp
.LCFI26:
	call	mcount
	movq	%xmm0, -8(%rbp)
	.loc 1 167 0
	movss	-8(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm1
	movss	-4(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	call	atan2
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movl	-12(%rbp), %eax
	.loc 1 168 0
	movl	%eax, -12(%rbp)
	movss	-12(%rbp), %xmm0
	leave
	ret
.LFE13:
	.size	_carg, .-_carg
.globl _cexp
	.type	_cexp, @function
_cexp:
.LFB14:
	.loc 1 170 0
	pushq	%rbp
.LCFI27:
	movq	%rsp, %rbp
.LCFI28:
	subq	$48, %rsp
.LCFI29:
	call	mcount
	movss	%xmm0, -20(%rbp)
	movss	%xmm1, -24(%rbp)
	.loc 1 172 0
	cvtss2sd	-20(%rbp), %xmm0
	movsd	%xmm0, -40(%rbp)
	cvtss2sd	-24(%rbp), %xmm0
	call	cos
	mulsd	-40(%rbp), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	.loc 1 173 0
	cvtss2sd	-20(%rbp), %xmm0
	movsd	%xmm0, -32(%rbp)
	cvtss2sd	-24(%rbp), %xmm0
	call	sin
	mulsd	-32(%rbp), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 178 0
	movq	-16(%rbp), %rax
	.loc 1 179 0
	movd	%rax, %xmm0
	leave
	ret
.LFE14:
	.size	_cexp, .-_cexp
.globl r2c
	.type	r2c, @function
r2c:
.LFB15:
	.loc 1 181 0
	pushq	%rbp
.LCFI30:
	movq	%rsp, %rbp
.LCFI31:
	subq	$40, %rsp
.LCFI32:
	call	mcount
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	.loc 1 183 0
	movl	$0, -4(%rbp)
	jmp	.L30
.L31:
	.loc 1 184 0
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-32(%rbp), %rdx
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	.loc 1 185 0
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-32(%rbp), %rdx
	movl	$0x00000000, %eax
	movl	%eax, 4(%rdx)
	.loc 1 183 0
	addl	$1, -4(%rbp)
.L30:
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L31
	.loc 1 187 0
	movl	$0, %eax
	.loc 1 188 0
	leave
	ret
.LFE15:
	.size	r2c, .-r2c
.globl c2r
	.type	c2r, @function
c2r:
.LFB16:
	.loc 1 190 0
	pushq	%rbp
.LCFI33:
	movq	%rsp, %rbp
.LCFI34:
	pushq	%rbx
.LCFI35:
	subq	$56, %rsp
.LCFI36:
	call	mcount
	movq	%rdi, -32(%rbp)
	movq	%rsi, -40(%rbp)
	movl	%edx, -44(%rbp)
	movl	%ecx, -48(%rbp)
	.loc 1 192 0
	movl	$0, -12(%rbp)
	jmp	.L35
.L36:
	.loc 1 193 0
	cmpl	$0, -48(%rbp)
	jne	.L37
	.loc 1 194 0
	movl	-12(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdx
	addq	-40(%rbp), %rdx
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-32(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	jmp	.L39
.L37:
	.loc 1 195 0
	cmpl	$1, -48(%rbp)
	jne	.L40
	.loc 1 196 0
	movl	-12(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdx
	addq	-40(%rbp), %rdx
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-32(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, (%rdx)
	jmp	.L39
.L40:
	.loc 1 197 0
	cmpl	$2, -48(%rbp)
	jne	.L42
	.loc 1 198 0
	movl	-12(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rbx
	addq	-40(%rbp), %rbx
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-32(%rbp), %rax
	movq	(%rax), %xmm0
	call	cmag
	movss	%xmm0, -60(%rbp)
	movl	-60(%rbp), %eax
	movl	%eax, (%rbx)
	jmp	.L39
.L42:
	.loc 1 199 0
	cmpl	$3, -48(%rbp)
	jne	.L44
	.loc 1 200 0
	movl	-12(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rbx
	addq	-40(%rbp), %rbx
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-32(%rbp), %rax
	movq	(%rax), %xmm0
	call	_carg
	movss	%xmm0, -60(%rbp)
	movl	-60(%rbp), %eax
	movl	%eax, (%rbx)
	jmp	.L39
.L44:
	.loc 1 203 0
	movl	$-1, -52(%rbp)
	jmp	.L46
.L39:
	.loc 1 192 0
	addl	$1, -12(%rbp)
.L35:
	movl	-12(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L36
	.loc 1 206 0
	movl	$0, -52(%rbp)
.L46:
	movl	-52(%rbp), %eax
	.loc 1 207 0
	addq	$56, %rsp
	popq	%rbx
	leave
	ret
.LFE16:
	.size	c2r, .-c2r
	.section	.rodata
	.align 8
.LC1:
	.long	1413754140
	.long	1075388923
	.align 16
.LC2:
	.long	2147483648
	.long	0
	.long	0
	.long	0
	.text
.globl ffw
	.type	ffw, @function
ffw:
.LFB17:
	.loc 1 215 0
	pushq	%rbp
.LCFI37:
	movq	%rsp, %rbp
.LCFI38:
	pushq	%rbx
.LCFI39:
	subq	$40, %rsp
.LCFI40:
	call	mcount
	movq	%rdi, -32(%rbp)
	movl	%esi, -36(%rbp)
	movl	%edx, -40(%rbp)
	.loc 1 219 0
	cvtsi2sd	-36(%rbp), %xmm1
	movsd	.LC1(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	cvtsi2sd	-40(%rbp), %xmm0
	movapd	%xmm1, %xmm2
	divsd	%xmm0, %xmm2
	movapd	%xmm2, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 222 0
	movl	$0, -20(%rbp)
	jmp	.L50
.L51:
	.loc 1 223 0
	cvtsi2ss	-20(%rbp), %xmm0
	mulss	-12(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	.loc 1 224 0
	movl	-20(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rbx
	addq	-32(%rbp), %rbx
	cvtss2sd	-16(%rbp), %xmm0
	call	cos
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, (%rbx)
	.loc 1 225 0
	movl	-20(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rbx
	addq	-32(%rbp), %rbx
	cvtss2sd	-16(%rbp), %xmm0
	call	sin
	cvtsd2ss	%xmm0, %xmm1
	movss	.LC2(%rip), %xmm0
	xorps	%xmm1, %xmm0
	movss	%xmm0, 4(%rbx)
	.loc 1 222 0
	addl	$1, -20(%rbp)
.L50:
	movl	-40(%rbp), %edx
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	cmpl	-20(%rbp), %eax
	jg	.L51
	.loc 1 230 0
	addq	$40, %rsp
	popq	%rbx
	leave
	ret
.LFE17:
	.size	ffw, .-ffw
.globl bitrev
	.type	bitrev, @function
bitrev:
.LFB18:
	.loc 1 232 0
	pushq	%rbp
.LCFI41:
	movq	%rsp, %rbp
.LCFI42:
	subq	$24, %rsp
.LCFI43:
	call	mcount
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	.loc 1 234 0
	movl	$0, -8(%rbp)
	.loc 1 236 0
	movl	$1, -4(%rbp)
	jmp	.L55
.L56:
	.loc 1 237 0
	movl	-4(%rbp), %ecx
	subl	$1, %ecx
	movl	-20(%rbp), %eax
	sarl	%cl, %eax
	movl	%eax, %esi
	andl	$1, %esi
	movl	-4(%rbp), %edx
	movl	-24(%rbp), %eax
	movl	%eax, %ecx
	subl	%edx, %ecx
	movl	%esi, %eax
	sall	%cl, %eax
	orl	%eax, -8(%rbp)
	.loc 1 236 0
	addl	$1, -4(%rbp)
.L55:
	movl	-4(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jle	.L56
	.loc 1 239 0
	movl	-8(%rbp), %eax
	.loc 1 240 0
	leave
	ret
.LFE18:
	.size	bitrev, .-bitrev
.globl perm
	.type	perm, @function
perm:
.LFB19:
	.loc 1 243 0
	pushq	%rbp
.LCFI44:
	movq	%rsp, %rbp
.LCFI45:
	subq	$32, %rsp
.LCFI46:
	call	mcount
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	.loc 1 246 0
	movl	-28(%rbp), %ecx
	movl	$1, %eax
	sall	%cl, %eax
	movl	%eax, -16(%rbp)
	.loc 1 247 0
	movl	$0, -12(%rbp)
	jmp	.L60
.L61:
	.loc 1 248 0
	movl	-28(%rbp), %esi
	movl	-12(%rbp), %edi
	call	bitrev
	movl	%eax, -8(%rbp)
	.loc 1 249 0
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jle	.L62
	.loc 1 250 0
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, (%rdx)
	.loc 1 251 0
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, 4(%rdx)
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, 4(%rdx)
.L62:
	.loc 1 247 0
	addl	$1, -12(%rbp)
.L60:
	movl	-12(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jl	.L61
	.loc 1 254 0
	leave
	ret
.LFE19:
	.size	perm, .-perm
.globl permrev
	.type	permrev, @function
permrev:
.LFB20:
	.loc 1 263 0
	pushq	%rbp
.LCFI47:
	movq	%rsp, %rbp
.LCFI48:
	subq	$32, %rsp
.LCFI49:
	call	mcount
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	.loc 1 266 0
	movl	-28(%rbp), %ecx
	movl	$1, %eax
	sall	%cl, %eax
	movl	%eax, -16(%rbp)
	.loc 1 268 0
	movl	$0, -12(%rbp)
	jmp	.L67
.L68:
	.loc 1 269 0
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rcx
	addq	-24(%rbp), %rcx
	movl	-16(%rbp), %edx
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	addl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, (%rcx)
	movl	-16(%rbp), %edx
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	addl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, (%rdx)
	.loc 1 270 0
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rcx
	addq	-24(%rbp), %rcx
	movl	-16(%rbp), %edx
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	addl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, 4(%rcx)
	movl	-16(%rbp), %edx
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	addl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, 4(%rdx)
	.loc 1 268 0
	addl	$1, -12(%rbp)
.L67:
	movl	-16(%rbp), %edx
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	cmpl	-12(%rbp), %eax
	jg	.L68
	.loc 1 272 0
	movl	$0, -12(%rbp)
	jmp	.L70
.L71:
	.loc 1 273 0
	movl	-28(%rbp), %esi
	movl	-12(%rbp), %edi
	call	bitrev
	movl	%eax, -8(%rbp)
	.loc 1 274 0
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jle	.L72
	.loc 1 275 0
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, (%rdx)
	.loc 1 276 0
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, 4(%rdx)
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, 4(%rdx)
.L72:
	.loc 1 272 0
	addl	$1, -12(%rbp)
.L70:
	movl	-12(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jl	.L71
	.loc 1 279 0
	leave
	ret
.LFE20:
	.size	permrev, .-permrev
.globl permcpy
	.type	permcpy, @function
permcpy:
.LFB21:
	.loc 1 281 0
	pushq	%rbp
.LCFI50:
	movq	%rsp, %rbp
.LCFI51:
	subq	$24, %rsp
.LCFI52:
	call	mcount
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	.loc 1 282 0
	movl	-20(%rbp), %ecx
	movl	$1, %eax
	sall	%cl, %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	cld
	rep
	movsb
	.loc 1 283 0
	movl	-20(%rbp), %esi
	movq	-16(%rbp), %rdi
	call	perm
	.loc 1 286 0
	leave
	ret
.LFE21:
	.size	permcpy, .-permcpy
.globl permrevcpy
	.type	permrevcpy, @function
permrevcpy:
.LFB22:
	.loc 1 288 0
	pushq	%rbp
.LCFI53:
	movq	%rsp, %rbp
.LCFI54:
	subq	$24, %rsp
.LCFI55:
	call	mcount
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	.loc 1 289 0
	movl	-20(%rbp), %ecx
	movl	$1, %eax
	sall	%cl, %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rax, %rdi
	movq	%rdx, %rsi
	cld
	rep
	movsb
	.loc 1 290 0
	movl	-20(%rbp), %esi
	movq	-16(%rbp), %rdi
	call	permrev
	.loc 1 293 0
	leave
	ret
.LFE22:
	.size	permrevcpy, .-permrevcpy
.globl fft1d
	.type	fft1d, @function
fft1d:
.LFB23:
	.loc 1 295 0
	pushq	%rbp
.LCFI56:
	movq	%rsp, %rbp
.LCFI57:
	subq	$80, %rsp
.LCFI58:
	call	mcount
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movl	%edx, -68(%rbp)
	movl	%ecx, -72(%rbp)
	.loc 1 299 0
	movl	-72(%rbp), %eax
	movl	%eax, -16(%rbp)
	.loc 1 300 0
	movl	$1, -24(%rbp)
	.loc 1 302 0
	jmp	.L81
.L82:
	.loc 1 303 0
	movl	-16(%rbp), %edx
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, -16(%rbp)
	.loc 1 304 0
	movl	-24(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, -20(%rbp)
	.loc 1 305 0
	movl	$0, -36(%rbp)
	.loc 1 306 0
	movl	$0, -12(%rbp)
	jmp	.L83
.L84:
	.loc 1 307 0
	movl	$0, -8(%rbp)
	.loc 1 308 0
	movl	$0, -4(%rbp)
	jmp	.L85
.L86:
	.loc 1 309 0
	movl	-4(%rbp), %eax
	addl	-36(%rbp), %eax
	movl	%eax, -32(%rbp)
	.loc 1 310 0
	movl	-24(%rbp), %eax
	addl	-32(%rbp), %eax
	movl	%eax, -28(%rbp)
	.loc 1 311 0
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-64(%rbp), %rax
	movss	(%rax), %xmm1
	movl	-28(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-56(%rbp), %rax
	movss	(%rax), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-64(%rbp), %rax
	movss	4(%rax), %xmm1
	movl	-28(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-56(%rbp), %rax
	movss	4(%rax), %xmm0
	mulss	%xmm1, %xmm0
	movaps	%xmm2, %xmm1
	subss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	movss	%xmm0, -48(%rbp)
	.loc 1 312 0
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-64(%rbp), %rax
	movss	(%rax), %xmm1
	movl	-28(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-56(%rbp), %rax
	movss	4(%rax), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-64(%rbp), %rax
	movss	4(%rax), %xmm1
	movl	-28(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-56(%rbp), %rax
	movss	(%rax), %xmm0
	mulss	%xmm1, %xmm0
	addss	%xmm2, %xmm0
	movss	%xmm0, -44(%rbp)
	.loc 1 313 0
	movl	-28(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-56(%rbp), %rdx
	movl	-32(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-56(%rbp), %rax
	movss	(%rax), %xmm1
	movss	-48(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	subss	%xmm0, %xmm2
	movaps	%xmm2, %xmm0
	movss	%xmm0, (%rdx)
	.loc 1 314 0
	movl	-28(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-56(%rbp), %rdx
	movl	-32(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-56(%rbp), %rax
	movss	4(%rax), %xmm1
	movss	-44(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	subss	%xmm0, %xmm2
	movaps	%xmm2, %xmm0
	movss	%xmm0, 4(%rdx)
	.loc 1 315 0
	movl	-32(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-56(%rbp), %rdx
	movl	-32(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-56(%rbp), %rax
	movss	(%rax), %xmm1
	movss	-48(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, (%rdx)
	.loc 1 316 0
	movl	-32(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-56(%rbp), %rdx
	movl	-32(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-56(%rbp), %rax
	movss	4(%rax), %xmm1
	movss	-44(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, 4(%rdx)
	.loc 1 317 0
	movl	-16(%rbp), %eax
	addl	%eax, -8(%rbp)
	.loc 1 308 0
	addl	$1, -4(%rbp)
.L85:
	movl	-4(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L86
	.loc 1 321 0
	movl	-20(%rbp), %eax
	addl	%eax, -36(%rbp)
	.loc 1 306 0
	addl	$1, -12(%rbp)
.L83:
	movl	-12(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jl	.L84
	.loc 1 323 0
	movl	-20(%rbp), %eax
	movl	%eax, -24(%rbp)
.L81:
	.loc 1 302 0
	cmpl	$1, -16(%rbp)
	jg	.L82
	.loc 1 327 0
	cmpl	$0, -68(%rbp)
	jns	.L94
	.loc 1 328 0
	movl	$0, -36(%rbp)
	jmp	.L92
.L93:
	.loc 1 329 0
	movl	-36(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-56(%rbp), %rdx
	movl	-36(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-56(%rbp), %rax
	movss	(%rax), %xmm1
	cvtsi2ss	-72(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	divss	%xmm0, %xmm2
	movaps	%xmm2, %xmm0
	movss	%xmm0, (%rdx)
	.loc 1 330 0
	movl	-36(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-56(%rbp), %rdx
	movl	-36(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-56(%rbp), %rax
	movss	4(%rax), %xmm1
	cvtsi2ss	-72(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	divss	%xmm0, %xmm2
	movaps	%xmm2, %xmm0
	movss	%xmm0, 4(%rdx)
	.loc 1 328 0
	addl	$1, -36(%rbp)
.L92:
	movl	-36(%rbp), %eax
	cmpl	-72(%rbp), %eax
	jl	.L93
.L94:
	.loc 1 337 0
	leave
	ret
.LFE23:
	.size	fft1d, .-fft1d
.globl fftrev
	.type	fftrev, @function
fftrev:
.LFB24:
	.loc 1 339 0
	pushq	%rbp
.LCFI59:
	movq	%rsp, %rbp
.LCFI60:
	subq	$32, %rsp
.LCFI61:
	call	mcount
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	.loc 1 341 0
	movl	-20(%rbp), %esi
	movq	-8(%rbp), %rdi
	call	permrev
	.loc 1 344 0
	movl	-20(%rbp), %ecx
	movl	$1, %eax
	movl	%eax, %edx
	sall	%cl, %edx
	movl	%edx, %ecx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rdi
	movl	$1, %edx
	call	fft1d
	.loc 1 345 0
	leave
	ret
.LFE24:
	.size	fftrev, .-fftrev
.globl fft
	.type	fft, @function
fft:
.LFB25:
	.loc 1 347 0
	pushq	%rbp
.LCFI62:
	movq	%rsp, %rbp
.LCFI63:
	subq	$32, %rsp
.LCFI64:
	call	mcount
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	.loc 1 349 0
	movl	-20(%rbp), %esi
	movq	-8(%rbp), %rdi
	call	perm
	.loc 1 352 0
	movl	-20(%rbp), %ecx
	movl	$1, %eax
	movl	%eax, %edx
	sall	%cl, %edx
	movl	%edx, %ecx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rdi
	movl	$1, %edx
	call	fft1d
	.loc 1 353 0
	leave
	ret
.LFE25:
	.size	fft, .-fft
.globl ifft
	.type	ifft, @function
ifft:
.LFB26:
	.loc 1 356 0
	pushq	%rbp
.LCFI65:
	movq	%rsp, %rbp
.LCFI66:
	subq	$32, %rsp
.LCFI67:
	call	mcount
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	.loc 1 358 0
	movl	-20(%rbp), %esi
	movq	-8(%rbp), %rdi
	call	perm
	.loc 1 361 0
	movl	-20(%rbp), %ecx
	movl	$1, %eax
	movl	%eax, %edx
	sall	%cl, %edx
	movl	%edx, %ecx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rdi
	movl	$-1, %edx
	call	fft1d
	.loc 1 363 0
	leave
	ret
.LFE26:
	.size	ifft, .-ifft
.globl ifftr
	.type	ifftr, @function
ifftr:
.LFB27:
	.loc 1 365 0
	pushq	%rbp
.LCFI68:
	movq	%rsp, %rbp
.LCFI69:
	subq	$24, %rsp
.LCFI70:
	call	mcount
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	.loc 1 369 0
	leave
	ret
.LFE27:
	.size	ifftr, .-ifftr
.globl fftcpy
	.type	fftcpy, @function
fftcpy:
.LFB28:
	.loc 1 372 0
	pushq	%rbp
.LCFI71:
	movq	%rsp, %rbp
.LCFI72:
	subq	$32, %rsp
.LCFI73:
	call	mcount
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movl	%ecx, -28(%rbp)
	.loc 1 374 0
	movl	-28(%rbp), %edx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rdi
	call	permcpy
	.loc 1 377 0
	movl	-28(%rbp), %ecx
	movl	$1, %eax
	movl	%eax, %edx
	sall	%cl, %edx
	movl	%edx, %ecx
	movq	-24(%rbp), %rsi
	movq	-16(%rbp), %rdi
	movl	$1, %edx
	call	fft1d
	.loc 1 378 0
	leave
	ret
.LFE28:
	.size	fftcpy, .-fftcpy
.globl ifftcpy
	.type	ifftcpy, @function
ifftcpy:
.LFB29:
	.loc 1 380 0
	pushq	%rbp
.LCFI74:
	movq	%rsp, %rbp
.LCFI75:
	subq	$32, %rsp
.LCFI76:
	call	mcount
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movl	%ecx, -28(%rbp)
	.loc 1 382 0
	movl	-28(%rbp), %edx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rdi
	call	permcpy
	.loc 1 385 0
	movl	-28(%rbp), %ecx
	movl	$1, %eax
	movl	%eax, %edx
	sall	%cl, %edx
	movl	%edx, %ecx
	movq	-24(%rbp), %rsi
	movq	-16(%rbp), %rdi
	movl	$-1, %edx
	call	fft1d
	.loc 1 386 0
	leave
	ret
.LFE29:
	.size	ifftcpy, .-ifftcpy
.globl fconv
	.type	fconv, @function
fconv:
.LFB30:
	.loc 1 390 0
	pushq	%rbp
.LCFI77:
	movq	%rsp, %rbp
.LCFI78:
	pushq	%rbx
.LCFI79:
	subq	$88, %rsp
.LCFI80:
	call	mcount
	movq	%rdi, -48(%rbp)
	movq	%rsi, -56(%rbp)
	movq	%rdx, -64(%rbp)
	movq	%rcx, -72(%rbp)
	movq	%r8, -80(%rbp)
	movl	%r9d, -84(%rbp)
	.loc 1 392 0
	movl	-84(%rbp), %ecx
	movl	$1, %eax
	sall	%cl, %eax
	movl	%eax, -16(%rbp)
	.loc 1 394 0
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdi
	call	malloc
	movq	%rax, -32(%rbp)
	.loc 1 395 0
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdi
	call	malloc
	movq	%rax, -24(%rbp)
	.loc 1 397 0
	movl	-84(%rbp), %ecx
	movq	-72(%rbp), %rdx
	movq	-32(%rbp), %rsi
	movq	-48(%rbp), %rdi
	call	fftcpy
	.loc 1 398 0
	movl	-84(%rbp), %ecx
	movq	-72(%rbp), %rdx
	movq	-24(%rbp), %rsi
	movq	-56(%rbp), %rdi
	call	fftcpy
	.loc 1 400 0
	movl	$0, -12(%rbp)
	jmp	.L108
.L109:
	.loc 1 401 0
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rbx
	addq	-32(%rbp), %rbx
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	-12(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-32(%rbp), %rax
	movq	(%rdx), %xmm1
	movq	(%rax), %xmm0
	call	cmult
	movd	%xmm0, %rax
	movq	%rax, (%rbx)
	.loc 1 400 0
	addl	$1, -12(%rbp)
.L108:
	movl	-12(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jl	.L109
	.loc 1 404 0
	movl	-84(%rbp), %ecx
	movq	-80(%rbp), %rdx
	movq	-64(%rbp), %rsi
	movq	-32(%rbp), %rdi
	call	ifftcpy
	.loc 1 406 0
	movq	-32(%rbp), %rdi
	call	free
	.loc 1 407 0
	movq	-24(%rbp), %rdi
	call	free
	.loc 1 408 0
	addq	$88, %rsp
	popq	%rbx
	leave
	ret
.LFE30:
	.size	fconv, .-fconv
.globl fwconv
	.type	fwconv, @function
fwconv:
.LFB31:
	.loc 1 410 0
	pushq	%rbp
.LCFI81:
	movq	%rsp, %rbp
.LCFI82:
	subq	$64, %rsp
.LCFI83:
	call	mcount
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movl	%ecx, -60(%rbp)
	.loc 1 412 0
	movl	-60(%rbp), %ecx
	movl	$1, %eax
	sall	%cl, %eax
	movl	%eax, -4(%rbp)
	.loc 1 414 0
	movl	-4(%rbp), %edx
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	cltq
	leaq	0(,%rax,8), %rdi
	call	malloc
	movq	%rax, -24(%rbp)
	.loc 1 415 0
	movl	-4(%rbp), %edx
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	cltq
	leaq	0(,%rax,8), %rdi
	call	malloc
	movq	%rax, -16(%rbp)
	.loc 1 418 0
	movl	-4(%rbp), %edx
	movq	-24(%rbp), %rdi
	movl	$1, %esi
	call	ffw
	.loc 1 419 0
	movl	-4(%rbp), %edx
	movq	-16(%rbp), %rdi
	movl	$-1, %esi
	call	ffw
	.loc 1 421 0
	movl	-60(%rbp), %eax
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-56(%rbp), %rsi
	movq	-48(%rbp), %rdi
	movq	-40(%rbp), %r10
	movl	%eax, %r9d
	movq	%rdx, %r8
	movq	%rsi, %rdx
	movq	%rdi, %rsi
	movq	%r10, %rdi
	call	fconv
	.loc 1 423 0
	movq	-24(%rbp), %rdi
	call	free
	.loc 1 424 0
	movq	-16(%rbp), %rdi
	call	free
	.loc 1 425 0
	leave
	ret
.LFE31:
	.size	fwconv, .-fwconv
.globl tconv
	.type	tconv, @function
tconv:
.LFB32:
	.loc 1 427 0
	pushq	%rbp
.LCFI84:
	movq	%rsp, %rbp
.LCFI85:
	pushq	%rbx
.LCFI86:
	subq	$56, %rsp
.LCFI87:
	call	mcount
	movq	%rdi, -32(%rbp)
	movl	%esi, -36(%rbp)
	movq	%rdx, -48(%rbp)
	movl	%ecx, -52(%rbp)
	movq	%r8, -64(%rbp)
	.loc 1 429 0
	movl	-52(%rbp), %eax
	addl	-36(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -12(%rbp)
	.loc 1 431 0
	movl	$0, -20(%rbp)
	jmp	.L115
.L116:
	.loc 1 432 0
	movl	-20(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-64(%rbp), %rdx
	movl	$0x00000000, %eax
	movl	%eax, (%rdx)
	.loc 1 433 0
	movl	-20(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-64(%rbp), %rdx
	movl	$0x00000000, %eax
	movl	%eax, 4(%rdx)
	.loc 1 431 0
	addl	$1, -20(%rbp)
.L115:
	movl	-20(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jl	.L116
	.loc 1 437 0
	movl	$0, -20(%rbp)
	jmp	.L118
.L119:
	.loc 1 439 0
	movl	$0, -16(%rbp)
	jmp	.L120
.L121:
	.loc 1 440 0
	movl	-16(%rbp), %eax
	addl	-20(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rbx
	addq	-64(%rbp), %rbx
	movl	-16(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-48(%rbp), %rdx
	movl	-20(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-32(%rbp), %rax
	movq	(%rdx), %xmm1
	movq	(%rax), %xmm0
	call	cmult
	movd	%xmm0, %rax
	movq	%rax, %rdx
	movl	-16(%rbp), %eax
	addl	-20(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-64(%rbp), %rax
	movd	%rdx, %xmm1
	movq	(%rax), %xmm0
	call	cadd
	movd	%xmm0, %rax
	movq	%rax, (%rbx)
	.loc 1 439 0
	addl	$1, -16(%rbp)
.L120:
	movl	-16(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L121
	.loc 1 437 0
	addl	$1, -20(%rbp)
.L118:
	movl	-20(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L119
	.loc 1 443 0
	addq	$56, %rsp
	popq	%rbx
	leave
	ret
.LFE32:
	.size	tconv, .-tconv
.globl vadd
	.type	vadd, @function
vadd:
.LFB33:
	.loc 1 459 0
	pushq	%rbp
.LCFI88:
	movq	%rsp, %rbp
.LCFI89:
	subq	$48, %rsp
.LCFI90:
	call	mcount
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movq	%rcx, -48(%rbp)
	.loc 1 461 0
	movl	$0, -4(%rbp)
	jmp	.L126
.L127:
	.loc 1 462 0
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdx
	addq	-48(%rbp), %rdx
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-24(%rbp), %rax
	movss	(%rax), %xmm1
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-32(%rbp), %rax
	movss	(%rax), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, (%rdx)
	.loc 1 461 0
	addl	$1, -4(%rbp)
.L126:
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L127
	.loc 1 467 0
	leave
	ret
.LFE33:
	.size	vadd, .-vadd
.globl vsub
	.type	vsub, @function
vsub:
.LFB34:
	.loc 1 469 0
	pushq	%rbp
.LCFI91:
	movq	%rsp, %rbp
.LCFI92:
	subq	$48, %rsp
.LCFI93:
	call	mcount
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movq	%rcx, -48(%rbp)
	.loc 1 471 0
	movl	$0, -4(%rbp)
	jmp	.L131
.L132:
	.loc 1 472 0
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdx
	addq	-48(%rbp), %rdx
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-24(%rbp), %rax
	movss	(%rax), %xmm1
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-32(%rbp), %rax
	movss	(%rax), %xmm0
	movaps	%xmm1, %xmm2
	subss	%xmm0, %xmm2
	movaps	%xmm2, %xmm0
	movss	%xmm0, (%rdx)
	.loc 1 471 0
	addl	$1, -4(%rbp)
.L131:
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L132
	.loc 1 477 0
	leave
	ret
.LFE34:
	.size	vsub, .-vsub
.globl vdotprod
	.type	vdotprod, @function
vdotprod:
.LFB35:
	.loc 1 479 0
	pushq	%rbp
.LCFI94:
	movq	%rsp, %rbp
.LCFI95:
	subq	$48, %rsp
.LCFI96:
	call	mcount
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 1 481 0
	movl	$0x00000000, %eax
	movl	%eax, -4(%rbp)
	.loc 1 482 0
	movl	$0, -8(%rbp)
	jmp	.L136
.L137:
	.loc 1 483 0
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-24(%rbp), %rax
	movss	(%rax), %xmm1
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-40(%rbp), %rax
	movss	(%rax), %xmm0
	mulss	%xmm0, %xmm1
	movss	-4(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 482 0
	addl	$1, -8(%rbp)
.L136:
	movl	-8(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L137
	.loc 1 489 0
	movl	-4(%rbp), %eax
	.loc 1 490 0
	movl	%eax, -44(%rbp)
	movss	-44(%rbp), %xmm0
	leave
	ret
.LFE35:
	.size	vdotprod, .-vdotprod
.globl vcrossprod
	.type	vcrossprod, @function
vcrossprod:
.LFB36:
	.loc 1 492 0
	pushq	%rbp
.LCFI97:
	movq	%rsp, %rbp
.LCFI98:
	subq	$32, %rsp
.LCFI99:
	call	mcount
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movq	%rcx, -32(%rbp)
	.loc 1 493 0
	cmpl	$3, -20(%rbp)
	jne	.L143
	.loc 1 497 0
	movq	-8(%rbp), %rax
	addq	$4, %rax
	movss	(%rax), %xmm1
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movss	(%rax), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movss	(%rax), %xmm1
	movq	-16(%rbp), %rax
	addq	$4, %rax
	movss	(%rax), %xmm0
	mulss	%xmm1, %xmm0
	movaps	%xmm2, %xmm1
	subss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	movq	-32(%rbp), %rax
	movss	%xmm0, (%rax)
	.loc 1 498 0
	movq	-32(%rbp), %rdx
	addq	$4, %rdx
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movss	(%rax), %xmm1
	movq	-16(%rbp), %rax
	movss	(%rax), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movq	-8(%rbp), %rax
	movss	(%rax), %xmm1
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movss	(%rax), %xmm0
	mulss	%xmm1, %xmm0
	movaps	%xmm2, %xmm1
	subss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	movss	%xmm0, (%rdx)
	.loc 1 499 0
	movq	-32(%rbp), %rdx
	addq	$8, %rdx
	movq	-8(%rbp), %rax
	movss	(%rax), %xmm1
	movq	-16(%rbp), %rax
	addq	$4, %rax
	movss	(%rax), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movq	-8(%rbp), %rax
	addq	$4, %rax
	movss	(%rax), %xmm1
	movq	-16(%rbp), %rax
	movss	(%rax), %xmm0
	mulss	%xmm1, %xmm0
	movaps	%xmm2, %xmm1
	subss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	movss	%xmm0, (%rdx)
.L143:
	.loc 1 504 0
	leave
	ret
.LFE36:
	.size	vcrossprod, .-vcrossprod
.globl vsmult
	.type	vsmult, @function
vsmult:
.LFB37:
	.loc 1 506 0
	pushq	%rbp
.LCFI100:
	movq	%rsp, %rbp
.LCFI101:
	subq	$40, %rsp
.LCFI102:
	call	mcount
	movq	%rdi, -24(%rbp)
	movss	%xmm0, -28(%rbp)
	movl	%esi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 1 508 0
	movl	$0, -4(%rbp)
	jmp	.L145
.L146:
	.loc 1 509 0
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdx
	addq	-40(%rbp), %rdx
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-24(%rbp), %rax
	movss	(%rax), %xmm0
	mulss	-28(%rbp), %xmm0
	movss	%xmm0, (%rdx)
	.loc 1 508 0
	addl	$1, -4(%rbp)
.L145:
	movl	-4(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jl	.L146
	.loc 1 514 0
	leave
	ret
.LFE37:
	.size	vsmult, .-vsmult
.globl vmag
	.type	vmag, @function
vmag:
.LFB38:
	.loc 1 516 0
	pushq	%rbp
.LCFI103:
	movq	%rsp, %rbp
.LCFI104:
	subq	$48, %rsp
.LCFI105:
	call	mcount
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	.loc 1 518 0
	movl	$0x00000000, %eax
	movl	%eax, -4(%rbp)
	.loc 1 519 0
	movl	$0, -8(%rbp)
	jmp	.L150
.L151:
	.loc 1 520 0
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-24(%rbp), %rax
	movss	(%rax), %xmm1
	movl	-8(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-24(%rbp), %rax
	movss	(%rax), %xmm0
	mulss	%xmm0, %xmm1
	movss	-4(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 519 0
	addl	$1, -8(%rbp)
.L150:
	movl	-8(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L151
	.loc 1 527 0
	cvtss2sd	-4(%rbp), %xmm0
	call	sqrt
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -36(%rbp)
	movl	-36(%rbp), %eax
	.loc 1 528 0
	movl	%eax, -36(%rbp)
	movss	-36(%rbp), %xmm0
	leave
	ret
.LFE38:
	.size	vmag, .-vmag
.globl zeroCplxVec
	.type	zeroCplxVec, @function
zeroCplxVec:
.LFB39:
	.loc 1 533 0
	pushq	%rbp
.LCFI106:
	movq	%rsp, %rbp
.LCFI107:
	subq	$32, %rsp
.LCFI108:
	call	mcount
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	.loc 1 535 0
	movl	$0, -4(%rbp)
	jmp	.L155
.L156:
	.loc 1 536 0
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	$0x00000000, %eax
	movl	%eax, (%rdx)
	.loc 1 537 0
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	$0x00000000, %eax
	movl	%eax, 4(%rdx)
	.loc 1 535 0
	addl	$1, -4(%rbp)
.L155:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L156
	.loc 1 539 0
	leave
	ret
.LFE39:
	.size	zeroCplxVec, .-zeroCplxVec
.globl zeroRealVec
	.type	zeroRealVec, @function
zeroRealVec:
.LFB40:
	.loc 1 541 0
	pushq	%rbp
.LCFI109:
	movq	%rsp, %rbp
.LCFI110:
	subq	$32, %rsp
.LCFI111:
	call	mcount
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	.loc 1 546 0
	movl	$0, -4(%rbp)
	jmp	.L160
.L161:
	.loc 1 547 0
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdx
	addq	-24(%rbp), %rdx
	movl	$0x00000000, %eax
	movl	%eax, (%rdx)
	.loc 1 546 0
	addl	$1, -4(%rbp)
.L160:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L161
	.loc 1 549 0
	leave
	ret
.LFE40:
	.size	zeroRealVec, .-zeroRealVec
.globl callocCplxArr
	.type	callocCplxArr, @function
callocCplxArr:
.LFB41:
	.loc 1 551 0
	pushq	%rbp
.LCFI112:
	movq	%rsp, %rbp
.LCFI113:
	pushq	%rbx
.LCFI114:
	subq	$24, %rsp
.LCFI115:
	call	mcount
	movl	%edi, -28(%rbp)
	movl	%esi, -32(%rbp)
	.loc 1 554 0
	movl	-28(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdi
	call	malloc
	movq	%rax, -16(%rbp)
	.loc 1 555 0
	movl	$0, -20(%rbp)
	jmp	.L165
.L166:
	.loc 1 556 0
	movl	-20(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rbx
	addq	-16(%rbp), %rbx
	movl	-32(%rbp), %eax
	movslq	%eax,%rdi
	movl	$8, %esi
	call	calloc
	movq	%rax, (%rbx)
	.loc 1 555 0
	addl	$1, -20(%rbp)
.L165:
	movl	-20(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L166
	.loc 1 558 0
	movq	-16(%rbp), %rax
	.loc 1 559 0
	addq	$24, %rsp
	popq	%rbx
	leave
	ret
.LFE41:
	.size	callocCplxArr, .-callocCplxArr
.globl callocRealArr
	.type	callocRealArr, @function
callocRealArr:
.LFB42:
	.loc 1 561 0
	pushq	%rbp
.LCFI116:
	movq	%rsp, %rbp
.LCFI117:
	pushq	%rbx
.LCFI118:
	subq	$24, %rsp
.LCFI119:
	call	mcount
	movl	%edi, -28(%rbp)
	movl	%esi, -32(%rbp)
	.loc 1 564 0
	movl	-28(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdi
	call	malloc
	movq	%rax, -16(%rbp)
	.loc 1 565 0
	movl	$0, -20(%rbp)
	jmp	.L170
.L171:
	.loc 1 566 0
	movl	-20(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rbx
	addq	-16(%rbp), %rbx
	movl	-32(%rbp), %eax
	movslq	%eax,%rdi
	movl	$4, %esi
	call	calloc
	movq	%rax, (%rbx)
	.loc 1 565 0
	addl	$1, -20(%rbp)
.L170:
	movl	-20(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L171
	.loc 1 568 0
	movq	-16(%rbp), %rax
	.loc 1 569 0
	addq	$24, %rsp
	popq	%rbx
	leave
	ret
.LFE42:
	.size	callocRealArr, .-callocRealArr
.globl freeCplxArr
	.type	freeCplxArr, @function
freeCplxArr:
.LFB43:
	.loc 1 571 0
	pushq	%rbp
.LCFI120:
	movq	%rsp, %rbp
.LCFI121:
	subq	$32, %rsp
.LCFI122:
	call	mcount
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	.loc 1 573 0
	movl	$0, -4(%rbp)
	jmp	.L175
.L176:
	.loc 1 574 0
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movq	(%rax), %rdi
	call	free
	.loc 1 573 0
	addl	$1, -4(%rbp)
.L175:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L176
	.loc 1 576 0
	movq	-24(%rbp), %rdi
	call	free
	.loc 1 577 0
	leave
	ret
.LFE43:
	.size	freeCplxArr, .-freeCplxArr
.globl freeRealArr
	.type	freeRealArr, @function
freeRealArr:
.LFB44:
	.loc 1 579 0
	pushq	%rbp
.LCFI123:
	movq	%rsp, %rbp
.LCFI124:
	subq	$32, %rsp
.LCFI125:
	call	mcount
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	.loc 1 581 0
	movl	$0, -4(%rbp)
	jmp	.L180
.L181:
	.loc 1 582 0
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movq	(%rax), %rdi
	call	free
	.loc 1 581 0
	addl	$1, -4(%rbp)
.L180:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L181
	.loc 1 584 0
	movq	-24(%rbp), %rdi
	call	free
	.loc 1 585 0
	leave
	ret
.LFE44:
	.size	freeRealArr, .-freeRealArr
	.section	.rodata
.LC8:
	.string	" %5d %10.5f %10.5f\n"
	.text
.globl printCplxVec
	.type	printCplxVec, @function
printCplxVec:
.LFB45:
	.loc 1 588 0
	pushq	%rbp
.LCFI126:
	movq	%rsp, %rbp
.LCFI127:
	subq	$32, %rsp
.LCFI128:
	call	mcount
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	.loc 1 590 0
	movl	$0, -4(%rbp)
	jmp	.L185
.L186:
	.loc 1 591 0
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movss	4(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm1
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	-24(%rbp), %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movl	-4(%rbp), %esi
	movl	$.LC8, %edi
	movl	$2, %eax
	call	printf
	.loc 1 590 0
	addl	$1, -4(%rbp)
.L185:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L186
	.loc 1 593 0
	movl	$10, %edi
	call	putchar
	.loc 1 594 0
	leave
	ret
.LFE45:
	.size	printCplxVec, .-printCplxVec
	.section	.rodata
.LC9:
	.string	" %5d %10.5f\n"
	.text
.globl printRealVec
	.type	printRealVec, @function
printRealVec:
.LFB46:
	.loc 1 596 0
	pushq	%rbp
.LCFI129:
	movq	%rsp, %rbp
.LCFI130:
	subq	$32, %rsp
.LCFI131:
	call	mcount
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	.loc 1 598 0
	movl	$0, -4(%rbp)
	jmp	.L190
.L191:
	.loc 1 599 0
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-24(%rbp), %rax
	movss	(%rax), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movl	-4(%rbp), %esi
	movl	$.LC9, %edi
	movl	$1, %eax
	call	printf
	.loc 1 598 0
	addl	$1, -4(%rbp)
.L190:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L191
	.loc 1 601 0
	movl	$10, %edi
	call	putchar
	.loc 1 602 0
	leave
	ret
.LFE46:
	.size	printRealVec, .-printRealVec
	.section	.rodata
.LC10:
	.string	"%i"
	.text
.globl printBits
	.type	printBits, @function
printBits:
.LFB47:
	.loc 1 604 0
	pushq	%rbp
.LCFI132:
	movq	%rsp, %rbp
.LCFI133:
	subq	$32, %rsp
.LCFI134:
	call	mcount
	movl	%edi, -20(%rbp)
	.loc 1 606 0
	andl	$255, -20(%rbp)
	.loc 1 607 0
	movl	$1, -4(%rbp)
	jmp	.L195
.L196:
	.loc 1 608 0
	movl	$8, %eax
	movl	%eax, %ecx
	subl	-4(%rbp), %ecx
	movl	$1, %eax
	sall	%cl, %eax
	andl	-20(%rbp), %eax
	movl	%eax, -8(%rbp)
	.loc 1 609 0
	cmpl	$0, -8(%rbp)
	setne	%al
	movzbl	%al, %esi
	movl	$.LC10, %edi
	movl	$0, %eax
	call	printf
	.loc 1 607 0
	addl	$1, -4(%rbp)
.L195:
	cmpl	$8, -4(%rbp)
	jle	.L196
	.loc 1 611 0
	movl	$10, %edi
	call	putchar
	.loc 1 612 0
	leave
	ret
.LFE47:
	.size	printBits, .-printBits
.globl vmag2d
	.type	vmag2d, @function
vmag2d:
.LFB48:
	.loc 1 616 0
	pushq	%rbp
.LCFI135:
	movq	%rsp, %rbp
.LCFI136:
	subq	$32, %rsp
.LCFI137:
	call	mcount
	movq	%xmm0, -24(%rbp)
	.loc 1 618 0
	movss	-24(%rbp), %xmm1
	movss	-24(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movss	-20(%rbp), %xmm1
	movss	-20(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	addss	%xmm2, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 625 0
	cvtss2sd	-4(%rbp), %xmm0
	call	sqrt
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -28(%rbp)
	movl	-28(%rbp), %eax
	.loc 1 627 0
	movl	%eax, -28(%rbp)
	movss	-28(%rbp), %xmm0
	leave
	ret
.LFE48:
	.size	vmag2d, .-vmag2d
.globl varg2d
	.type	varg2d, @function
varg2d:
.LFB49:
	.loc 1 630 0
	pushq	%rbp
.LCFI138:
	movq	%rsp, %rbp
.LCFI139:
	subq	$32, %rsp
.LCFI140:
	call	mcount
	movq	%xmm0, -24(%rbp)
	.loc 1 632 0
	movss	-24(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm1
	movss	-20(%rbp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	call	atan2
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 636 0
	movl	-4(%rbp), %eax
	.loc 1 637 0
	movl	%eax, -28(%rbp)
	movss	-28(%rbp), %xmm0
	leave
	ret
.LFE49:
	.size	varg2d, .-varg2d
.globl vmult2d
	.type	vmult2d, @function
vmult2d:
.LFB50:
	.loc 1 639 0
	pushq	%rbp
.LCFI141:
	movq	%rsp, %rbp
.LCFI142:
	subq	$40, %rsp
.LCFI143:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 641 0
	movss	-24(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movss	-20(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	addss	%xmm2, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 646 0
	movl	-4(%rbp), %eax
	.loc 1 647 0
	movl	%eax, -36(%rbp)
	movss	-36(%rbp), %xmm0
	leave
	ret
.LFE50:
	.size	vmult2d, .-vmult2d
.globl vsmult2d
	.type	vsmult2d, @function
vsmult2d:
.LFB51:
	.loc 1 650 0
	pushq	%rbp
.LCFI144:
	movq	%rsp, %rbp
.LCFI145:
	subq	$32, %rsp
.LCFI146:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movss	%xmm1, -28(%rbp)
	.loc 1 652 0
	movss	-24(%rbp), %xmm0
	mulss	-28(%rbp), %xmm0
	movss	%xmm0, -16(%rbp)
	.loc 1 653 0
	movss	-20(%rbp), %xmm0
	mulss	-28(%rbp), %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 657 0
	movq	-16(%rbp), %rax
	.loc 1 658 0
	movd	%rax, %xmm0
	leave
	ret
.LFE51:
	.size	vsmult2d, .-vsmult2d
.globl vadd2d
	.type	vadd2d, @function
vadd2d:
.LFB52:
	.loc 1 661 0
	pushq	%rbp
.LCFI147:
	movq	%rsp, %rbp
.LCFI148:
	subq	$32, %rsp
.LCFI149:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 663 0
	movss	-24(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -16(%rbp)
	.loc 1 664 0
	movss	-20(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 668 0
	movq	-16(%rbp), %rax
	.loc 1 669 0
	movd	%rax, %xmm0
	leave
	ret
.LFE52:
	.size	vadd2d, .-vadd2d
.globl vsub2d
	.type	vsub2d, @function
vsub2d:
.LFB53:
	.loc 1 671 0
	pushq	%rbp
.LCFI150:
	movq	%rsp, %rbp
.LCFI151:
	subq	$32, %rsp
.LCFI152:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 673 0
	movss	-24(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	subss	%xmm0, %xmm2
	movaps	%xmm2, %xmm0
	movss	%xmm0, -16(%rbp)
	.loc 1 674 0
	movss	-20(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	subss	%xmm0, %xmm2
	movaps	%xmm2, %xmm0
	movss	%xmm0, -12(%rbp)
	.loc 1 678 0
	movq	-16(%rbp), %rax
	.loc 1 679 0
	movd	%rax, %xmm0
	leave
	ret
.LFE53:
	.size	vsub2d, .-vsub2d
.globl vcos2d
	.type	vcos2d, @function
vcos2d:
.LFB54:
	.loc 1 681 0
	pushq	%rbp
.LCFI153:
	movq	%rsp, %rbp
.LCFI154:
	subq	$48, %rsp
.LCFI155:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 683 0
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movd	%rax, %xmm1
	movd	%rdx, %xmm0
	call	vmult2d
	movss	%xmm0, -40(%rbp)
	movq	-24(%rbp), %rax
	movd	%rax, %xmm0
	call	vmag2d
	movss	%xmm0, -36(%rbp)
	movq	-32(%rbp), %rax
	movd	%rax, %xmm0
	call	vmag2d
	mulss	-36(%rbp), %xmm0
	movss	-40(%rbp), %xmm1
	divss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 687 0
	movl	-4(%rbp), %eax
	.loc 1 688 0
	movl	%eax, -44(%rbp)
	movss	-44(%rbp), %xmm0
	leave
	ret
.LFE54:
	.size	vcos2d, .-vcos2d
.globl vsin2d
	.type	vsin2d, @function
vsin2d:
.LFB55:
	.loc 1 691 0
	pushq	%rbp
.LCFI156:
	movq	%rsp, %rbp
.LCFI157:
	subq	$48, %rsp
.LCFI158:
	call	mcount
	movq	%xmm0, -24(%rbp)
	movq	%xmm1, -32(%rbp)
	.loc 1 693 0
	movss	-24(%rbp), %xmm1
	movss	-28(%rbp), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movss	-20(%rbp), %xmm1
	movss	-32(%rbp), %xmm0
	mulss	%xmm1, %xmm0
	movaps	%xmm2, %xmm1
	subss	%xmm0, %xmm1
	movss	%xmm1, -40(%rbp)
	movq	-24(%rbp), %rax
	movd	%rax, %xmm0
	call	vmag2d
	movss	%xmm0, -36(%rbp)
	movq	-32(%rbp), %rax
	movd	%rax, %xmm0
	call	vmag2d
	mulss	-36(%rbp), %xmm0
	movss	-40(%rbp), %xmm1
	divss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	.loc 1 698 0
	movl	-4(%rbp), %eax
	.loc 1 699 0
	movl	%eax, -44(%rbp)
	movss	-44(%rbp), %xmm0
	leave
	ret
.LFE55:
	.size	vsin2d, .-vsin2d
	.section	.debug_frame,"",@progbits
.Lframe0:
	.long	.LECIE0-.LSCIE0
.LSCIE0:
	.long	0xffffffff
	.byte	0x1
	.string	""
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE0:
.LSFDE0:
	.long	.LEFDE0-.LASFDE0
.LASFDE0:
	.long	.Lframe0
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.byte	0x4
	.long	.LCFI0-.LFB5
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE0:
.LSFDE2:
	.long	.LEFDE2-.LASFDE2
.LASFDE2:
	.long	.Lframe0
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.byte	0x4
	.long	.LCFI3-.LFB6
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE2:
.LSFDE4:
	.long	.LEFDE4-.LASFDE4
.LASFDE4:
	.long	.Lframe0
	.quad	.LFB7
	.quad	.LFE7-.LFB7
	.byte	0x4
	.long	.LCFI6-.LFB7
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE4:
.LSFDE6:
	.long	.LEFDE6-.LASFDE6
.LASFDE6:
	.long	.Lframe0
	.quad	.LFB8
	.quad	.LFE8-.LFB8
	.byte	0x4
	.long	.LCFI9-.LFB8
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE6:
.LSFDE8:
	.long	.LEFDE8-.LASFDE8
.LASFDE8:
	.long	.Lframe0
	.quad	.LFB9
	.quad	.LFE9-.LFB9
	.byte	0x4
	.long	.LCFI12-.LFB9
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI13-.LCFI12
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE8:
.LSFDE10:
	.long	.LEFDE10-.LASFDE10
.LASFDE10:
	.long	.Lframe0
	.quad	.LFB10
	.quad	.LFE10-.LFB10
	.byte	0x4
	.long	.LCFI15-.LFB10
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI16-.LCFI15
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE10:
.LSFDE12:
	.long	.LEFDE12-.LASFDE12
.LASFDE12:
	.long	.Lframe0
	.quad	.LFB11
	.quad	.LFE11-.LFB11
	.byte	0x4
	.long	.LCFI18-.LFB11
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI19-.LCFI18
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE12:
.LSFDE14:
	.long	.LEFDE14-.LASFDE14
.LASFDE14:
	.long	.Lframe0
	.quad	.LFB12
	.quad	.LFE12-.LFB12
	.byte	0x4
	.long	.LCFI21-.LFB12
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI22-.LCFI21
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE14:
.LSFDE16:
	.long	.LEFDE16-.LASFDE16
.LASFDE16:
	.long	.Lframe0
	.quad	.LFB13
	.quad	.LFE13-.LFB13
	.byte	0x4
	.long	.LCFI24-.LFB13
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI25-.LCFI24
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE16:
.LSFDE18:
	.long	.LEFDE18-.LASFDE18
.LASFDE18:
	.long	.Lframe0
	.quad	.LFB14
	.quad	.LFE14-.LFB14
	.byte	0x4
	.long	.LCFI27-.LFB14
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI28-.LCFI27
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE18:
.LSFDE20:
	.long	.LEFDE20-.LASFDE20
.LASFDE20:
	.long	.Lframe0
	.quad	.LFB15
	.quad	.LFE15-.LFB15
	.byte	0x4
	.long	.LCFI30-.LFB15
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI31-.LCFI30
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE20:
.LSFDE22:
	.long	.LEFDE22-.LASFDE22
.LASFDE22:
	.long	.Lframe0
	.quad	.LFB16
	.quad	.LFE16-.LFB16
	.byte	0x4
	.long	.LCFI33-.LFB16
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI34-.LCFI33
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI36-.LCFI34
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE22:
.LSFDE24:
	.long	.LEFDE24-.LASFDE24
.LASFDE24:
	.long	.Lframe0
	.quad	.LFB17
	.quad	.LFE17-.LFB17
	.byte	0x4
	.long	.LCFI37-.LFB17
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI38-.LCFI37
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI40-.LCFI38
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE24:
.LSFDE26:
	.long	.LEFDE26-.LASFDE26
.LASFDE26:
	.long	.Lframe0
	.quad	.LFB18
	.quad	.LFE18-.LFB18
	.byte	0x4
	.long	.LCFI41-.LFB18
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI42-.LCFI41
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE26:
.LSFDE28:
	.long	.LEFDE28-.LASFDE28
.LASFDE28:
	.long	.Lframe0
	.quad	.LFB19
	.quad	.LFE19-.LFB19
	.byte	0x4
	.long	.LCFI44-.LFB19
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI45-.LCFI44
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE28:
.LSFDE30:
	.long	.LEFDE30-.LASFDE30
.LASFDE30:
	.long	.Lframe0
	.quad	.LFB20
	.quad	.LFE20-.LFB20
	.byte	0x4
	.long	.LCFI47-.LFB20
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI48-.LCFI47
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE30:
.LSFDE32:
	.long	.LEFDE32-.LASFDE32
.LASFDE32:
	.long	.Lframe0
	.quad	.LFB21
	.quad	.LFE21-.LFB21
	.byte	0x4
	.long	.LCFI50-.LFB21
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI51-.LCFI50
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE32:
.LSFDE34:
	.long	.LEFDE34-.LASFDE34
.LASFDE34:
	.long	.Lframe0
	.quad	.LFB22
	.quad	.LFE22-.LFB22
	.byte	0x4
	.long	.LCFI53-.LFB22
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI54-.LCFI53
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE34:
.LSFDE36:
	.long	.LEFDE36-.LASFDE36
.LASFDE36:
	.long	.Lframe0
	.quad	.LFB23
	.quad	.LFE23-.LFB23
	.byte	0x4
	.long	.LCFI56-.LFB23
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI57-.LCFI56
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE36:
.LSFDE38:
	.long	.LEFDE38-.LASFDE38
.LASFDE38:
	.long	.Lframe0
	.quad	.LFB24
	.quad	.LFE24-.LFB24
	.byte	0x4
	.long	.LCFI59-.LFB24
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI60-.LCFI59
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE38:
.LSFDE40:
	.long	.LEFDE40-.LASFDE40
.LASFDE40:
	.long	.Lframe0
	.quad	.LFB25
	.quad	.LFE25-.LFB25
	.byte	0x4
	.long	.LCFI62-.LFB25
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI63-.LCFI62
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE40:
.LSFDE42:
	.long	.LEFDE42-.LASFDE42
.LASFDE42:
	.long	.Lframe0
	.quad	.LFB26
	.quad	.LFE26-.LFB26
	.byte	0x4
	.long	.LCFI65-.LFB26
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI66-.LCFI65
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE42:
.LSFDE44:
	.long	.LEFDE44-.LASFDE44
.LASFDE44:
	.long	.Lframe0
	.quad	.LFB27
	.quad	.LFE27-.LFB27
	.byte	0x4
	.long	.LCFI68-.LFB27
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI69-.LCFI68
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE44:
.LSFDE46:
	.long	.LEFDE46-.LASFDE46
.LASFDE46:
	.long	.Lframe0
	.quad	.LFB28
	.quad	.LFE28-.LFB28
	.byte	0x4
	.long	.LCFI71-.LFB28
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI72-.LCFI71
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE46:
.LSFDE48:
	.long	.LEFDE48-.LASFDE48
.LASFDE48:
	.long	.Lframe0
	.quad	.LFB29
	.quad	.LFE29-.LFB29
	.byte	0x4
	.long	.LCFI74-.LFB29
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI75-.LCFI74
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE48:
.LSFDE50:
	.long	.LEFDE50-.LASFDE50
.LASFDE50:
	.long	.Lframe0
	.quad	.LFB30
	.quad	.LFE30-.LFB30
	.byte	0x4
	.long	.LCFI77-.LFB30
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI78-.LCFI77
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI80-.LCFI78
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE50:
.LSFDE52:
	.long	.LEFDE52-.LASFDE52
.LASFDE52:
	.long	.Lframe0
	.quad	.LFB31
	.quad	.LFE31-.LFB31
	.byte	0x4
	.long	.LCFI81-.LFB31
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI82-.LCFI81
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE52:
.LSFDE54:
	.long	.LEFDE54-.LASFDE54
.LASFDE54:
	.long	.Lframe0
	.quad	.LFB32
	.quad	.LFE32-.LFB32
	.byte	0x4
	.long	.LCFI84-.LFB32
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI85-.LCFI84
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI87-.LCFI85
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE54:
.LSFDE56:
	.long	.LEFDE56-.LASFDE56
.LASFDE56:
	.long	.Lframe0
	.quad	.LFB33
	.quad	.LFE33-.LFB33
	.byte	0x4
	.long	.LCFI88-.LFB33
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI89-.LCFI88
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE56:
.LSFDE58:
	.long	.LEFDE58-.LASFDE58
.LASFDE58:
	.long	.Lframe0
	.quad	.LFB34
	.quad	.LFE34-.LFB34
	.byte	0x4
	.long	.LCFI91-.LFB34
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI92-.LCFI91
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE58:
.LSFDE60:
	.long	.LEFDE60-.LASFDE60
.LASFDE60:
	.long	.Lframe0
	.quad	.LFB35
	.quad	.LFE35-.LFB35
	.byte	0x4
	.long	.LCFI94-.LFB35
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI95-.LCFI94
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE60:
.LSFDE62:
	.long	.LEFDE62-.LASFDE62
.LASFDE62:
	.long	.Lframe0
	.quad	.LFB36
	.quad	.LFE36-.LFB36
	.byte	0x4
	.long	.LCFI97-.LFB36
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI98-.LCFI97
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE62:
.LSFDE64:
	.long	.LEFDE64-.LASFDE64
.LASFDE64:
	.long	.Lframe0
	.quad	.LFB37
	.quad	.LFE37-.LFB37
	.byte	0x4
	.long	.LCFI100-.LFB37
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI101-.LCFI100
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE64:
.LSFDE66:
	.long	.LEFDE66-.LASFDE66
.LASFDE66:
	.long	.Lframe0
	.quad	.LFB38
	.quad	.LFE38-.LFB38
	.byte	0x4
	.long	.LCFI103-.LFB38
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI104-.LCFI103
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE66:
.LSFDE68:
	.long	.LEFDE68-.LASFDE68
.LASFDE68:
	.long	.Lframe0
	.quad	.LFB39
	.quad	.LFE39-.LFB39
	.byte	0x4
	.long	.LCFI106-.LFB39
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI107-.LCFI106
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE68:
.LSFDE70:
	.long	.LEFDE70-.LASFDE70
.LASFDE70:
	.long	.Lframe0
	.quad	.LFB40
	.quad	.LFE40-.LFB40
	.byte	0x4
	.long	.LCFI109-.LFB40
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI110-.LCFI109
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE70:
.LSFDE72:
	.long	.LEFDE72-.LASFDE72
.LASFDE72:
	.long	.Lframe0
	.quad	.LFB41
	.quad	.LFE41-.LFB41
	.byte	0x4
	.long	.LCFI112-.LFB41
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI113-.LCFI112
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI115-.LCFI113
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE72:
.LSFDE74:
	.long	.LEFDE74-.LASFDE74
.LASFDE74:
	.long	.Lframe0
	.quad	.LFB42
	.quad	.LFE42-.LFB42
	.byte	0x4
	.long	.LCFI116-.LFB42
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI117-.LCFI116
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI119-.LCFI117
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE74:
.LSFDE76:
	.long	.LEFDE76-.LASFDE76
.LASFDE76:
	.long	.Lframe0
	.quad	.LFB43
	.quad	.LFE43-.LFB43
	.byte	0x4
	.long	.LCFI120-.LFB43
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI121-.LCFI120
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE76:
.LSFDE78:
	.long	.LEFDE78-.LASFDE78
.LASFDE78:
	.long	.Lframe0
	.quad	.LFB44
	.quad	.LFE44-.LFB44
	.byte	0x4
	.long	.LCFI123-.LFB44
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI124-.LCFI123
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE78:
.LSFDE80:
	.long	.LEFDE80-.LASFDE80
.LASFDE80:
	.long	.Lframe0
	.quad	.LFB45
	.quad	.LFE45-.LFB45
	.byte	0x4
	.long	.LCFI126-.LFB45
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI127-.LCFI126
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE80:
.LSFDE82:
	.long	.LEFDE82-.LASFDE82
.LASFDE82:
	.long	.Lframe0
	.quad	.LFB46
	.quad	.LFE46-.LFB46
	.byte	0x4
	.long	.LCFI129-.LFB46
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI130-.LCFI129
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE82:
.LSFDE84:
	.long	.LEFDE84-.LASFDE84
.LASFDE84:
	.long	.Lframe0
	.quad	.LFB47
	.quad	.LFE47-.LFB47
	.byte	0x4
	.long	.LCFI132-.LFB47
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI133-.LCFI132
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE84:
.LSFDE86:
	.long	.LEFDE86-.LASFDE86
.LASFDE86:
	.long	.Lframe0
	.quad	.LFB48
	.quad	.LFE48-.LFB48
	.byte	0x4
	.long	.LCFI135-.LFB48
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI136-.LCFI135
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE86:
.LSFDE88:
	.long	.LEFDE88-.LASFDE88
.LASFDE88:
	.long	.Lframe0
	.quad	.LFB49
	.quad	.LFE49-.LFB49
	.byte	0x4
	.long	.LCFI138-.LFB49
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI139-.LCFI138
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE88:
.LSFDE90:
	.long	.LEFDE90-.LASFDE90
.LASFDE90:
	.long	.Lframe0
	.quad	.LFB50
	.quad	.LFE50-.LFB50
	.byte	0x4
	.long	.LCFI141-.LFB50
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI142-.LCFI141
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE90:
.LSFDE92:
	.long	.LEFDE92-.LASFDE92
.LASFDE92:
	.long	.Lframe0
	.quad	.LFB51
	.quad	.LFE51-.LFB51
	.byte	0x4
	.long	.LCFI144-.LFB51
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI145-.LCFI144
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE92:
.LSFDE94:
	.long	.LEFDE94-.LASFDE94
.LASFDE94:
	.long	.Lframe0
	.quad	.LFB52
	.quad	.LFE52-.LFB52
	.byte	0x4
	.long	.LCFI147-.LFB52
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI148-.LCFI147
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE94:
.LSFDE96:
	.long	.LEFDE96-.LASFDE96
.LASFDE96:
	.long	.Lframe0
	.quad	.LFB53
	.quad	.LFE53-.LFB53
	.byte	0x4
	.long	.LCFI150-.LFB53
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI151-.LCFI150
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE96:
.LSFDE98:
	.long	.LEFDE98-.LASFDE98
.LASFDE98:
	.long	.Lframe0
	.quad	.LFB54
	.quad	.LFE54-.LFB54
	.byte	0x4
	.long	.LCFI153-.LFB54
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI154-.LCFI153
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE98:
.LSFDE100:
	.long	.LEFDE100-.LASFDE100
.LASFDE100:
	.long	.Lframe0
	.quad	.LFB55
	.quad	.LFE55-.LFB55
	.byte	0x4
	.long	.LCFI156-.LFB55
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI157-.LCFI156
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE100:
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zR"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x1
	.byte	0x3
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB5
	.long	.LFE5-.LFB5
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI0-.LFB5
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB6
	.long	.LFE6-.LFB6
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI3-.LFB6
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB7
	.long	.LFE7-.LFB7
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI6-.LFB7
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB8
	.long	.LFE8-.LFB8
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI9-.LFB8
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB9
	.long	.LFE9-.LFB9
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI12-.LFB9
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI13-.LCFI12
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB10
	.long	.LFE10-.LFB10
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI15-.LFB10
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI16-.LCFI15
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE11:
.LSFDE13:
	.long	.LEFDE13-.LASFDE13
.LASFDE13:
	.long	.LASFDE13-.Lframe1
	.long	.LFB11
	.long	.LFE11-.LFB11
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI18-.LFB11
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI19-.LCFI18
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE13:
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB12
	.long	.LFE12-.LFB12
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI21-.LFB12
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI22-.LCFI21
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE15:
.LSFDE17:
	.long	.LEFDE17-.LASFDE17
.LASFDE17:
	.long	.LASFDE17-.Lframe1
	.long	.LFB13
	.long	.LFE13-.LFB13
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI24-.LFB13
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI25-.LCFI24
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE17:
.LSFDE19:
	.long	.LEFDE19-.LASFDE19
.LASFDE19:
	.long	.LASFDE19-.Lframe1
	.long	.LFB14
	.long	.LFE14-.LFB14
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI27-.LFB14
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI28-.LCFI27
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE19:
.LSFDE21:
	.long	.LEFDE21-.LASFDE21
.LASFDE21:
	.long	.LASFDE21-.Lframe1
	.long	.LFB15
	.long	.LFE15-.LFB15
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI30-.LFB15
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI31-.LCFI30
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE21:
.LSFDE23:
	.long	.LEFDE23-.LASFDE23
.LASFDE23:
	.long	.LASFDE23-.Lframe1
	.long	.LFB16
	.long	.LFE16-.LFB16
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI33-.LFB16
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI34-.LCFI33
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI36-.LCFI34
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE23:
.LSFDE25:
	.long	.LEFDE25-.LASFDE25
.LASFDE25:
	.long	.LASFDE25-.Lframe1
	.long	.LFB17
	.long	.LFE17-.LFB17
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI37-.LFB17
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI38-.LCFI37
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI40-.LCFI38
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE25:
.LSFDE27:
	.long	.LEFDE27-.LASFDE27
.LASFDE27:
	.long	.LASFDE27-.Lframe1
	.long	.LFB18
	.long	.LFE18-.LFB18
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI41-.LFB18
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI42-.LCFI41
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE27:
.LSFDE29:
	.long	.LEFDE29-.LASFDE29
.LASFDE29:
	.long	.LASFDE29-.Lframe1
	.long	.LFB19
	.long	.LFE19-.LFB19
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI44-.LFB19
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI45-.LCFI44
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE29:
.LSFDE31:
	.long	.LEFDE31-.LASFDE31
.LASFDE31:
	.long	.LASFDE31-.Lframe1
	.long	.LFB20
	.long	.LFE20-.LFB20
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI47-.LFB20
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI48-.LCFI47
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE31:
.LSFDE33:
	.long	.LEFDE33-.LASFDE33
.LASFDE33:
	.long	.LASFDE33-.Lframe1
	.long	.LFB21
	.long	.LFE21-.LFB21
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI50-.LFB21
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI51-.LCFI50
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE33:
.LSFDE35:
	.long	.LEFDE35-.LASFDE35
.LASFDE35:
	.long	.LASFDE35-.Lframe1
	.long	.LFB22
	.long	.LFE22-.LFB22
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI53-.LFB22
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI54-.LCFI53
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE35:
.LSFDE37:
	.long	.LEFDE37-.LASFDE37
.LASFDE37:
	.long	.LASFDE37-.Lframe1
	.long	.LFB23
	.long	.LFE23-.LFB23
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI56-.LFB23
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI57-.LCFI56
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE37:
.LSFDE39:
	.long	.LEFDE39-.LASFDE39
.LASFDE39:
	.long	.LASFDE39-.Lframe1
	.long	.LFB24
	.long	.LFE24-.LFB24
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI59-.LFB24
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI60-.LCFI59
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE39:
.LSFDE41:
	.long	.LEFDE41-.LASFDE41
.LASFDE41:
	.long	.LASFDE41-.Lframe1
	.long	.LFB25
	.long	.LFE25-.LFB25
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI62-.LFB25
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI63-.LCFI62
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE41:
.LSFDE43:
	.long	.LEFDE43-.LASFDE43
.LASFDE43:
	.long	.LASFDE43-.Lframe1
	.long	.LFB26
	.long	.LFE26-.LFB26
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI65-.LFB26
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI66-.LCFI65
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE43:
.LSFDE45:
	.long	.LEFDE45-.LASFDE45
.LASFDE45:
	.long	.LASFDE45-.Lframe1
	.long	.LFB27
	.long	.LFE27-.LFB27
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI68-.LFB27
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI69-.LCFI68
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE45:
.LSFDE47:
	.long	.LEFDE47-.LASFDE47
.LASFDE47:
	.long	.LASFDE47-.Lframe1
	.long	.LFB28
	.long	.LFE28-.LFB28
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI71-.LFB28
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI72-.LCFI71
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE47:
.LSFDE49:
	.long	.LEFDE49-.LASFDE49
.LASFDE49:
	.long	.LASFDE49-.Lframe1
	.long	.LFB29
	.long	.LFE29-.LFB29
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI74-.LFB29
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI75-.LCFI74
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE49:
.LSFDE51:
	.long	.LEFDE51-.LASFDE51
.LASFDE51:
	.long	.LASFDE51-.Lframe1
	.long	.LFB30
	.long	.LFE30-.LFB30
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI77-.LFB30
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI78-.LCFI77
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI80-.LCFI78
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE51:
.LSFDE53:
	.long	.LEFDE53-.LASFDE53
.LASFDE53:
	.long	.LASFDE53-.Lframe1
	.long	.LFB31
	.long	.LFE31-.LFB31
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI81-.LFB31
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI82-.LCFI81
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE53:
.LSFDE55:
	.long	.LEFDE55-.LASFDE55
.LASFDE55:
	.long	.LASFDE55-.Lframe1
	.long	.LFB32
	.long	.LFE32-.LFB32
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI84-.LFB32
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI85-.LCFI84
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI87-.LCFI85
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE55:
.LSFDE57:
	.long	.LEFDE57-.LASFDE57
.LASFDE57:
	.long	.LASFDE57-.Lframe1
	.long	.LFB33
	.long	.LFE33-.LFB33
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI88-.LFB33
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI89-.LCFI88
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE57:
.LSFDE59:
	.long	.LEFDE59-.LASFDE59
.LASFDE59:
	.long	.LASFDE59-.Lframe1
	.long	.LFB34
	.long	.LFE34-.LFB34
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI91-.LFB34
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI92-.LCFI91
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE59:
.LSFDE61:
	.long	.LEFDE61-.LASFDE61
.LASFDE61:
	.long	.LASFDE61-.Lframe1
	.long	.LFB35
	.long	.LFE35-.LFB35
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI94-.LFB35
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI95-.LCFI94
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE61:
.LSFDE63:
	.long	.LEFDE63-.LASFDE63
.LASFDE63:
	.long	.LASFDE63-.Lframe1
	.long	.LFB36
	.long	.LFE36-.LFB36
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI97-.LFB36
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI98-.LCFI97
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE63:
.LSFDE65:
	.long	.LEFDE65-.LASFDE65
.LASFDE65:
	.long	.LASFDE65-.Lframe1
	.long	.LFB37
	.long	.LFE37-.LFB37
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI100-.LFB37
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI101-.LCFI100
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE65:
.LSFDE67:
	.long	.LEFDE67-.LASFDE67
.LASFDE67:
	.long	.LASFDE67-.Lframe1
	.long	.LFB38
	.long	.LFE38-.LFB38
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI103-.LFB38
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI104-.LCFI103
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE67:
.LSFDE69:
	.long	.LEFDE69-.LASFDE69
.LASFDE69:
	.long	.LASFDE69-.Lframe1
	.long	.LFB39
	.long	.LFE39-.LFB39
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI106-.LFB39
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI107-.LCFI106
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE69:
.LSFDE71:
	.long	.LEFDE71-.LASFDE71
.LASFDE71:
	.long	.LASFDE71-.Lframe1
	.long	.LFB40
	.long	.LFE40-.LFB40
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI109-.LFB40
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI110-.LCFI109
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE71:
.LSFDE73:
	.long	.LEFDE73-.LASFDE73
.LASFDE73:
	.long	.LASFDE73-.Lframe1
	.long	.LFB41
	.long	.LFE41-.LFB41
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI112-.LFB41
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI113-.LCFI112
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI115-.LCFI113
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE73:
.LSFDE75:
	.long	.LEFDE75-.LASFDE75
.LASFDE75:
	.long	.LASFDE75-.Lframe1
	.long	.LFB42
	.long	.LFE42-.LFB42
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI116-.LFB42
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI117-.LCFI116
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI119-.LCFI117
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE75:
.LSFDE77:
	.long	.LEFDE77-.LASFDE77
.LASFDE77:
	.long	.LASFDE77-.Lframe1
	.long	.LFB43
	.long	.LFE43-.LFB43
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI120-.LFB43
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI121-.LCFI120
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE77:
.LSFDE79:
	.long	.LEFDE79-.LASFDE79
.LASFDE79:
	.long	.LASFDE79-.Lframe1
	.long	.LFB44
	.long	.LFE44-.LFB44
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI123-.LFB44
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI124-.LCFI123
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE79:
.LSFDE81:
	.long	.LEFDE81-.LASFDE81
.LASFDE81:
	.long	.LASFDE81-.Lframe1
	.long	.LFB45
	.long	.LFE45-.LFB45
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI126-.LFB45
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI127-.LCFI126
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE81:
.LSFDE83:
	.long	.LEFDE83-.LASFDE83
.LASFDE83:
	.long	.LASFDE83-.Lframe1
	.long	.LFB46
	.long	.LFE46-.LFB46
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI129-.LFB46
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI130-.LCFI129
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE83:
.LSFDE85:
	.long	.LEFDE85-.LASFDE85
.LASFDE85:
	.long	.LASFDE85-.Lframe1
	.long	.LFB47
	.long	.LFE47-.LFB47
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI132-.LFB47
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI133-.LCFI132
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE85:
.LSFDE87:
	.long	.LEFDE87-.LASFDE87
.LASFDE87:
	.long	.LASFDE87-.Lframe1
	.long	.LFB48
	.long	.LFE48-.LFB48
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI135-.LFB48
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI136-.LCFI135
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE87:
.LSFDE89:
	.long	.LEFDE89-.LASFDE89
.LASFDE89:
	.long	.LASFDE89-.Lframe1
	.long	.LFB49
	.long	.LFE49-.LFB49
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI138-.LFB49
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI139-.LCFI138
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE89:
.LSFDE91:
	.long	.LEFDE91-.LASFDE91
.LASFDE91:
	.long	.LASFDE91-.Lframe1
	.long	.LFB50
	.long	.LFE50-.LFB50
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI141-.LFB50
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI142-.LCFI141
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE91:
.LSFDE93:
	.long	.LEFDE93-.LASFDE93
.LASFDE93:
	.long	.LASFDE93-.Lframe1
	.long	.LFB51
	.long	.LFE51-.LFB51
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI144-.LFB51
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI145-.LCFI144
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE93:
.LSFDE95:
	.long	.LEFDE95-.LASFDE95
.LASFDE95:
	.long	.LASFDE95-.Lframe1
	.long	.LFB52
	.long	.LFE52-.LFB52
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI147-.LFB52
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI148-.LCFI147
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE95:
.LSFDE97:
	.long	.LEFDE97-.LASFDE97
.LASFDE97:
	.long	.LASFDE97-.Lframe1
	.long	.LFB53
	.long	.LFE53-.LFB53
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI150-.LFB53
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI151-.LCFI150
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE97:
.LSFDE99:
	.long	.LEFDE99-.LASFDE99
.LASFDE99:
	.long	.LASFDE99-.Lframe1
	.long	.LFB54
	.long	.LFE54-.LFB54
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI153-.LFB54
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI154-.LCFI153
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE99:
.LSFDE101:
	.long	.LEFDE101-.LASFDE101
.LASFDE101:
	.long	.LASFDE101-.Lframe1
	.long	.LFB55
	.long	.LFE55-.LFB55
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI156-.LFB55
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI157-.LCFI156
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE101:
	.file 2 "mymath.h"
	.text
.Letext0:
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.quad	.LFB5-.Ltext0
	.quad	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI0-.Ltext0
	.quad	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI1-.Ltext0
	.quad	.LFE5-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST1:
	.quad	.LFB6-.Ltext0
	.quad	.LCFI3-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI3-.Ltext0
	.quad	.LCFI4-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI4-.Ltext0
	.quad	.LFE6-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST2:
	.quad	.LFB7-.Ltext0
	.quad	.LCFI6-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI6-.Ltext0
	.quad	.LCFI7-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI7-.Ltext0
	.quad	.LFE7-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST3:
	.quad	.LFB8-.Ltext0
	.quad	.LCFI9-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI9-.Ltext0
	.quad	.LCFI10-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI10-.Ltext0
	.quad	.LFE8-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST4:
	.quad	.LFB9-.Ltext0
	.quad	.LCFI12-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI12-.Ltext0
	.quad	.LCFI13-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI13-.Ltext0
	.quad	.LFE9-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST5:
	.quad	.LFB10-.Ltext0
	.quad	.LCFI15-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI15-.Ltext0
	.quad	.LCFI16-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI16-.Ltext0
	.quad	.LFE10-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST6:
	.quad	.LFB11-.Ltext0
	.quad	.LCFI18-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI18-.Ltext0
	.quad	.LCFI19-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI19-.Ltext0
	.quad	.LFE11-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST7:
	.quad	.LFB12-.Ltext0
	.quad	.LCFI21-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI21-.Ltext0
	.quad	.LCFI22-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI22-.Ltext0
	.quad	.LFE12-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST8:
	.quad	.LFB13-.Ltext0
	.quad	.LCFI24-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI24-.Ltext0
	.quad	.LCFI25-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI25-.Ltext0
	.quad	.LFE13-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST9:
	.quad	.LFB14-.Ltext0
	.quad	.LCFI27-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI27-.Ltext0
	.quad	.LCFI28-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI28-.Ltext0
	.quad	.LFE14-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST10:
	.quad	.LFB15-.Ltext0
	.quad	.LCFI30-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI30-.Ltext0
	.quad	.LCFI31-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI31-.Ltext0
	.quad	.LFE15-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST11:
	.quad	.LFB16-.Ltext0
	.quad	.LCFI33-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI33-.Ltext0
	.quad	.LCFI34-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI34-.Ltext0
	.quad	.LFE16-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST12:
	.quad	.LFB17-.Ltext0
	.quad	.LCFI37-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI37-.Ltext0
	.quad	.LCFI38-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI38-.Ltext0
	.quad	.LFE17-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST13:
	.quad	.LFB18-.Ltext0
	.quad	.LCFI41-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI41-.Ltext0
	.quad	.LCFI42-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI42-.Ltext0
	.quad	.LFE18-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST14:
	.quad	.LFB19-.Ltext0
	.quad	.LCFI44-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI44-.Ltext0
	.quad	.LCFI45-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI45-.Ltext0
	.quad	.LFE19-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST15:
	.quad	.LFB20-.Ltext0
	.quad	.LCFI47-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI47-.Ltext0
	.quad	.LCFI48-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI48-.Ltext0
	.quad	.LFE20-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST16:
	.quad	.LFB21-.Ltext0
	.quad	.LCFI50-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI50-.Ltext0
	.quad	.LCFI51-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI51-.Ltext0
	.quad	.LFE21-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST17:
	.quad	.LFB22-.Ltext0
	.quad	.LCFI53-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI53-.Ltext0
	.quad	.LCFI54-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI54-.Ltext0
	.quad	.LFE22-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST18:
	.quad	.LFB23-.Ltext0
	.quad	.LCFI56-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI56-.Ltext0
	.quad	.LCFI57-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI57-.Ltext0
	.quad	.LFE23-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST19:
	.quad	.LFB24-.Ltext0
	.quad	.LCFI59-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI59-.Ltext0
	.quad	.LCFI60-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI60-.Ltext0
	.quad	.LFE24-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST20:
	.quad	.LFB25-.Ltext0
	.quad	.LCFI62-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI62-.Ltext0
	.quad	.LCFI63-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI63-.Ltext0
	.quad	.LFE25-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST21:
	.quad	.LFB26-.Ltext0
	.quad	.LCFI65-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI65-.Ltext0
	.quad	.LCFI66-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI66-.Ltext0
	.quad	.LFE26-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST22:
	.quad	.LFB27-.Ltext0
	.quad	.LCFI68-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI68-.Ltext0
	.quad	.LCFI69-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI69-.Ltext0
	.quad	.LFE27-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST23:
	.quad	.LFB28-.Ltext0
	.quad	.LCFI71-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI71-.Ltext0
	.quad	.LCFI72-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI72-.Ltext0
	.quad	.LFE28-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST24:
	.quad	.LFB29-.Ltext0
	.quad	.LCFI74-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI74-.Ltext0
	.quad	.LCFI75-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI75-.Ltext0
	.quad	.LFE29-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST25:
	.quad	.LFB30-.Ltext0
	.quad	.LCFI77-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI77-.Ltext0
	.quad	.LCFI78-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI78-.Ltext0
	.quad	.LFE30-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST26:
	.quad	.LFB31-.Ltext0
	.quad	.LCFI81-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI81-.Ltext0
	.quad	.LCFI82-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI82-.Ltext0
	.quad	.LFE31-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST27:
	.quad	.LFB32-.Ltext0
	.quad	.LCFI84-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI84-.Ltext0
	.quad	.LCFI85-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI85-.Ltext0
	.quad	.LFE32-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST28:
	.quad	.LFB33-.Ltext0
	.quad	.LCFI88-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI88-.Ltext0
	.quad	.LCFI89-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI89-.Ltext0
	.quad	.LFE33-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST29:
	.quad	.LFB34-.Ltext0
	.quad	.LCFI91-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI91-.Ltext0
	.quad	.LCFI92-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI92-.Ltext0
	.quad	.LFE34-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST30:
	.quad	.LFB35-.Ltext0
	.quad	.LCFI94-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI94-.Ltext0
	.quad	.LCFI95-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI95-.Ltext0
	.quad	.LFE35-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST31:
	.quad	.LFB36-.Ltext0
	.quad	.LCFI97-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI97-.Ltext0
	.quad	.LCFI98-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI98-.Ltext0
	.quad	.LFE36-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST32:
	.quad	.LFB37-.Ltext0
	.quad	.LCFI100-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI100-.Ltext0
	.quad	.LCFI101-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI101-.Ltext0
	.quad	.LFE37-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST33:
	.quad	.LFB38-.Ltext0
	.quad	.LCFI103-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI103-.Ltext0
	.quad	.LCFI104-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI104-.Ltext0
	.quad	.LFE38-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST34:
	.quad	.LFB39-.Ltext0
	.quad	.LCFI106-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI106-.Ltext0
	.quad	.LCFI107-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI107-.Ltext0
	.quad	.LFE39-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST35:
	.quad	.LFB40-.Ltext0
	.quad	.LCFI109-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI109-.Ltext0
	.quad	.LCFI110-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI110-.Ltext0
	.quad	.LFE40-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST36:
	.quad	.LFB41-.Ltext0
	.quad	.LCFI112-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI112-.Ltext0
	.quad	.LCFI113-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI113-.Ltext0
	.quad	.LFE41-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST37:
	.quad	.LFB42-.Ltext0
	.quad	.LCFI116-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI116-.Ltext0
	.quad	.LCFI117-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI117-.Ltext0
	.quad	.LFE42-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST38:
	.quad	.LFB43-.Ltext0
	.quad	.LCFI120-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI120-.Ltext0
	.quad	.LCFI121-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI121-.Ltext0
	.quad	.LFE43-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST39:
	.quad	.LFB44-.Ltext0
	.quad	.LCFI123-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI123-.Ltext0
	.quad	.LCFI124-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI124-.Ltext0
	.quad	.LFE44-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST40:
	.quad	.LFB45-.Ltext0
	.quad	.LCFI126-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI126-.Ltext0
	.quad	.LCFI127-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI127-.Ltext0
	.quad	.LFE45-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST41:
	.quad	.LFB46-.Ltext0
	.quad	.LCFI129-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI129-.Ltext0
	.quad	.LCFI130-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI130-.Ltext0
	.quad	.LFE46-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST42:
	.quad	.LFB47-.Ltext0
	.quad	.LCFI132-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI132-.Ltext0
	.quad	.LCFI133-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI133-.Ltext0
	.quad	.LFE47-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST43:
	.quad	.LFB48-.Ltext0
	.quad	.LCFI135-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI135-.Ltext0
	.quad	.LCFI136-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI136-.Ltext0
	.quad	.LFE48-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST44:
	.quad	.LFB49-.Ltext0
	.quad	.LCFI138-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI138-.Ltext0
	.quad	.LCFI139-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI139-.Ltext0
	.quad	.LFE49-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST45:
	.quad	.LFB50-.Ltext0
	.quad	.LCFI141-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI141-.Ltext0
	.quad	.LCFI142-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI142-.Ltext0
	.quad	.LFE50-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST46:
	.quad	.LFB51-.Ltext0
	.quad	.LCFI144-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI144-.Ltext0
	.quad	.LCFI145-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI145-.Ltext0
	.quad	.LFE51-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST47:
	.quad	.LFB52-.Ltext0
	.quad	.LCFI147-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI147-.Ltext0
	.quad	.LCFI148-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI148-.Ltext0
	.quad	.LFE52-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST48:
	.quad	.LFB53-.Ltext0
	.quad	.LCFI150-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI150-.Ltext0
	.quad	.LCFI151-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI151-.Ltext0
	.quad	.LFE53-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST49:
	.quad	.LFB54-.Ltext0
	.quad	.LCFI153-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI153-.Ltext0
	.quad	.LCFI154-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI154-.Ltext0
	.quad	.LFE54-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
.LLST50:
	.quad	.LFB55-.Ltext0
	.quad	.LCFI156-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI156-.Ltext0
	.quad	.LCFI157-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI157-.Ltext0
	.quad	.LFE55-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	0x0
	.quad	0x0
	.section	.debug_info
	.long	0x1465
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.Ldebug_line0
	.quad	.Letext0
	.quad	.Ltext0
	.string	"GNU C 4.1.2 20080704 (Red Hat 4.1.2-48)"
	.byte	0x1
	.string	"mymath.c"
	.string	"/home/arash/pin/wfs_hArtes_original"
	.uleb128 0x2
	.long	.LASF0
	.byte	0x8
	.byte	0x7
	.uleb128 0x3
	.string	"int"
	.byte	0x4
	.byte	0x5
	.uleb128 0x3
	.string	"long int"
	.byte	0x8
	.byte	0x5
	.uleb128 0x3
	.string	"unsigned char"
	.byte	0x1
	.byte	0x8
	.uleb128 0x3
	.string	"short unsigned int"
	.byte	0x2
	.byte	0x7
	.uleb128 0x3
	.string	"unsigned int"
	.byte	0x4
	.byte	0x7
	.uleb128 0x3
	.string	"signed char"
	.byte	0x1
	.byte	0x6
	.uleb128 0x3
	.string	"short int"
	.byte	0x2
	.byte	0x5
	.uleb128 0x2
	.long	.LASF0
	.byte	0x8
	.byte	0x7
	.uleb128 0x3
	.string	"char"
	.byte	0x1
	.byte	0x6
	.uleb128 0x3
	.string	"long long unsigned int"
	.byte	0x8
	.byte	0x7
	.uleb128 0x3
	.string	"long long int"
	.byte	0x8
	.byte	0x5
	.uleb128 0x3
	.string	"double"
	.byte	0x8
	.byte	0x4
	.uleb128 0x4
	.string	"real"
	.byte	0x2
	.byte	0x42
	.long	0x133
	.uleb128 0x3
	.string	"float"
	.byte	0x4
	.byte	0x4
	.uleb128 0x5
	.long	0x165
	.string	"_cplx"
	.byte	0x8
	.byte	0x2
	.byte	0x47
	.uleb128 0x6
	.string	"re"
	.byte	0x2
	.byte	0x48
	.long	0x127
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.string	"im"
	.byte	0x2
	.byte	0x49
	.long	0x127
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0x0
	.uleb128 0x4
	.string	"complex"
	.byte	0x2
	.byte	0x4a
	.long	0x13c
	.uleb128 0x7
	.long	0x198
	.byte	0x8
	.byte	0x2
	.value	0x1d1
	.uleb128 0x8
	.string	"x"
	.byte	0x2
	.value	0x1d2
	.long	0x127
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x8
	.string	"y"
	.byte	0x2
	.value	0x1d3
	.long	0x127
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0x0
	.uleb128 0x9
	.string	"Vector2d"
	.byte	0x2
	.value	0x1d4
	.long	0x174
	.uleb128 0xa
	.long	0x1f5
	.byte	0x1
	.string	"ldint"
	.byte	0x1
	.byte	0x3f
	.byte	0x1
	.long	0x7d
	.quad	.LFB5
	.quad	.LFE5
	.long	.LLST0
	.uleb128 0xb
	.string	"n"
	.byte	0x1
	.byte	0x3f
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0xc
	.string	"p"
	.byte	0x1
	.byte	0x40
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xc
	.string	"m"
	.byte	0x1
	.byte	0x41
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xa
	.long	0x240
	.byte	0x1
	.string	"cadd"
	.byte	0x1
	.byte	0x4f
	.byte	0x1
	.long	0x165
	.quad	.LFB6
	.quad	.LFE6
	.long	.LLST1
	.uleb128 0xb
	.string	"x"
	.byte	0x1
	.byte	0x4f
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xb
	.string	"y"
	.byte	0x1
	.byte	0x4f
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xc
	.string	"z"
	.byte	0x1
	.byte	0x50
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.uleb128 0xa
	.long	0x28b
	.byte	0x1
	.string	"csub"
	.byte	0x1
	.byte	0x5a
	.byte	0x1
	.long	0x165
	.quad	.LFB7
	.quad	.LFE7
	.long	.LLST2
	.uleb128 0xb
	.string	"x"
	.byte	0x1
	.byte	0x5a
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xb
	.string	"y"
	.byte	0x1
	.byte	0x5a
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xc
	.string	"z"
	.byte	0x1
	.byte	0x5b
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.uleb128 0xa
	.long	0x2f1
	.byte	0x1
	.string	"cmult"
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.long	0x165
	.quad	.LFB8
	.quad	.LFE8
	.long	.LLST3
	.uleb128 0xb
	.string	"x"
	.byte	0x1
	.byte	0x64
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xb
	.string	"y"
	.byte	0x1
	.byte	0x64
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xc
	.string	"z"
	.byte	0x1
	.byte	0x65
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xc
	.string	"ac"
	.byte	0x1
	.byte	0x66
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xc
	.string	"bd"
	.byte	0x1
	.byte	0x66
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xa
	.long	0x34a
	.byte	0x1
	.string	"cdiv"
	.byte	0x1
	.byte	0x79
	.byte	0x1
	.long	0x165
	.quad	.LFB9
	.quad	.LFE9
	.long	.LLST4
	.uleb128 0xb
	.string	"x"
	.byte	0x1
	.byte	0x79
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xb
	.string	"y"
	.byte	0x1
	.byte	0x79
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xc
	.string	"z"
	.byte	0x1
	.byte	0x7a
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xc
	.string	"cd2"
	.byte	0x1
	.byte	0x7b
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xa
	.long	0x397
	.byte	0x1
	.string	"csmult"
	.byte	0x1
	.byte	0x86
	.byte	0x1
	.long	0x165
	.quad	.LFB10
	.quad	.LFE10
	.long	.LLST5
	.uleb128 0xb
	.string	"x"
	.byte	0x1
	.byte	0x86
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xb
	.string	"a"
	.byte	0x1
	.byte	0x86
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0xc
	.string	"z"
	.byte	0x1
	.byte	0x87
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.uleb128 0xa
	.long	0x3e3
	.byte	0x1
	.string	"csdiv"
	.byte	0x1
	.byte	0x90
	.byte	0x1
	.long	0x165
	.quad	.LFB11
	.quad	.LFE11
	.long	.LLST6
	.uleb128 0xb
	.string	"x"
	.byte	0x1
	.byte	0x90
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xb
	.string	"a"
	.byte	0x1
	.byte	0x90
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0xc
	.string	"z"
	.byte	0x1
	.byte	0x91
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.uleb128 0xa
	.long	0x416
	.byte	0x1
	.string	"cmag"
	.byte	0x1
	.byte	0x9a
	.byte	0x1
	.long	0x127
	.quad	.LFB12
	.quad	.LFE12
	.long	.LLST7
	.uleb128 0xb
	.string	"x"
	.byte	0x1
	.byte	0x9a
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.byte	0x0
	.uleb128 0xa
	.long	0x44a
	.byte	0x1
	.string	"_carg"
	.byte	0x1
	.byte	0xa3
	.byte	0x1
	.long	0x127
	.quad	.LFB13
	.quad	.LFE13
	.long	.LLST8
	.uleb128 0xb
	.string	"x"
	.byte	0x1
	.byte	0xa3
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.byte	0x0
	.uleb128 0xa
	.long	0x49a
	.byte	0x1
	.string	"_cexp"
	.byte	0x1
	.byte	0xaa
	.byte	0x1
	.long	0x165
	.quad	.LFB14
	.quad	.LFE14
	.long	.LLST9
	.uleb128 0xb
	.string	"mag"
	.byte	0x1
	.byte	0xaa
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0xb
	.string	"arg"
	.byte	0x1
	.byte	0xaa
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xc
	.string	"z"
	.byte	0x1
	.byte	0xab
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.uleb128 0xa
	.long	0x4f5
	.byte	0x1
	.string	"r2c"
	.byte	0x1
	.byte	0xb5
	.byte	0x1
	.long	0x7d
	.quad	.LFB15
	.quad	.LFE15
	.long	.LLST10
	.uleb128 0xb
	.string	"in"
	.byte	0x1
	.byte	0xb5
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xb
	.string	"out"
	.byte	0x1
	.byte	0xb5
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xb
	.string	"len"
	.byte	0x1
	.byte	0xb5
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0xc
	.string	"i"
	.byte	0x1
	.byte	0xb6
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xd
	.byte	0x8
	.long	0x127
	.uleb128 0xd
	.byte	0x8
	.long	0x165
	.uleb128 0xa
	.long	0x56b
	.byte	0x1
	.string	"c2r"
	.byte	0x1
	.byte	0xbe
	.byte	0x1
	.long	0x7d
	.quad	.LFB16
	.quad	.LFE16
	.long	.LLST11
	.uleb128 0xb
	.string	"in"
	.byte	0x1
	.byte	0xbe
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xb
	.string	"out"
	.byte	0x1
	.byte	0xbe
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0xb
	.string	"len"
	.byte	0x1
	.byte	0xbe
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0xb
	.string	"mode"
	.byte	0x1
	.byte	0xbe
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0xc
	.string	"i"
	.byte	0x1
	.byte	0xbf
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.byte	0x0
	.uleb128 0xe
	.long	0x5dc
	.byte	0x1
	.string	"ffw"
	.byte	0x1
	.byte	0xd7
	.byte	0x1
	.quad	.LFB17
	.quad	.LFE17
	.long	.LLST12
	.uleb128 0xb
	.string	"w"
	.byte	0x1
	.byte	0xd7
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xb
	.string	"idir"
	.byte	0x1
	.byte	0xd7
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0xb
	.string	"n"
	.byte	0x1
	.byte	0xd7
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0xc
	.string	"i"
	.byte	0x1
	.byte	0xd8
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0xc
	.string	"arg"
	.byte	0x1
	.byte	0xd9
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xc
	.string	"phi"
	.byte	0x1
	.byte	0xd9
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.byte	0x0
	.uleb128 0xa
	.long	0x636
	.byte	0x1
	.string	"bitrev"
	.byte	0x1
	.byte	0xe8
	.byte	0x1
	.long	0x7d
	.quad	.LFB18
	.quad	.LFE18
	.long	.LLST13
	.uleb128 0xb
	.string	"i"
	.byte	0x1
	.byte	0xe8
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0xb
	.string	"m"
	.byte	0x1
	.byte	0xe8
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xc
	.string	"ir"
	.byte	0x1
	.byte	0xe9
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xc
	.string	"k"
	.byte	0x1
	.byte	0xe9
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xe
	.long	0x6a5
	.byte	0x1
	.string	"perm"
	.byte	0x1
	.byte	0xf3
	.byte	0x1
	.quad	.LFB19
	.quad	.LFE19
	.long	.LLST14
	.uleb128 0xb
	.string	"x"
	.byte	0x1
	.byte	0xf3
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xb
	.string	"m"
	.byte	0x1
	.byte	0xf3
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0xc
	.string	"n"
	.byte	0x1
	.byte	0xf4
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xc
	.string	"i"
	.byte	0x1
	.byte	0xf4
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xc
	.string	"ir"
	.byte	0x1
	.byte	0xf4
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xc
	.string	"temp"
	.byte	0x1
	.byte	0xf5
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xf
	.long	0x71e
	.byte	0x1
	.string	"permrev"
	.byte	0x1
	.value	0x107
	.byte	0x1
	.quad	.LFB20
	.quad	.LFE20
	.long	.LLST15
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x107
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"m"
	.byte	0x1
	.value	0x107
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x11
	.string	"n"
	.byte	0x1
	.value	0x108
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x108
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x11
	.string	"ir"
	.byte	0x1
	.value	0x108
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x11
	.string	"temp"
	.byte	0x1
	.value	0x109
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xf
	.long	0x76c
	.byte	0x1
	.string	"permcpy"
	.byte	0x1
	.value	0x119
	.byte	0x1
	.quad	.LFB21
	.quad	.LFE21
	.long	.LLST16
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x119
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.value	0x119
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x10
	.string	"m"
	.byte	0x1
	.value	0x119
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.byte	0x0
	.uleb128 0xf
	.long	0x7bd
	.byte	0x1
	.string	"permrevcpy"
	.byte	0x1
	.value	0x120
	.byte	0x1
	.quad	.LFB22
	.quad	.LFE22
	.long	.LLST17
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x120
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.value	0x120
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x10
	.string	"m"
	.byte	0x1
	.value	0x120
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.byte	0x0
	.uleb128 0xf
	.long	0x8aa
	.byte	0x1
	.string	"fft1d"
	.byte	0x1
	.value	0x127
	.byte	0x1
	.quad	.LFB23
	.quad	.LFE23
	.long	.LLST18
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x127
	.long	0x4fb
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x10
	.string	"w"
	.byte	0x1
	.value	0x127
	.long	0x4fb
	.byte	0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x10
	.string	"idir"
	.byte	0x1
	.value	0x127
	.long	0x7d
	.byte	0x3
	.byte	0x91
	.sleb128 -84
	.uleb128 0x10
	.string	"n"
	.byte	0x1
	.value	0x127
	.long	0x7d
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x128
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x11
	.string	"u"
	.byte	0x1
	.value	0x128
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.string	"v"
	.byte	0x1
	.value	0x128
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x11
	.string	"inca"
	.byte	0x1
	.value	0x128
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x11
	.string	"incb"
	.byte	0x1
	.value	0x128
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x11
	.string	"incn"
	.byte	0x1
	.value	0x128
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x11
	.string	"j"
	.byte	0x1
	.value	0x128
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x11
	.string	"k"
	.byte	0x1
	.value	0x128
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x11
	.string	"ell"
	.byte	0x1
	.value	0x128
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x11
	.string	"z"
	.byte	0x1
	.value	0x129
	.long	0x165
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.byte	0x0
	.uleb128 0xf
	.long	0x8f7
	.byte	0x1
	.string	"fftrev"
	.byte	0x1
	.value	0x153
	.byte	0x1
	.quad	.LFB24
	.quad	.LFE24
	.long	.LLST19
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x153
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x10
	.string	"w"
	.byte	0x1
	.value	0x153
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x10
	.string	"m"
	.byte	0x1
	.value	0x153
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.byte	0x0
	.uleb128 0xf
	.long	0x941
	.byte	0x1
	.string	"fft"
	.byte	0x1
	.value	0x15b
	.byte	0x1
	.quad	.LFB25
	.quad	.LFE25
	.long	.LLST20
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x15b
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x10
	.string	"w"
	.byte	0x1
	.value	0x15b
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x10
	.string	"m"
	.byte	0x1
	.value	0x15b
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.byte	0x0
	.uleb128 0xf
	.long	0x98c
	.byte	0x1
	.string	"ifft"
	.byte	0x1
	.value	0x164
	.byte	0x1
	.quad	.LFB26
	.quad	.LFE26
	.long	.LLST21
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x164
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x10
	.string	"w"
	.byte	0x1
	.value	0x164
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x10
	.string	"m"
	.byte	0x1
	.value	0x164
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.byte	0x0
	.uleb128 0xf
	.long	0x9d8
	.byte	0x1
	.string	"ifftr"
	.byte	0x1
	.value	0x16d
	.byte	0x1
	.quad	.LFB27
	.quad	.LFE27
	.long	.LLST22
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x16d
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x10
	.string	"w"
	.byte	0x1
	.value	0x16d
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x10
	.string	"m"
	.byte	0x1
	.value	0x16d
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.byte	0x0
	.uleb128 0xf
	.long	0xa32
	.byte	0x1
	.string	"fftcpy"
	.byte	0x1
	.value	0x174
	.byte	0x1
	.quad	.LFB28
	.quad	.LFE28
	.long	.LLST23
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x174
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.value	0x174
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x10
	.string	"w"
	.byte	0x1
	.value	0x174
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"m"
	.byte	0x1
	.value	0x174
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.byte	0x0
	.uleb128 0xf
	.long	0xa8d
	.byte	0x1
	.string	"ifftcpy"
	.byte	0x1
	.value	0x17c
	.byte	0x1
	.quad	.LFB29
	.quad	.LFE29
	.long	.LLST24
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x17c
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.value	0x17c
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x10
	.string	"w"
	.byte	0x1
	.value	0x17c
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"m"
	.byte	0x1
	.value	0x17c
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.byte	0x0
	.uleb128 0xf
	.long	0xb43
	.byte	0x1
	.string	"fconv"
	.byte	0x1
	.value	0x186
	.byte	0x1
	.quad	.LFB30
	.quad	.LFE30
	.long	.LLST25
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x186
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x10
	.string	"h"
	.byte	0x1
	.value	0x186
	.long	0x4fb
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.value	0x186
	.long	0x4fb
	.byte	0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x10
	.string	"wf"
	.byte	0x1
	.value	0x186
	.long	0x4fb
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x10
	.string	"wi"
	.byte	0x1
	.value	0x186
	.long	0x4fb
	.byte	0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x10
	.string	"m"
	.byte	0x1
	.value	0x186
	.long	0x7d
	.byte	0x3
	.byte	0x91
	.sleb128 -100
	.uleb128 0x11
	.string	"xspec"
	.byte	0x1
	.value	0x187
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.string	"hspec"
	.byte	0x1
	.value	0x187
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x11
	.string	"n"
	.byte	0x1
	.value	0x188
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x188
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.byte	0x0
	.uleb128 0xf
	.long	0xbc8
	.byte	0x1
	.string	"fwconv"
	.byte	0x1
	.value	0x19a
	.byte	0x1
	.quad	.LFB31
	.quad	.LFE31
	.long	.LLST26
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x19a
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x10
	.string	"h"
	.byte	0x1
	.value	0x19a
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.value	0x19a
	.long	0x4fb
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x10
	.string	"m"
	.byte	0x1
	.value	0x19a
	.long	0x7d
	.byte	0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x11
	.string	"wf"
	.byte	0x1
	.value	0x19b
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x11
	.string	"wi"
	.byte	0x1
	.value	0x19b
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x11
	.string	"n"
	.byte	0x1
	.value	0x19c
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xf
	.long	0xc60
	.byte	0x1
	.string	"tconv"
	.byte	0x1
	.value	0x1ab
	.byte	0x1
	.quad	.LFB32
	.quad	.LFE32
	.long	.LLST27
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x1ab
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x10
	.string	"xlen"
	.byte	0x1
	.value	0x1ab
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x10
	.string	"h"
	.byte	0x1
	.value	0x1ab
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x10
	.string	"hlen"
	.byte	0x1
	.value	0x1ab
	.long	0x7d
	.byte	0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.value	0x1ab
	.long	0x4fb
	.byte	0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x1ac
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x11
	.string	"j"
	.byte	0x1
	.value	0x1ac
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x11
	.string	"ylen"
	.byte	0x1
	.value	0x1ad
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.byte	0x0
	.uleb128 0xf
	.long	0xcc7
	.byte	0x1
	.string	"vadd"
	.byte	0x1
	.value	0x1cb
	.byte	0x1
	.quad	.LFB33
	.quad	.LFE33
	.long	.LLST28
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x1cb
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.value	0x1cb
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x10
	.string	"dim"
	.byte	0x1
	.value	0x1cb
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x10
	.string	"z"
	.byte	0x1
	.value	0x1cb
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x1cc
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xf
	.long	0xd2e
	.byte	0x1
	.string	"vsub"
	.byte	0x1
	.value	0x1d5
	.byte	0x1
	.quad	.LFB34
	.quad	.LFE34
	.long	.LLST29
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x1d5
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.value	0x1d5
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x10
	.string	"dim"
	.byte	0x1
	.value	0x1d5
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x10
	.string	"z"
	.byte	0x1
	.value	0x1d5
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x1d6
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0x12
	.long	0xd9d
	.byte	0x1
	.string	"vdotprod"
	.byte	0x1
	.value	0x1df
	.byte	0x1
	.long	0x127
	.quad	.LFB35
	.quad	.LFE35
	.long	.LLST30
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x1df
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"dim"
	.byte	0x1
	.value	0x1df
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.value	0x1df
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x1e0
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x11
	.string	"z"
	.byte	0x1
	.value	0x1e1
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xf
	.long	0xdfd
	.byte	0x1
	.string	"vcrossprod"
	.byte	0x1
	.value	0x1ec
	.byte	0x1
	.quad	.LFB36
	.quad	.LFE36
	.long	.LLST31
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x1ec
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.value	0x1ec
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x10
	.string	"dim"
	.byte	0x1
	.value	0x1ec
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x10
	.string	"z"
	.byte	0x1
	.value	0x1ec
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.byte	0x0
	.uleb128 0xf
	.long	0xe66
	.byte	0x1
	.string	"vsmult"
	.byte	0x1
	.value	0x1fa
	.byte	0x1
	.quad	.LFB37
	.quad	.LFE37
	.long	.LLST32
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x1fa
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"a"
	.byte	0x1
	.value	0x1fa
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x10
	.string	"dim"
	.byte	0x1
	.value	0x1fa
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x10
	.string	"z"
	.byte	0x1
	.value	0x1fa
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x1fb
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0x12
	.long	0xec6
	.byte	0x1
	.string	"vmag"
	.byte	0x1
	.value	0x204
	.byte	0x1
	.long	0x127
	.quad	.LFB38
	.quad	.LFE38
	.long	.LLST33
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x204
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"dim"
	.byte	0x1
	.value	0x204
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x205
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x11
	.string	"mag"
	.byte	0x1
	.value	0x206
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xf
	.long	0xf1b
	.byte	0x1
	.string	"zeroCplxVec"
	.byte	0x1
	.value	0x215
	.byte	0x1
	.quad	.LFB39
	.quad	.LFE39
	.long	.LLST34
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x215
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"xlen"
	.byte	0x1
	.value	0x215
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x216
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xf
	.long	0xf70
	.byte	0x1
	.string	"zeroRealVec"
	.byte	0x1
	.value	0x21d
	.byte	0x1
	.quad	.LFB40
	.quad	.LFE40
	.long	.LLST35
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x21d
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"xlen"
	.byte	0x1
	.value	0x21d
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x21e
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0x12
	.long	0xfd6
	.byte	0x1
	.string	"callocCplxArr"
	.byte	0x1
	.value	0x227
	.byte	0x1
	.long	0xfd6
	.quad	.LFB41
	.quad	.LFE41
	.long	.LLST36
	.uleb128 0x10
	.string	"M"
	.byte	0x1
	.value	0x227
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x10
	.string	"N"
	.byte	0x1
	.value	0x227
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x228
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x11
	.string	"aa"
	.byte	0x1
	.value	0x229
	.long	0xfd6
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.uleb128 0xd
	.byte	0x8
	.long	0x4fb
	.uleb128 0x12
	.long	0x1042
	.byte	0x1
	.string	"callocRealArr"
	.byte	0x1
	.value	0x231
	.byte	0x1
	.long	0x1042
	.quad	.LFB42
	.quad	.LFE42
	.long	.LLST37
	.uleb128 0x10
	.string	"M"
	.byte	0x1
	.value	0x231
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x10
	.string	"N"
	.byte	0x1
	.value	0x231
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x232
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x11
	.string	"aa"
	.byte	0x1
	.value	0x233
	.long	0x1042
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.uleb128 0xd
	.byte	0x8
	.long	0x4f5
	.uleb128 0xf
	.long	0x109b
	.byte	0x1
	.string	"freeCplxArr"
	.byte	0x1
	.value	0x23b
	.byte	0x1
	.quad	.LFB43
	.quad	.LFE43
	.long	.LLST38
	.uleb128 0x10
	.string	"aa"
	.byte	0x1
	.value	0x23b
	.long	0xfd6
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"M"
	.byte	0x1
	.value	0x23b
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x23c
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xf
	.long	0x10ee
	.byte	0x1
	.string	"freeRealArr"
	.byte	0x1
	.value	0x243
	.byte	0x1
	.quad	.LFB44
	.quad	.LFE44
	.long	.LLST39
	.uleb128 0x10
	.string	"aa"
	.byte	0x1
	.value	0x243
	.long	0x1042
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"M"
	.byte	0x1
	.value	0x243
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x244
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xf
	.long	0x1141
	.byte	0x1
	.string	"printCplxVec"
	.byte	0x1
	.value	0x24c
	.byte	0x1
	.quad	.LFB45
	.quad	.LFE45
	.long	.LLST40
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x24c
	.long	0x4fb
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"n"
	.byte	0x1
	.value	0x24c
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x24d
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xf
	.long	0x1194
	.byte	0x1
	.string	"printRealVec"
	.byte	0x1
	.value	0x254
	.byte	0x1
	.quad	.LFB46
	.quad	.LFE46
	.long	.LLST41
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.value	0x254
	.long	0x4f5
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"n"
	.byte	0x1
	.value	0x254
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x255
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xf
	.long	0x11e4
	.byte	0x1
	.string	"printBits"
	.byte	0x1
	.value	0x25c
	.byte	0x1
	.quad	.LFB47
	.quad	.LFE47
	.long	.LLST42
	.uleb128 0x10
	.string	"n"
	.byte	0x1
	.value	0x25c
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x11
	.string	"u"
	.byte	0x1
	.value	0x25d
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x11
	.string	"i"
	.byte	0x1
	.value	0x25d
	.long	0x7d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0x12
	.long	0x122a
	.byte	0x1
	.string	"vmag2d"
	.byte	0x1
	.value	0x268
	.byte	0x1
	.long	0x127
	.quad	.LFB48
	.quad	.LFE48
	.long	.LLST43
	.uleb128 0x10
	.string	"v"
	.byte	0x1
	.value	0x267
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x11
	.string	"mag"
	.byte	0x1
	.value	0x269
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0x12
	.long	0x1270
	.byte	0x1
	.string	"varg2d"
	.byte	0x1
	.value	0x276
	.byte	0x1
	.long	0x127
	.quad	.LFB49
	.quad	.LFE49
	.long	.LLST44
	.uleb128 0x10
	.string	"v"
	.byte	0x1
	.value	0x275
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x11
	.string	"arg"
	.byte	0x1
	.value	0x277
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0x12
	.long	0x12c7
	.byte	0x1
	.string	"vmult2d"
	.byte	0x1
	.value	0x27f
	.byte	0x1
	.long	0x127
	.quad	.LFB50
	.quad	.LFE50
	.long	.LLST45
	.uleb128 0x10
	.string	"v1"
	.byte	0x1
	.value	0x27e
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"v2"
	.byte	0x1
	.value	0x27e
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.string	"mult"
	.byte	0x1
	.value	0x280
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0x12
	.long	0x131c
	.byte	0x1
	.string	"vsmult2d"
	.byte	0x1
	.value	0x28a
	.byte	0x1
	.long	0x198
	.quad	.LFB51
	.quad	.LFE51
	.long	.LLST46
	.uleb128 0x10
	.string	"v1"
	.byte	0x1
	.value	0x289
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"a"
	.byte	0x1
	.value	0x289
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x11
	.string	"v2"
	.byte	0x1
	.value	0x28b
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.uleb128 0x12
	.long	0x136f
	.byte	0x1
	.string	"vadd2d"
	.byte	0x1
	.value	0x295
	.byte	0x1
	.long	0x198
	.quad	.LFB52
	.quad	.LFE52
	.long	.LLST47
	.uleb128 0x10
	.string	"v1"
	.byte	0x1
	.value	0x294
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"v2"
	.byte	0x1
	.value	0x294
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.string	"v"
	.byte	0x1
	.value	0x296
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.uleb128 0x12
	.long	0x13c2
	.byte	0x1
	.string	"vsub2d"
	.byte	0x1
	.value	0x29f
	.byte	0x1
	.long	0x198
	.quad	.LFB53
	.quad	.LFE53
	.long	.LLST48
	.uleb128 0x10
	.string	"v1"
	.byte	0x1
	.value	0x29e
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"v2"
	.byte	0x1
	.value	0x29e
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.string	"v"
	.byte	0x1
	.value	0x2a0
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0x0
	.uleb128 0x12
	.long	0x1417
	.byte	0x1
	.string	"vcos2d"
	.byte	0x1
	.value	0x2a9
	.byte	0x1
	.long	0x127
	.quad	.LFB54
	.quad	.LFE54
	.long	.LLST49
	.uleb128 0x10
	.string	"v1"
	.byte	0x1
	.value	0x2a8
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"v2"
	.byte	0x1
	.value	0x2a8
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.string	"cos"
	.byte	0x1
	.value	0x2aa
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0x13
	.byte	0x1
	.string	"vsin2d"
	.byte	0x1
	.value	0x2b3
	.byte	0x1
	.long	0x127
	.quad	.LFB55
	.quad	.LFE55
	.long	.LLST50
	.uleb128 0x10
	.string	"v1"
	.byte	0x1
	.value	0x2b2
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x10
	.string	"v2"
	.byte	0x1
	.value	0x2b2
	.long	0x198
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.string	"sin"
	.byte	0x1
	.value	0x2b4
	.long	0x127
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x10
	.uleb128 0x6
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.long	0x259
	.value	0x2
	.long	.Ldebug_info0
	.long	0x1469
	.long	0x1a9
	.string	"ldint"
	.long	0x1f5
	.string	"cadd"
	.long	0x240
	.string	"csub"
	.long	0x28b
	.string	"cmult"
	.long	0x2f1
	.string	"cdiv"
	.long	0x34a
	.string	"csmult"
	.long	0x397
	.string	"csdiv"
	.long	0x3e3
	.string	"cmag"
	.long	0x416
	.string	"_carg"
	.long	0x44a
	.string	"_cexp"
	.long	0x49a
	.string	"r2c"
	.long	0x501
	.string	"c2r"
	.long	0x56b
	.string	"ffw"
	.long	0x5dc
	.string	"bitrev"
	.long	0x636
	.string	"perm"
	.long	0x6a5
	.string	"permrev"
	.long	0x71e
	.string	"permcpy"
	.long	0x76c
	.string	"permrevcpy"
	.long	0x7bd
	.string	"fft1d"
	.long	0x8aa
	.string	"fftrev"
	.long	0x8f7
	.string	"fft"
	.long	0x941
	.string	"ifft"
	.long	0x98c
	.string	"ifftr"
	.long	0x9d8
	.string	"fftcpy"
	.long	0xa32
	.string	"ifftcpy"
	.long	0xa8d
	.string	"fconv"
	.long	0xb43
	.string	"fwconv"
	.long	0xbc8
	.string	"tconv"
	.long	0xc60
	.string	"vadd"
	.long	0xcc7
	.string	"vsub"
	.long	0xd2e
	.string	"vdotprod"
	.long	0xd9d
	.string	"vcrossprod"
	.long	0xdfd
	.string	"vsmult"
	.long	0xe66
	.string	"vmag"
	.long	0xec6
	.string	"zeroCplxVec"
	.long	0xf1b
	.string	"zeroRealVec"
	.long	0xf70
	.string	"callocCplxArr"
	.long	0xfdc
	.string	"callocRealArr"
	.long	0x1048
	.string	"freeCplxArr"
	.long	0x109b
	.string	"freeRealArr"
	.long	0x10ee
	.string	"printCplxVec"
	.long	0x1141
	.string	"printRealVec"
	.long	0x1194
	.string	"printBits"
	.long	0x11e4
	.string	"vmag2d"
	.long	0x122a
	.string	"varg2d"
	.long	0x1270
	.string	"vmult2d"
	.long	0x12c7
	.string	"vsmult2d"
	.long	0x131c
	.string	"vadd2d"
	.long	0x136f
	.string	"vsub2d"
	.long	0x13c2
	.string	"vcos2d"
	.long	0x1417
	.string	"vsin2d"
	.long	0x0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0x0
	.value	0x0
	.value	0x0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0x0
	.quad	0x0
	.section	.debug_str,"",@progbits
.LASF0:
	.string	"long unsigned int"
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-48)"
	.section	.note.GNU-stack,"",@progbits

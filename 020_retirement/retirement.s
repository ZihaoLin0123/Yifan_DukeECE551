	.file	"retirement.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"Age %3d month %2d you have $%.2lf\n"
	.text
	.globl	retirement
	.type	retirement, @function
retirement:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -36(%rbp)
	movsd	%xmm0, -48(%rbp)
	movsd	-48(%rbp), %xmm0
	movsd	%xmm0, -8(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L2
.L3:
	movl	-20(%rbp), %esi
	movl	$715827883, %edx
	movl	%esi, %eax
	imull	%edx
	sarl	%edx
	movl	%esi, %eax
	sarl	$31, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	%eax, %eax
	addl	%ecx, %eax
	sall	$2, %eax
	movl	%esi, %ecx
	subl	%eax, %ecx
	movl	-20(%rbp), %esi
	movl	$715827883, %edx
	movl	%esi, %eax
	imull	%edx
	sarl	%edx
	movl	%esi, %eax
	sarl	$31, %eax
	movl	%edx, %esi
	subl	%eax, %esi
	movq	-8(%rbp), %rax
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	movl	%ecx, %edx
	leaq	.LC0(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movsd	32(%rbp), %xmm1
	movsd	24(%rbp), %xmm0
	movq	-8(%rbp), %rax
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	call	calculation
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	addl	$1, -20(%rbp)
	addl	$1, -16(%rbp)
.L2:
	movl	16(%rbp), %eax
	cmpl	%eax, -16(%rbp)
	jl	.L3
	movl	$0, -12(%rbp)
	jmp	.L4
.L5:
	movl	-20(%rbp), %esi
	movl	$715827883, %edx
	movl	%esi, %eax
	imull	%edx
	sarl	%edx
	movl	%esi, %eax
	sarl	$31, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	%eax, %eax
	addl	%ecx, %eax
	sall	$2, %eax
	movl	%esi, %ecx
	subl	%eax, %ecx
	movl	-20(%rbp), %esi
	movl	$715827883, %edx
	movl	%esi, %eax
	imull	%edx
	sarl	%edx
	movl	%esi, %eax
	sarl	$31, %eax
	movl	%edx, %esi
	subl	%eax, %esi
	movq	-8(%rbp), %rax
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	movl	%ecx, %edx
	leaq	.LC0(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movsd	56(%rbp), %xmm1
	movsd	48(%rbp), %xmm0
	movq	-8(%rbp), %rax
	movapd	%xmm1, %xmm2
	movapd	%xmm0, %xmm1
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	call	calculation
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	addl	$1, -20(%rbp)
	addl	$1, -12(%rbp)
.L4:
	movl	40(%rbp), %eax
	cmpl	%eax, -12(%rbp)
	jl	.L5
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	retirement, .-retirement
	.globl	calculation
	.type	calculation, @function
calculation:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movsd	%xmm0, -24(%rbp)
	movsd	%xmm1, -32(%rbp)
	movsd	%xmm2, -40(%rbp)
	movsd	-24(%rbp), %xmm0
	mulsd	-40(%rbp), %xmm0
	addsd	-24(%rbp), %xmm0
	movsd	-32(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	calculation, .-calculation
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	$489, -64(%rbp)
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -56(%rbp)
	movsd	.LC2(%rip), %xmm0
	movsd	%xmm0, -48(%rbp)
	movl	$384, -32(%rbp)
	movsd	.LC3(%rip), %xmm0
	movsd	%xmm0, -24(%rbp)
	movsd	.LC4(%rip), %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	.LC5(%rip), %rax
	pushq	-16(%rbp)
	pushq	-24(%rbp)
	pushq	-32(%rbp)
	pushq	-48(%rbp)
	pushq	-56(%rbp)
	pushq	-64(%rbp)
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$327, %edi
	call	retirement
	addq	$48, %rsp
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1083129856
	.align 8
.LC2:
	.long	3951369912
	.long	1064220753
	.align 8
.LC3:
	.long	0
	.long	-1062256640
	.align 8
.LC4:
	.long	3035110223
	.long	1061899905
	.align 8
.LC5:
	.long	0
	.long	1087690816
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

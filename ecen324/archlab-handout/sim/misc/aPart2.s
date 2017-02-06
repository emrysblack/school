	.file	"aPart2.c"
	.text
.globl rsum_list
	.type	rsum_list, @function
rsum_list:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	8(%ebp), %ebx
	movl	$0, %eax
	testl	%ebx, %ebx
	je	.L3
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	rsum_list
	addl	(%ebx), %eax
.L3:
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	rsum_list, .-rsum_list
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-11)"
	.section	.note.GNU-stack,"",@progbits

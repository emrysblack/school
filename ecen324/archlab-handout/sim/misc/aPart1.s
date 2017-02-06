	.file	"aPart1.c"
	.text
.globl sum_list
	.type	sum_list, @function
sum_list:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	$0, %eax
	testl	%edx, %edx
	je	.L3
.L6:
	addl	(%edx), %eax
	movl	4(%edx), %edx
	testl	%edx, %edx
	jne	.L6
.L3:
	popl	%ebp
	ret
	.size	sum_list, .-sum_list
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	$0, (%esp)
	call	sum_list
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-11)"
	.section	.note.GNU-stack,"",@progbits

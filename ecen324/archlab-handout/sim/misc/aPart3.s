	.file	"aPart3.c"
	.text
.globl copy_block
	.type	copy_block, @function
copy_block:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %edi
	movl	12(%ebp), %esi
	movl	16(%ebp), %ecx
	movl	$0, %edx
	movl	$0, %eax
	testl	%ecx, %ecx
	jle	.L3
.L6:
	movl	(%edi,%edx), %ebx
	movl	%ebx, (%esi,%edx)
	xorl	%ebx, %eax
	addl	$4, %edx
	subl	$1, %ecx
	jne	.L6
.L3:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	copy_block, .-copy_block
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$0, (%esp)
	call	rsum_list
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-11)"
	.section	.note.GNU-stack,"",@progbits

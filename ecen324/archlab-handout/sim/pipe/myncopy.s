	.file	"myncopy.c"
	.text
.globl ncopy
	.type	ncopy, @function
ncopy:
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
	testl	%ebx, %ebx
	setne	%bl
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	addl	$4, %edx
	subl	$1, %ecx
	jne	.L6
.L3:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ncopy, .-ncopy
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"count=%d\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$0, %eax
	movl	$src-4, %edx
.L9:
	addl	$1, %eax
	movl	%eax, (%edx,%eax,4)
	cmpl	$8, %eax
	jne	.L9
	movl	$8, 8(%esp)
	movl	$dst, 4(%esp)
	movl	$src, (%esp)
	call	ncopy
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	$0, (%esp)
	call	exit
	.size	main, .-main
	.comm	src,32,32
	.comm	dst,32,32
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-11)"
	.section	.note.GNU-stack,"",@progbits

	.file	"exercise-6-2.c"
	.text
	.globl	are_first_n_chars_identical
	.def	are_first_n_chars_identical;	.scl	2;	.type	32;	.endef
	.seh_proc	are_first_n_chars_identical
are_first_n_chars_identical:
	.seh_endprologue
	xorl	%eax, %eax
.L2:
	cmpl	%eax, %r8d
	jle	.L7
	movb	(%rcx,%rax), %r9b
	cmpb	%r9b, (%rdx,%rax)
	setne	%r10b
	testb	%r9b, %r9b
	sete	%r9b
	incq	%rax
	orb	%r9b, %r10b
	je	.L2
	xorl	%eax, %eax
	jmp	.L1
.L7:
	movl	$1, %eax
.L1:
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "Error while creating subtree node ! memory error\0"
.LC1:
	.ascii "Error while copying the word to subtree\0"
	.text
	.globl	add_subtree
	.def	add_subtree;	.scl	2;	.type	32;	.endef
	.seh_proc	add_subtree
add_subtree:
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	testq	%rcx, %rcx
	movq	%rcx, %rbx
	movq	%rdx, %rsi
	jne	.L9
	movl	$40, %ecx
	call	malloc
	testq	%rax, %rax
	movq	%rax, %rbx
	jne	.L10
	leaq	.LC0(%rip), %rcx
	call	puts
	jmp	.L11
.L10:
	xorl	%eax, %eax
	orq	$-1, %rcx
	movq	%rsi, %rdi
	repnz scasb
	movq	%rcx, %rdx
	notq	%rdx
	movq	%rdx, %rcx
	call	malloc
	testq	%rax, %rax
	movq	%rax, (%rbx)
	jne	.L12
	leaq	.LC1(%rip), %rcx
	xorl	%ebx, %ebx
	call	printf
	jmp	.L11
.L12:
	movq	$0, 16(%rbx)
	movq	%rsi, %rdx
	movq	%rax, %rcx
	movq	$0, 8(%rbx)
	call	strcpy
	jmp	.L11
.L9:
	movq	(%rcx), %rdx
	movq	%rsi, %rcx
	call	strcmp
	testl	%eax, %eax
	jle	.L13
	movq	16(%rbx), %rcx
	movq	%rsi, %rdx
	call	add_subtree
	movq	%rax, 16(%rbx)
	jmp	.L11
.L13:
	je	.L11
	movq	8(%rbx), %rcx
	movq	%rsi, %rdx
	call	add_subtree
	movq	%rax, 8(%rbx)
.L11:
	movq	%rbx, %rax
	addq	$32, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC2:
	.ascii "Error while creating node ! memory error\0"
.LC3:
	.ascii "Error while copying the word\0"
	.text
	.globl	add_tree
	.def	add_tree;	.scl	2;	.type	32;	.endef
	.seh_proc	add_tree
add_tree:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	testq	%rcx, %rcx
	movq	%rcx, %rbx
	movq	%rdx, %rsi
	jne	.L18
	movl	$40, %ecx
	call	malloc
	testq	%rax, %rax
	movq	%rax, %rbp
	jne	.L19
	leaq	.LC2(%rip), %rcx
	call	puts
	jmp	.L20
.L19:
	xorl	%eax, %eax
	orq	$-1, %rcx
	movq	%rsi, %rdi
	repnz scasb
	movq	%rcx, %rdx
	notq	%rdx
	movq	%rdx, %rcx
	call	malloc
	testq	%rax, %rax
	movq	%rax, 0(%rbp)
	jne	.L21
	leaq	.LC3(%rip), %rcx
	call	printf
	jmp	.L20
.L21:
	movq	$0, 16(%rbp)
	movq	%rsi, %rdx
	movq	%rax, %rcx
	movq	%rbp, %rbx
	movq	$0, 8(%rbp)
	movq	$0, 32(%rbp)
	movq	$0, 24(%rbp)
	call	strcpy
	jmp	.L20
.L18:
	movq	(%rcx), %r11
	movl	n(%rip), %r8d
	movq	%r11, %rcx
	call	are_first_n_chars_identical
	movq	%rsi, %rcx
	movl	%eax, %ebp
	movq	%r11, %rdx
	call	strcmp
	testl	%ebp, %ebp
	je	.L22
	testl	%eax, %eax
	jle	.L23
	movq	32(%rbx), %rcx
	movq	%rsi, %rdx
	call	add_subtree
	movq	%rax, 32(%rbx)
.L23:
	movq	(%rbx), %rdx
	movq	%rsi, %rcx
	call	strcmp
	testl	%eax, %eax
	jns	.L20
	movq	24(%rbx), %rcx
	movq	%rsi, %rdx
	call	add_subtree
	movq	%rax, 24(%rbx)
	jmp	.L20
.L22:
	testl	%eax, %eax
	jle	.L25
	movq	16(%rbx), %rcx
	movq	%rsi, %rdx
	call	add_tree
	movq	%rax, 16(%rbx)
	jmp	.L20
.L25:
	je	.L20
	movq	8(%rbx), %rcx
	movq	%rsi, %rdx
	call	add_tree
	movq	%rax, 8(%rbx)
.L20:
	movq	%rbx, %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	ret
	.seh_endproc
	.globl	print_subtree
	.def	print_subtree;	.scl	2;	.type	32;	.endef
	.seh_proc	print_subtree
print_subtree:
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, %rbx
.L32:
	testq	%rbx, %rbx
	je	.L30
	movq	8(%rbx), %rcx
	call	print_subtree
	movq	(%rbx), %rcx
	call	puts
	movq	16(%rbx), %rbx
	jmp	.L32
.L30:
	addq	$32, %rsp
	popq	%rbx
	ret
	.seh_endproc
	.globl	print_tree
	.def	print_tree;	.scl	2;	.type	32;	.endef
	.seh_proc	print_tree
print_tree:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movq	%rcx, %rbx
	movl	%edx, %esi
.L37:
	testq	%rbx, %rbx
	je	.L33
	movq	24(%rbx), %rcx
	call	print_subtree
	testl	%esi, %esi
	jne	.L35
	cmpq	$0, 24(%rbx)
	jne	.L35
	cmpq	$0, 32(%rbx)
	je	.L36
.L35:
	movq	(%rbx), %rcx
	call	puts
.L36:
	movq	32(%rbx), %rcx
	xorl	%esi, %esi
	call	print_subtree
	movq	8(%rbx), %rcx
	xorl	%edx, %edx
	call	print_tree
	movq	16(%rbx), %rbx
	jmp	.L37
.L33:
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	ret
	.seh_endproc
	.globl	free_subtree
	.def	free_subtree;	.scl	2;	.type	32;	.endef
	.seh_proc	free_subtree
free_subtree:
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	testq	%rcx, %rcx
	movq	%rcx, %rbx
	je	.L38
	movq	8(%rcx), %rcx
	call	free_subtree
	movq	16(%rbx), %rcx
	call	free_subtree
	movq	(%rbx), %rcx
	call	free
	movq	%rbx, %rcx
	addq	$32, %rsp
	popq	%rbx
	jmp	free
.L38:
	addq	$32, %rsp
	popq	%rbx
	ret
	.seh_endproc
	.globl	free_tree
	.def	free_tree;	.scl	2;	.type	32;	.endef
	.seh_proc	free_tree
free_tree:
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	testq	%rcx, %rcx
	movq	%rcx, %rbx
	je	.L40
	movq	8(%rcx), %rcx
	call	free_tree
	movq	16(%rbx), %rcx
	call	free_tree
	movq	24(%rbx), %rcx
	call	free_subtree
	movq	32(%rbx), %rcx
	call	free_subtree
	movq	(%rbx), %rcx
	call	free
	movq	%rbx, %rcx
	addq	$32, %rsp
	popq	%rbx
	jmp	free
.L40:
	addq	$32, %rsp
	popq	%rbx
	ret
	.seh_endproc
	.globl	is_invalid_char
	.def	is_invalid_char;	.scl	2;	.type	32;	.endef
	.seh_proc	is_invalid_char
is_invalid_char:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	xorl	%eax, %eax
	cmpl	$-1, %ecx
	je	.L42
	cmpl	$32, %ecx
	movl	$1, %eax
	je	.L42
	call	*__imp_isalnum(%rip)
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
.L42:
	addq	$40, %rsp
	ret
	.seh_endproc
	.globl	get_word
	.def	get_word;	.scl	2;	.type	32;	.endef
	.seh_proc	get_word
get_word:
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	$1, %eax
	movq	__imp___acrt_iob_func(%rip), %rdi
	testq	%rcx, %rcx
	movq	%rcx, %rsi
	movq	%rdx, %rbp
	je	.L46
.L49:
	call	getchar
	movl	%eax, %ecx
	movl	%eax, %ebx
	call	is_invalid_char
	testl	%eax, %eax
	je	.L63
	cmpl	$47, %ebx
	jne	.L49
	call	getchar
	cmpl	$47, %eax
	movl	%eax, %ebx
	jne	.L50
.L52:
	call	getchar
	testl	%eax, %eax
	je	.L49
	cmpl	$10, %eax
	jne	.L52
	jmp	.L49
.L50:
	xorl	%ecx, %ecx
	call	*%rdi
	movl	%ebx, %ecx
	movq	%rax, %rdx
	call	ungetc
	jmp	.L49
.L63:
	cmpl	$-1, %ebx
	je	.L46
	movb	%bl, (%rsi)
	decq	%rbp
	movl	$1, %ebx
.L54:
	leaq	(%rsi,%rbx), %r12
	cmpq	%rbp, %rbx
	jnb	.L56
	call	getchar
	cmpl	$-1, %eax
	movl	%eax, %edi
	je	.L56
	movl	%eax, %ecx
	call	is_invalid_char
	testl	%eax, %eax
	je	.L57
	xorl	%ecx, %ecx
	call	*__imp___acrt_iob_func(%rip)
	movl	%edi, %ecx
	movq	%rax, %rdx
	call	ungetc
	jmp	.L56
.L57:
	incq	%rbx
	movb	%dil, -1(%rsi,%rbx)
	jmp	.L54
.L56:
	movb	$0, (%r12)
	movl	$2, %eax
.L46:
	addq	$32, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC4:
	.ascii "Usage: ./exercise-6-2 n\0"
.LC5:
	.ascii "n is the number of starting chars\0"
	.section	.text.startup,"x"
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$152, %rsp
	.seh_stackalloc	152
	.seh_endprologue
	movl	%ecx, %edi
	movq	%rdx, %rbx
	call	__main
	cmpl	$2, %edi
	jne	.L65
	movq	8(%rbx), %rcx
	call	atoi
	movl	%eax, n(%rip)
	jmp	.L66
.L65:
	leaq	.LC4(%rip), %rcx
	call	puts
	leaq	.LC5(%rip), %rcx
	call	puts
	movl	$2, n(%rip)
.L66:
	leaq	44(%rsp), %rdi
	movl	$25, %ecx
	xorl	%eax, %eax
	rep stosl
	leaq	44(%rsp), %rdi
	xorl	%ebx, %ebx
.L68:
	movl	$100, %edx
	movq	%rdi, %rcx
	call	get_word
	testl	%eax, %eax
	je	.L67
	cmpl	$2, %eax
	jne	.L68
	movq	%rbx, %rcx
	movq	%rdi, %rdx
	call	add_tree
	movq	%rax, %rbx
	jmp	.L68
.L67:
	xorl	%edx, %edx
	movq	%rbx, %rcx
	call	print_tree
	movq	%rbx, %rcx
	call	free_tree
	xorl	%eax, %eax
	addq	$152, %rsp
	popq	%rbx
	popq	%rdi
	ret
	.seh_endproc
	.comm	n, 4, 2
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	strcpy;	.scl	2;	.type	32;	.endef
	.def	strcmp;	.scl	2;	.type	32;	.endef
	.def	free;	.scl	2;	.type	32;	.endef
	.def	getchar;	.scl	2;	.type	32;	.endef
	.def	ungetc;	.scl	2;	.type	32;	.endef
	.def	atoi;	.scl	2;	.type	32;	.endef

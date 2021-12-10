	.cpu cortex-m4
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.section	.rodata
	.align	2
	.type	a, %object
	.size	a, 4
a:
	.word	7
	.data
	.align	2
	.type	z, %object
	.size	z, 4
z:
	.word	8
	.bss
	.align	2
sum:
	.space	4
	.size	sum, 4
	.text
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #16
	add	r7, sp, #8
	mov	r3, #-1442840576
	str	r3, [r7, #4]
	movs	r2, #7
	ldr	r3, [r7, #4]
	add	r2, r2, r3
	ldr	r3, .L2
	ldr	r3, [r3]
	add	r3, r3, r2
	ldr	r2, .L2+4
	str	r3, [r2]
	movs	r3, #12
	str	r3, [sp]
	movs	r3, #4
	movs	r2, #3
	movs	r1, #2
	movs	r0, #1
	bl	foo
	movs	r2, #7
	ldr	r3, .L2
	ldr	r3, [r3]
	add	r3, r3, r2
	adds	r3, r3, #3
	ldr	r2, .L2+4
	str	r3, [r2]
	nop
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L3:
	.align	2
.L2:
	.word	z
	.word	sum
	.size	main, .-main
	.align	1
	.global	foo
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	foo, %function
foo:
	@ args = 4, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #28
	add	r7, sp, #0
	str	r0, [r7, #12]
	str	r1, [r7, #8]
	str	r2, [r7, #4]
	str	r3, [r7]
	movs	r3, #4
	str	r3, [r7, #20]
	ldr	r3, .L5
	ldr	r3, [r3]
	adds	r3, r3, #1
	ldr	r2, .L5
	str	r3, [r2]
	ldr	r3, [r7, #12]
	adds	r3, r3, #1
	str	r3, [r7, #12]
	ldr	r3, [r7, #8]
	adds	r3, r3, #1
	str	r3, [r7, #8]
	ldr	r3, [r7, #4]
	adds	r3, r3, #1
	str	r3, [r7, #4]
	ldr	r3, [r7]
	adds	r3, r3, #1
	str	r3, [r7]
	ldr	r3, [r7, #32]
	adds	r3, r3, #2
	str	r3, [r7, #32]
	ldr	r3, [r7, #20]
	adds	r3, r3, #4
	str	r3, [r7, #20]
	nop
	adds	r7, r7, #28
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L6:
	.align	2
.L5:
	.word	z
	.size	foo, .-foo
	.ident	"GCC: (15:7-2018-q2-6) 7.3.1 20180622 (release) [ARM/embedded-7-branch revision 261907]"

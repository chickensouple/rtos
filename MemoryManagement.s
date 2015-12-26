	.syntax unified
	.cpu cortex-m4
	.eabi_attribute 27, 3
	.fpu fpv4-sp-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 4
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.thumb
	.file	"MemoryManagement.cpp"
	.section	.text._ZN16MemoryManagement6tallocEm,"ax",%progbits
	.align	1
	.global	_ZN16MemoryManagement6tallocEm
	.thumb
	.thumb_func
	.type	_ZN16MemoryManagement6tallocEm, %function
_ZN16MemoryManagement6tallocEm:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	ldr	r5, .L5
	ldr	r4, [r5, #0]
	cmp	r0, #15360
	add	r3, r4, r0
	bcs	.L3
	mov	r0, r3
	bl	_ZN7Utility9wordAlignEPh
	str	r0, [r5, #0]
	b	.L2
.L3:
	movs	r4, #0
.L2:
	mov	r0, r4
	pop	{r3, r4, r5, pc}
.L6:
	.align	2
.L5:
	.word	.LANCHOR0
	.size	_ZN16MemoryManagement6tallocEm, .-_ZN16MemoryManagement6tallocEm
	.section	.text._ZN16MemoryManagement7kmallocEm,"ax",%progbits
	.align	1
	.global	_ZN16MemoryManagement7kmallocEm
	.thumb
	.thumb_func
	.type	_ZN16MemoryManagement7kmallocEm, %function
_ZN16MemoryManagement7kmallocEm:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movs	r0, #0
	bx	lr
	.size	_ZN16MemoryManagement7kmallocEm, .-_ZN16MemoryManagement7kmallocEm
	.global	_ZN16MemoryManagement10kernelHeapE
	.global	_ZN16MemoryManagement19kernelTaskMemoryPtrE
	.global	_ZN16MemoryManagement16kernelTaskMemoryE
	.section	.bss._ZN16MemoryManagement16kernelTaskMemoryE,"aw",%nobits
	.type	_ZN16MemoryManagement16kernelTaskMemoryE, %object
	.size	_ZN16MemoryManagement16kernelTaskMemoryE, 15360
_ZN16MemoryManagement16kernelTaskMemoryE:
	.space	15360
	.section	.data._ZN16MemoryManagement19kernelTaskMemoryPtrE,"aw",%progbits
	.align	2
	.set	.LANCHOR0,. + 0
	.type	_ZN16MemoryManagement19kernelTaskMemoryPtrE, %object
	.size	_ZN16MemoryManagement19kernelTaskMemoryPtrE, 4
_ZN16MemoryManagement19kernelTaskMemoryPtrE:
	.word	_ZN16MemoryManagement16kernelTaskMemoryE
	.section	.bss._ZN16MemoryManagement10kernelHeapE,"aw",%nobits
	.type	_ZN16MemoryManagement10kernelHeapE, %object
	.size	_ZN16MemoryManagement10kernelHeapE, 5120
_ZN16MemoryManagement10kernelHeapE:
	.space	5120
	.ident	"GCC: (GNU Tools for ARM Embedded Processors) 4.7.4 20140401 (release) [ARM/embedded-4_7-branch revision 209195]"

	.global fpu_init
regz .field 0xE000ED88,32
fpu_init:
	push {r0, r1}
	LDR.W r0, regz
	LDR r1, [r0]
	ORR r1, r1, #(0xF << 20)
	STR r1, [r0]
	DSB
	ISB
	pop {r0, r1}
	mov pc, lr

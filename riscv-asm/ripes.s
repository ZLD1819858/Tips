

	li x0, 0x10101010
	li x1, 0x0000000F
	li x2, 0x0000000C
label:
	add x30, x1, x2
    c.j    label
    add x30, x1, x2



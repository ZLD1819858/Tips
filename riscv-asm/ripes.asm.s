.text
.global main_func
main_func:
	li x10, 0x10101010
    li a1, 0x18                # 加载立即数0x18到a1寄存器中
    lb a2, 0(a1)               # 加载a1+0地址处的字节到a2寄存器中
    sb a1, 0(a1)


    # bubble start
     lb a2, 0(a1)

    li a3, 0x11
lab2:
    lb a4, 10(a1)
    # bubble end
    
	li x12, 0x0000000F
	li x13, 0x0000000C
    li a3, 0x3
    li a4, 0xa
    add a5, a4, a3
    add a5, a5, a3
	add x30, x10, x11

    # write memory
    li a1, 0x18                # 加载立即数0x18到a1寄存器中
     lb a2, 0(a1)

    #jal lab1
    

    li a3, 0x11
    sb a3, 0(a1)
lab1:
    lb a4, 10(a1)
    lb a4, 10(a1)
        lb a4, 10(a1)
            lb a4, 10(a1)
    nop
    

lui $1, 0x1001
ori $4, $1, 0xa
addiu $2, $0, 0x4
syscall
addiu $2, $0, 0x5
syscall
addu $10, $0, $2
lui $1, 0x1001
ori $4, $1, 0x21
addiu $2, $0, 0x4
syscall
addiu $8, $0, 0x8
lui $1, 0x1001
ori $11, $1, 0x0
srl $1, $0, 0x1c
sll $10, $0, 0x4
or $10, $10, $1
andi $9, $10, 0xf
addi $1, $9, 0xffff
slti $1, $1, 0x9
bne $1, $0, 0x1
addi $9, $9, 0x7
addi $9, $9, 0x30
sb $9, 0x0($11)
addi $11, $11, 0x1
addi $8, $8, 0xffff
bne $8, $0, 0xfff3
lui $1, 0x1001
ori $4, $1, 0x0
addiu $2, $0, 0x4
syscall
addiu $2, $0, 0xa
syscall

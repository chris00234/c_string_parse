lui $1, 0x1001
ori $4, $1, 0x0
jal 0x10001a
addu $4, $0, $2
addiu $2, $0, 0x1
syscall
lui $1, 0x1001
ori $4, $1, 0x23
addiu $2, $0, 0x4
syscall
addiu $2, $0, 0xa
syscall
addiu $2, $0, 0x0
addi $1, $0, 0x61
beq $1, $4, 0x9
addi $1, $0, 0x65
beq $1, $4, 0x7
addi $1, $0, 0x69
beq $1, $4, 0x5
addi $1, $0, 0x6f
beq $1, $4, 0x3
addi $1, $0, 0x75
beq $1, $4, 0x1
jr $0
addiu $2, $0, 0x1
jr $0
addi $29, $29, 0xfff0
sw $4, 0x0($29)
sw $16, 0x4($29)
sw $17, 0x8($29)
sw $31, 0xc($29)
addiu $16, $0, 0x0
addu $17, $0, $4
lb $4, 0x0($17)
beq $4, $0, 0x4
jal 0x10000c
add $16, $16, $2
addi $17, $17, 0x1
UNKNOWN INST
addu $2, $0, $16
lw $4, 0x0($29)
lw $16, 0x4($29)
lw $17, 0x8($29)
lw $31, 0xc($29)
addi $29, $29, 0x10
jr $0

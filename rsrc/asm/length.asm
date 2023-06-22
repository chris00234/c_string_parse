lui $at, 0x1001
ori $t2, $at, 0x0
addiu $t1, $zero, 0x0
lb $t0, 0x0($t2)
beq $t0, $zero, 0x3
addi $t1, $t1, 0x1
addi $t2, $t2, 0x1
j 0x100003
lui $at, 0x1001
ori $a0, $at, 0xc
addiu $v0, $zero, 0x4
syscall
addu $a0, $zero, $t1
addiu $v0, $zero, 0x1
syscall
lui $at, 0x1001
ori $a0, $at, 0x17
addiu $v0, $zero, 0x4
syscall
addiu $v0, $zero, 0xa
syscall

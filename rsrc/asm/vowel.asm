lui $at, 0x1001
ori $a0, $at, 0x0
jal 0x10001a
addu $a0, $zero, $v0
addiu $v0, $zero, 0x1
syscall
lui $at, 0x1001
ori $a0, $at, 0x23
addiu $v0, $zero, 0x4
syscall
addiu $v0, $zero, 0xa
syscall
addiu $v0, $zero, 0x0
addi $at, $zero, 0x61
beq $at, $a0, 0x9
addi $at, $zero, 0x65
beq $at, $a0, 0x7
addi $at, $zero, 0x69
beq $at, $a0, 0x5
addi $at, $zero, 0x6f
beq $at, $a0, 0x3
addi $at, $zero, 0x75
beq $at, $a0, 0x1
jr $zero
addiu $v0, $zero, 0x1
jr $zero
addi $sp, $sp, 0xfff0
sw $a0, 0x0($sp)
sw $s0, 0x4($sp)
sw $s1, 0x8($sp)
sw $ra, 0xc($sp)
addiu $s0, $zero, 0x0
addu $s1, $zero, $a0
lb $a0, 0x0($s1)
beq $a0, $zero, 0x4
jal 0x10000c
add $s0, $s0, $v0
addi $s1, $s1, 0x1
UNKNOWN INST
addu $v0, $zero, $s0
lw $a0, 0x0($sp)
lw $s0, 0x4($sp)
lw $s1, 0x8($sp)
lw $ra, 0xc($sp)
addi $sp, $sp, 0x10
jr $zero

addiu $t0, $zero, 0x539
add $t0, $t1, $t2
addiu $t1, $zero, 0x2
sub $t3, $t4, $t5
add $t0, $zero, $t0
syscall
sub $t0, $t0, $zero
srl $t1, $zero, 0x1
beq $t1, $zero, 0x6
div $t0, $t1
mflo $t3
lui $at, 0x1001
ori $t4, $at, 0x0
lw $t4, 0x0($t4)
j 0x100000
addiu $v0, $zero, 0xa
syscall

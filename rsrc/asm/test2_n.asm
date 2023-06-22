addiu $8, $0, 0x539
add $8, $9, $10
addiu $9, $0, 0x2
sub $11, $12, $13
add $8, $0, $8
syscall
sub $8, $8, $0
srl $9, $0, 0x1
beq $9, $0, 0x6
div $8, $9
mflo $11
lui $1, 0x1001
ori $12, $1, 0x0
lw $12, 0x0($12)
j 0x100000
addiu $2, $0, 0xa
syscall

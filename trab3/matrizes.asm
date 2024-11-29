.data
mat1: .word 1 2 3
	    4 5 6
	    7 8 9

mat2: .word 11 12 13
	    14 15 16
	    17 18 19
	    
matr:  .word 0 0 0
	     0 0 0
	     0 0 0


nova_linha: .asciz "\n"
virgula: .asciz ", "


.text
la	a0, mat1
li	a1, 2
li	a2, 2
li	a3, 3
li	a4, 2

jal	ra, write_cel

li	a1, 3
li	a2, 3
jal	ra, imprime

la	a0, mat1
jal	ra, imprime

la	a0, mat2
jal	ra, imprime

la	a0, mat1
la	a1, mat2
la	a2, matr
li	a3, 3
li	a4, 3
jal	ra, soma


li	a7, 10
ecall

read_cel: # (matriz,lin,col,tamLinha):
		mul	t0, a1, a3 # t0 -> linha * tamLinha
		add	t0, t0, a2 # t0 -> linha * tamLinha + col
		slli	t0, t0, 2  # t0 *= 4
		add	a0, a0, t0 # a0 = &matriz + t0
		lw	a0, 0(a0)  # a0 = &a0
		
		jalr 	zero, 0(ra)
		
write_cel: # (matriz,lin,col,tamLinha,val)
		mul	t0, a1, a3 # t0 -> linha * tamLinha
		add	t0, t0, a2 # t0 -> linha * tamLinha + col
		slli	t0, t0, 2  # t0 *= 4
		add	t0, a0, t0 # a0 = &matriz + t0
		
		sw	a4, 0(t0)
		jalr	zero, 0(ra)
		
imprime: #(matriz,numLinhas,tamLinha)
# t0 = &matriz
# t1 = linha
# t2 = coluna
		add	t0, a0, zero
		add	t1, zero, zero # linha = 0
		
lb_linha:	beq	t1, a1, end_imprime
		
		add	t2, zero, zero # coluna = 0
		
		la	a0, nova_linha
		li	a7, 4
		ecall
		
		addi	t1, t1, 1
		
lb_col:		beq	t2, a2, lb_linha
		lw	a0, 0(t0)
		
		li	a7, 1
		ecall
		
		la	a0, virgula
		li	a7, 4
		ecall
		
		addi	t2, t2, 1
		addi	t0, t0, 4
		j	lb_col
		

end_imprime:	la	a0, nova_linha
		li	a7, 4
		ecall
		jalr	zero, 0(ra)
		
soma: #(m1,m2,mr,numLinhas,tamanhoLinha)
# a0 = &matriz1
# a1 = &matriz2
# a2 = &mr
# a3 = numLinhas
# a4 = tamanhoLinha

# t1 = linha
# t2 = coluna
# t3 = valor atual da matriz1
# t4 = valor atual da matriz2

		add	t1, zero, zero # linha = 0		
lb_soma_linha:	beq	t1, a3, end_soma
		
		add	t2, zero, zero # coluna = 0
		
		addi	t1, t1, 1
		
lb_soma_col:	beq	t2, a4, lb_soma_linha
		
		lw	t3, 0(a0)
		lw	t4, 0(a1)
		
		add	t5, t3, t4
		
		sw	t5, 0(a2)
		
		addi	t2, t2, 1
		addi	a0, a0, 4
		addi	a1, a1, 4
		addi 	a2, a2, 4
		j	lb_soma_col
		

end_soma:	jalr	zero, 0(ra)
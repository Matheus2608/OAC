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
bem_vindo: .asciz "Bem vindo ao Operador de Matrizes!!! \nAs matrizes 1 e 2 que vao ser operadas seguem abaixo, respectivamente.\n"
mudar_matriz: .asciz "\nCaso queira mudar alguma delas, altera diretamente no arquivo matrizes.asm\n\n"
qual_operacao: .asciz "Qual operação deseja realizar? \n\nDigite 1 para somar as matrizes \nDigite 2 para multiplicar as matrizes \nDigite 3 para obter a transposta da matriz resultante da última operação \n\n" 
resultado: .asciz "O resultado da operação é:\n"
bye_bye: .asciz "ByeBye!!!\n"


.text
		la	a0, bem_vindo
		li	a7, 4
		ecall
		
		la	a0, mat1
		li	a1, 3
		li	a2, 3
		jal	ra, imprime
		
		la	a0, mat2
		li	a1, 3
		li	a2, 3
		jal	ra, imprime
		
		la	a0, mudar_matriz
		ecall

		la	a0, qual_operacao
		ecall
		
		li	a7, 5
		ecall
		
		li	s0, 1
		beq 	a0, s0, prep_soma
		
		
		li	s0, 2
		beq 	a0, s0, prep_mult
		
		li	s0, 3
		beq 	a0, s0, prep_transposta
		

end:		la	a0, resultado
		li	a7, 4
		ecall
		
		la	a0, matr
		li	a1, 3
		li	a2, 3
		jal	ra, imprime
		
		la	a0, bye_bye
		li	a7, 4
		
		li	a7, 10
		ecall	
		
		
#(m1,m2,mr,numLinhas,tamanhoLinha)		
prep_soma:	la	a0, mat1
		la	a1, mat2
		la	a2, matr
		li	a3, 3
		li	a4, 3
		
		jal	ra, soma
		j	end

prep_mult:	la	a0, mat1
		la	a1, mat2
		la	a2, matr
		li	a3, 3
		li	a4, 3

		jal 	ra, mult
		j end
		

prep_transposta:la	a0, mat1
		la	a1, matr
		li	a2, 3
		li	a3, 3
		jal	ra, transposta
		j end
		
	
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
		
soma: 
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

mult:	
# a0 = &matriz1
# a1 = &matriz2
# a2 = &mr
# a3 = numLinhas (número de linhas da matriz 1)
# a4 = tamLinha (número de colunas da matriz 1 e número de linhas da matriz 2)

# t0 = linha da matriz1
# t1 = coluna da matriz2
# t2 = índice para somar os produtos
# t3 = elemento atual da matriz1
# t4 = elemento atual da matriz2
# t5 = produto parcial
# t6 = soma parcial

		add	t0, zero, zero    # t0 = linha da matriz1
lb_mult_linha:	beq	t0, a3, end_mult # Se todas as linhas da matriz1 foram processadas, termina
		add	t1, zero, zero    # t1 = coluna da matriz2
		
lb_mult_coluna:	beq	t1, a4, next_linha # Se todas as colunas da matriz2 foram processadas, próxima linha
		add	t6, zero, zero    # t6 = soma parcial (inicializa com 0)
		add	t2, zero, zero    # t2 = índice para multiplicação das células

lb_mult_soma:	beq	t2, a4, write_result # Se todos os produtos foram somados, escreve o resultado

		# Calcula endereço de matriz1[t0][t2]
		mul	t3, t0, a4        # t3 = linha * tamanhoLinha
		add	t3, t3, t2        # t3 = linha * tamanhoLinha + t2
		slli	t3, t3, 2        # t3 *= 4
		add	t3, a0, t3        # t3 = endereço de matriz1[t0][t2]
		lw	t3, 0(t3)          # t3 = matriz1[t0][t2]

		# Calcula endereço de matriz2[t2][t1]
		mul	t4, t2, a4        # t4 = t2 * tamanhoLinha
		add	t4, t4, t1        # t4 = t2 * tamanhoLinha + coluna
		slli	t4, t4, 2        # t4 *= 4
		add	t4, a1, t4        # t4 = endereço de matriz2[t2][t1]
		lw	t4, 0(t4)          # t4 = matriz2[t2][t1]

		# Calcula o produto e adiciona à soma parcial
		mul	t5, t3, t4        # t5 = matriz1[t0][t2] * matriz2[t2][t1]
		add	t6, t6, t5        # t6 += t5

		# Incrementa o índice
		addi	t2, t2, 1        # t2++
		j	lb_mult_soma      # Próximo produto

write_result:	# Escreve o resultado na matriz de resultado
		mul	t3, t0, a4        # t3 = linha * tamanhoLinha
		add	t3, t3, t1        # t3 = linha * tamanhoLinha + coluna
		slli	t3, t3, 2        # t3 *= 4
		add	t3, a2, t3        # t3 = endereço de resultado[t0][t1]
		sw	t6, 0(t3)          # resultado[t0][t1] = soma parcial

		# Incrementa a coluna
		addi	t1, t1, 1        # t1++
		j	lb_mult_coluna    # Próxima coluna

next_linha:	addi	t0, t0, 1        # t0++
		j	lb_mult_linha     # Próxima linha

end_mult:	jalr	zero, 0(ra)      # Retorna


transposta:	add t0, zero, zero    # t0 = i (índice da linha da matriz original)

loop_linha: 	beq t0, a2, end_transposta # Se i >= número de linhas, fim da transposição
		add t1, zero, zero    # t1 = j (índice da coluna da matriz original)

loop_coluna:	beq t1, a3, next_linha_mult # Se j >= tamanho da linha, vá para a próxima linha
		
		# Calcula o endereço do elemento [i][j] na matriz original
		mul t2, t0, a3        # t2 = i * tamanho da linha
		add t2, t2, t1        # t2 = i * tamanho da linha + j
		slli t2, t2, 2        # t2 *= 4 (cada elemento tem 4 bytes)
		add t2, a0, t2        # t2 = endereço de matriz[i][j]
		lw t3, 0(t2)          # t3 = matriz[i][j]

		# Calcula o endereço do elemento [j][i] na matriz transposta
		mul t4, t1, a2        # t4 = j * número de linhas
		add t4, t4, t0        # t4 = j * número de linhas + i
		slli t4, t4, 2        # t4 *= 4 (cada elemento tem 4 bytes)
		add t4, a1, t4        # t4 = endereço de transposta[j][i]
		sw t3, 0(t4)          # transposta[j][i] = matriz[i][j]

		# Incrementa o índice da coluna
		addi t1, t1, 1        # j++
		j loop_coluna         # Próxima coluna

next_linha_mult:addi t0, t0, 1        # i++
		j loop_linha          # Próxima linha

end_transposta:	jalr zero, 0(ra)      # Retorna
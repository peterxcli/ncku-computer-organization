.global conv2d
conv2d:
# a0: address of input
# a1: address of kernel
# a2: w
# a3: h
# a4: ksize
# a5: s

prologue:
    addi sp, sp, -20  # Allocate stack space for saved registers
    sw ra, 0(sp)      # Save return address
    sw s0, 4(sp)      # Save frame pointer
    sw s1, 8(sp)      # Save additional register s1
    sw s2, 12(sp)     # Save additional register s2
    sw s3, 16(sp)     # Save additional register s3
    addi s0, sp, 20   # Set frame pointer

    # Initialize registers for bounds of loops
    sub s1, a2, a4    # s1 = w - ksize
    sub s2, a3, a4    # s2 = h - ksize

    # Initialize outer loop counter (i)
    addi t0, zero, 0  # i = 0
outer_loop:
    # Calculate address of row start in input array
    mul t1, t0, a2    # t1 = i * w
    slli t1, t1, 2    # Convert to byte offset
    add t1, t1, a0    # t1 = address of input[i * w]

    # Initialize inner loop counter (j)
    addi t2, zero, 0  # j = 0
	inner_loop:
		li t3, 0          # sum = 0

		# Kernel application loops (over n and m)
		addi t4, zero, 0  # n = 0
		kernel_row_loop:
			addi t5, zero, 0  # m = 0
			kernel_col_loop:
					add t6, t0, t5    # t6 = i + m
					mul t6, t6, a2    # t6 = (i + m) * w
					add t6, t6, t2    # t6 = (i + m) * w + j
					add t6, t6, t4    # t6 = (i + m) * w + j + n
					slli t6, t6, 2    # Convert to byte offset
					add t6, a0, t6    # t6 = address of input[(i + m) * w + j + n]
					lw s3, 0(t6)      # Load input element

					mul s3, t5, a4    # Calculate kernel index (m * ksize)
					add s3, s3, t4    # Adjust for kernel row (n)
					slli s3, s3, 2    # Convert to byte offset
					add s3, a1, s3    # Address of kernel[m * ksize + n]
					lw s3, 0(s3)      # Load kernel element

					mul s3, s3, s3    # input * kernel
					add t3, t3, s3    # Accumulate in sum

					addi t5, t5, 1    # Increment m
					blt t5, a4, kernel_col_loop # Loop over m

			addi t4, t4, 1       # Increment n
			blt t4, a4, kernel_row_loop # Loop over n

			sw t3, 0(t1)          # Store result in input[i * w + j]

			addi t2, t2, 1        # Increment j
			addi t1, t1, 4        # Move to next output element
			ble t2, s1, inner_loop # Loop over j

		addi t0, t0, 1        # Increment i
		ble t0, s2, outer_loop # Loop over i

epilogue: # Restore registers and return
    lw ra, 0(sp)          # Restore return address
    lw s0, 4(sp)          # Restore frame pointer
    lw s1, 8(sp)          # Restore s1
    lw s2, 12(sp)         # Restore s2
    lw s3, 16(sp)         # Restore s3
    addi sp, sp, 20       # Deallocate stack space
    ret                   # Return from function

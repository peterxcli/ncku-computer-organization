.global conv2d
conv2d:
# a0: address of input
# a1: address of kernel
# a2: w
# a3: h
# a4: ksize
# a5: s

prologue:
    addi sp, sp, -4
    sw a0, 0(sp)

# Loop over output height (i)
    sub t0, a2, a4       # t0 = h - ksize
    sub t1, a3, a4       # t1 = w - ksize
    li  t2, 0            # i = 0
loop_output_height:
    li  t3, 0            # j = 0

    # Loop over output width (i)
    loop_output_width:
        li  t4, 0            # sum = 0
        li  t5, 0            # n = 0

        # Loop over kernel height (m)
        loop_kernel_height:
            li  t6, 0            # m = 0

            # Loop over kernel width (n)
            loop_kernel_width:
                # Calculate addresses and load values
                add a6, t2, t6       # a6 = i + m
                mul a6, a6, a2       # a6 = (i + m) * w
                add a6, a6, t3       # a6 = (i + m) * w + j
                add a6, a6, t5       # a6 = (i + m) * w + j + n
                slli a6, a6, 2       # a6 = ((i + m) * w + j + n) * 4
                add a6, a6, a0       # a6 = address of input[(i + m) * w + j + n]
                lw  a6, 0(a6)        # load input[(i + m) * w + j + n]

                mul a7, a4, t6       # a7 = m * ksize
                add a7, a7, t5       # a7 = m * ksize + n
                slli a7, a7, 2       # a7 = (m * ksize + n) * 4
                add a7, a7, a1       # a7 = address of kernel[m * ksize + n]
                lw  a7, 0(a7)        # load kernel[m * ksize + n]

                # Multiply and accumulate
                mul a6, a7, a6       # a6 = input[] * kernel[]
                add t4, t4, a6       # sum += input * kernel

                # Increment kernel width (n)
                add t6, t6, a5
                blt t6, a4, loop_kernel_width       # if n < ksize, repeat

            # Increment kernel height (m)
            add t5, t5, a5
            blt t5, a4, loop_kernel_height       # if m < ksize, repeat

        # Store the result in the input array
        mul a6, t2, a2       # a6 = i * w
        add a6, a6, t3       # a6 = i * w + j
        slli a6, a6, 2       # a6 = (i * w + j) * 4
        add a6, a0, a6       # a6 = address of input[i * w + j]
        sw  t4, 0(a6)        # input[i * w + j] = sum

        # Increment output width (j)
        addi t3, t3, 1
        ble t3, t1, loop_output_width       # if i < w - ksize, repeat

    # Increment output height (i)
    addi t2, t2, 1
    ble t2, t0, loop_output_height       # if i < h - ksize, repeat

epilogue:
    lw a0, 0(sp)
    addi sp, sp, 4
    ret

#include<stdio.h>
int main()
{ 
    int i = 0;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/4.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    
    int *p_x = &x[0];
    int *p_h = &h[0];
    int *p_y = &y[0];
    
    asm volatile(
        "li t3, 3\n" // int i = 3;
            "i_loop:\n"
                "li t4, 2\n" // int j = 2;
                "j_loop:\n"
                    "li t5, 3\n" // int k = 3;
                    "k_loop:\n"
                        "lw t0, 0(%0)\n" // Load x[2*k+j] into t0
                        "lw t1, 0(%1)\n" // Load h[i*3+k] into t1
                        "mul t2, t0, t1\n" // Multiply t0(x[2*k+j]) and t1(h[i*3+k]), store result in t2
                        "lw t6, 0(%2)\n" // Load the current value of y[i*2+j] into t6
                        "add t6, t6, t2\n" // Add t2 to t6
                        "sw t6, 0(%2)\n" // Store t6 back into y[i*2+j]
                        "addi t5, t5, -1\n" // k--
                        "addi %1, %1, 4\n" // p_h++
                        "addi %0, %0, 8\n" // p_x+=2
                        "bnez t5, k_loop\n" // if k != 0, jump to k_loop
                    "addi %1, %1, -12\n" // p_h-=3
                    "addi %0, %0, -20\n" // p_x-=5
                    "addi t4, t4, -1\n" // j--
                    "addi %2, %2, 4\n" // p_y++
                    "bnez t4, j_loop\n" // if j != 0, jump to j_loop
                "addi t3, t3, -1\n" // i--
                "addi %1, %1, 12\n" // p_h+=3
                "addi %0, %0, -8\n" // p_x-=2
                "bnez t3, i_loop\n" // if i != 0, jump to i_loop
        : // No outputs, everything done through memory
        : "r" (p_x), "r" (p_h), "r" (p_y)
        : "t0", "t1", "t2", "t3", "t4", "t5", "t6", "memory"
    );

    p_y = &y[0];
    for(i = 0; i < 6; i++)
        printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}

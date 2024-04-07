#include <stdio.h>

int main() {
    int a[10] = {0}, b[10] = {0}, c[10] = {0}; 
    int i, arr_size = 10;
    FILE *input = fopen("../input/2.txt", "r");
    for(i = 0; i < arr_size; i++) fscanf(input, "%d", &a[i]);
    for(i = 0; i < arr_size; i++) fscanf(input, "%d", &b[i]);
    for(i = 0; i < arr_size; i++) fscanf(input, "%d", &c[i]);
    fclose(input);
    int *p_a = &a[0];
    int *p_b = &b[0];
    int *p_c = &c[0];
    
    for (int i = 0; i < arr_size; i++) {
        asm volatile(
            "lw t0, 0(%1)\n"  // Load word from memory pointed to by p_a into t0
            "lw t1, 0(%2)\n"  // Load word from memory pointed to by p_b into t1
            "sub t2, t0, t1\n" // Subtract t1 from t0, store result in t2
            "sw t2, 0(%0)\n"  // Store word from t2 into memory pointed to by p_c
            "addi %0, %0, 4\n"// Increment p_c pointer
            "addi %1, %1, 4\n"// Increment p_a pointer
            "addi %2, %2, 4\n"// Increment p_b pointer
            : "+r" (p_c), "+r" (p_a), "+r" (p_b) // Output operands: pointers are updated
            : // No input operands
            : "t0", "t1", "t2", "memory" // Clobbers: registers t0, t1, t2 and memory
        );
    }
    
    p_c = &c[0];
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", *p_c++);
    }
    printf("\n");
    return 0;
}

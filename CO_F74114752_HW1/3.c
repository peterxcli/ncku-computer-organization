#include<stdio.h>
int main()
{ 
    int f, i, j;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/3.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    int *p_x = &x[0] ;
    int *p_h = &h[0] ;
    int *p_y = &y[0] ;
    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 2; j++){        	
            for (f = 0; f < 3; f++)
                // this version use array index directly
                // asm volatile(
                //     // matrix multiplication
                //     "mul t0, %1, %2\n" // t0 = x[i] * h[i*3+f]
                //     "add %0, %0, t0\n"
                //     : "+r" (y[i*2+j])
                //     : "r" (x[2*f+j]), "r" (h[i*3+f]) 
                //     : "t0"
                // );
                asm volatile(
                    "lw t1, 0(%1)\n" // Load x[f*2+j] into t1
                    "lw t2, 0(%2)\n" // Load h[i*3+f] into t2
                    "mul t3, t1, t2\n" // Multiply t1 and t2, store result in t3
                    "lw t0, 0(%0)\n" // Load the current value of y[i*2+j] into t0
                    "add t0, t0, t3\n" // Add t3 to t0
                    "sw t0, 0(%0)\n" // Store t0 back into y[i*2+j]
                    : // No outputs, everything done through memory
                    : "r" (p_y + i*2 + j), "r" (p_x + f*2 + j), "r" (p_h + i*3 + f)
                    : "t0", "t1", "t2", "t3", "memory"
                );
	    }
    }
    p_y = &y[0];
    for(i = 0; i < 6; i++)
    printf("%d ", *p_y++);
    printf("\n"); 
    return 0; 
 
}

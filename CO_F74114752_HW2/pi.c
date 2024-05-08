"li t1, 0;"  
"li t2, 1;" 

"addi %[lw_cnt], %[lw_cnt], 2;"

"loop:"
  "slli t3, t1, 1;" 
  "addi t3, t3, 1;" 

  "fcvt.d.w f1, t3;" 
  "fcvt.d.w f2, t2;"

  "fdiv.d f1, f2, f1;"
  "fadd.d %[pi], %[pi], f1;"

  "sub t2, zero, t2;"
  "addi t1, t1, 1;"

  "addi %[add_cnt], %[add_cnt], 3;"
  "addi %[sub_cnt], %[sub_cnt], 1;"
  "addi %[div_cnt], %[div_cnt], 1;"
  "addi %[others_cnt], %[others_cnt], 4;"

  "blt t1, %[N], loop;"

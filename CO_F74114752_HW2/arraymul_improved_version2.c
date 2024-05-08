"improved_loop:;"
  "vsetivli t0, 8, e16;"

  "vle16.v v1, (%[x]);"
  "vle16.v v2, (%[h]);"
  "vmul.vv v3, v1, v2;"
  "vadd.vx v3, v3, %[id];"
  "vse16.v v3, (%[y]);"

  "sub %[arr_size], %[arr_size], t0;"

  "slli t0, t0, 1;"
  "add %[x], %[x], t0;"
  "add %[h], %[h], t0;"
  "add %[y], %[y], t0;"

  "addi %[add_cnt], %[add_cnt], 4;"
  "addi %[sub_cnt], %[sub_cnt], 1;"
  "addi %[mul_cnt], %[mul_cnt], 1;"
  "addi %[lw_cnt], %[lw_cnt], 2;"
  "addi %[sw_cnt], %[sw_cnt], 1;"
  "addi %[others_cnt], %[others_cnt], 3;"

  "bnez %[arr_size], improved_loop;"

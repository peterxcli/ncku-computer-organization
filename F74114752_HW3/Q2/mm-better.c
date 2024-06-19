// 1: 0.5207417389790451
// 2:1.0570331685610188
// 3:1.2842224039790013
// 4: 1.5021693627890609
// 5: 1.5982859002020617
// 6: 1.7014920666084594
// 7: 1.7278000434834562
// 8: 1.8028832665212113
// 9: 1.7919090736218644
// 10: 1.84911471048118
// 11: 1.7842511046585148
// 12: 1.7735885017084267
// 13: 1.6510909543763417
// 14: 1.6204082830200242
// 15: 1.5868228860116294
// 16: 1.5618883754180133
// 17: 1.4877620312702484
// 20: 1.4868997967109583
// 32: 1.2057418542534164

// https://hackmd.io/@shaoeChen/BJH0QuJQI#Block-Multiplication1
void matrix_multiplication(int *a, int *b, int *output, int i, int k, int j) {
    int block_size = 10;

    for (int x = 0; x < i; x += block_size) {
        for (int y = 0; y < j; y += block_size) {
            for (int z = 0; z < k; z += block_size) {
                // Process the block
                for (int xx = x; xx < x + block_size && xx < i; xx++) {
                    for (int yy = y; yy < y + block_size && yy < j; yy++) {
                        int sum = 0;
                        for (int zz = z; zz < z + block_size && zz < k; zz++) {
                            sum += a[xx * k + zz] * b[zz * j + yy];
                        }
                        output[xx * j + yy] += sum;
                    }
                }
            }
        }
    }
}

#ifndef CPUSTRESS_AVX_H
#define CPUSTRESS_AVX_H

#define AVX512_INPUT_SIZE 16
#define AVX512_OUTPUT_SIZE 8

#define AVX256_INPUT_SIZE 8
#define AVX256_OUTPUT_SIZE 4

#define AVX128_INPUT_SIZE 4
#define AVX128_OUTPUT_SIZE 2

bool copy_result(const int &, const double *, double *);

#endif //CPUSTRESS_AVX_H

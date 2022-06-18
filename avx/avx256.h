#ifndef CPUSTRESSER_AVX256_H
#define CPUSTRESSER_AVX256_H

#define AVX256_BUFFER_INPUT_SIZE 8
#define AVX256_BUFFER_RESULT_SIZE 4

void avx256_add_double(double *input, double *result);

void avx256_div_double(double *input, double *result);

#endif //CPUSTRESSER_AVX256_H

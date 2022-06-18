#ifndef CPUSTRESSER_AVX512_H
#define CPUSTRESSER_AVX512_H

#define AVX512_BUFFER_INPUT_SIZE 16
#define AVX512_BUFFER_RESULT_SIZE 8

void avx512_add_double(double *input, double *result);

void avx512_div_double(double *input, double *result);

#endif //CPUSTRESSER_AVX512_H

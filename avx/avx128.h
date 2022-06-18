#ifndef CPUSTRESSER_AVX128_H
#define CPUSTRESSER_AVX128_H

#define AVX128_BUFFER_INPUT_SIZE 4
#define AVX128_BUFFER_RESULT_SIZE 2

void avx128_add_double(double *, double *);

void avx128_div_double(double *, double *);

#endif //CPUSTRESSER_AVX128_H

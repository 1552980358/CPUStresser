#include "avx128.h"

#include <immintrin.h>

void avx128_add_double(double *input, double *result) {
    __m128d avx128_result = _mm_add_pd(
            _mm_set_pd(input[0], input[1]),
            _mm_set_pd(input[2], input[3])
            );
    auto *avx128_double_result = (double *) &avx128_result;
    result[0] = avx128_double_result[0];
    result[1] = avx128_double_result[1];
}

void avx128_div_double(double *input, double *result) {
    __m128d avx128_result = _mm_div_pd(
            _mm_set_pd(input[0], input[1]),
            _mm_set_pd(input[2], input[3])
    );
    auto *avx128_double_result = (double *) &avx128_result;
    result[0] = avx128_double_result[0];
    result[1] = avx128_double_result[1];
}
#include <intrin.h>

#include "avx.h"
#include "avx256.h"

bool avx256_add(const double *input, double *output) {
    __m256d result_m256;
    try {
        result_m256 = _mm256_add_pd(
                _mm256_set_pd(*(input + 0), *(input + 1), *(input + 2), *(input + 3)),
                _mm256_set_pd(*(input + 4), *(input + 5), *(input + 6), *(input + 7))
                );
    } catch (...) {
        return false;
    }
    return copy_result(AVX256_OUTPUT_SIZE, (double *) &result_m256, output);
}

bool avx256_div(const double *input, double *output) {
    __m256d result_m256;
    try {
        result_m256 = _mm256_div_pd(
                _mm256_set_pd(*(input + 0), *(input + 1), *(input + 2), *(input + 3)),
                _mm256_set_pd(*(input + 4), *(input + 5), *(input + 6), *(input + 7))
        );
    } catch (...) {
        return false;
    }
    return copy_result(AVX256_OUTPUT_SIZE, (double *) &result_m256, output);
}
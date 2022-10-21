#include <intrin.h>

#include "avx.h"
#include "avx256.h"

bool avx256_add(const double *summand, const double *addend, double *output) {
    __m256d result_m256;
    try {
        result_m256 = _mm256_add_pd(
                _mm256_set_pd(*(summand + 0), *(summand + 1), *(summand + 2), *(summand + 3)),
                _mm256_set_pd(*(addend + 0), *(addend + 1), *(addend + 2), *(addend + 3))
                );
    } catch (...) {
        return false;
    }
    return copy_result(AVX256_OUTPUT_SIZE, (double *) &result_m256, output);
}

bool avx256_div(const double *dividend, const double *divisor, double *output) {
    __m256d result_m256;
    try {
        result_m256 = _mm256_div_pd(
                _mm256_set_pd(*(dividend + 0), *(dividend + 1), *(dividend + 2), *(dividend + 3)),
                _mm256_set_pd(*(divisor + 0), *(divisor + 1), *(divisor + 2), *(divisor + 3))
                );
    } catch (...) {
        return false;
    }
    return copy_result(AVX256_OUTPUT_SIZE, (double *) &result_m256, output);
}
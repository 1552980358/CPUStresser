#include <intrin.h>

#include "avx.h"
#include "avx128.h"

bool avx128_add(const double *summand, const double *addend, double *output) {
    __m128d result_m128;
    try {
        result_m128 = _mm_add_pd(
                _mm_set_pd(*(summand + 0), *(summand + 1)),
                _mm_set_pd(*(addend + 0), *(addend + 1))
                );
    } catch (...) {
        return false;
    }
    return copy_result(AVX128_OUTPUT_SIZE, (double *) &result_m128, output);
}

bool avx128_div(const double *dividend, const double *divisor, double *output) {
    __m128d result_m128;
    try {
        result_m128 = _mm_div_pd(
                _mm_set_pd(*(dividend + 0), *(dividend + 1)),
                _mm_set_pd(*(divisor + 0), *(divisor + 1))
                );
    } catch (...) {
        return false;
    }
    return copy_result(AVX128_OUTPUT_SIZE, (double *) &result_m128, output);
}
#include <intrin.h>

#include "avx.h"
#include "avx128.h"

bool avx128_add(const double *input, double *output) {
    __m128d result_m128;
    try {
        result_m128 = _mm_add_pd(
                _mm_set_pd(*(input + 0), *(input + 1)),
                _mm_set_pd(*(input + 2), *(input + 3))
        );
    } catch (...) {
        return false;
    }
    return copy_result(AVX128_OUTPUT_SIZE, (double *) &result_m128, output);
}

bool avx128_div(const double *input, double *output) {
    __m128d result_m128;
    try {
        result_m128 = _mm_div_pd(
                _mm_set_pd(*(input + 0), *(input + 1)),
                _mm_set_pd(*(input + 2), *(input + 3))
        );
    } catch (...) {
        return false;
    }
    return copy_result(AVX128_OUTPUT_SIZE, (double *) &result_m128, output);
}
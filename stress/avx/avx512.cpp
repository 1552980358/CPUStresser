#include <intrin.h>

#include "avx.h"
#include "avx512.h"

bool avx512_add(const double *input, double *output) {
    __m512d result_m512;
    try {
        result_m512 = _mm512_add_pd(
                _mm512_set_pd(
                        *(input + 0), *(input + 1), *(input + 2), *(input + 3),
                        *(input + 4), *(input + 5), *(input + 6), *(input + 7)
                ),
                _mm512_set_pd(
                        *(input + 8), *(input + 9), *(input + 10), *(input + 11),
                        *(input + 12), *(input + 13), *(input + 14), *(input + 15)
                )
        );
    } catch (...) {
        return false;
    }
    return copy_result(AVX256_OUTPUT_SIZE, (double *) &result_m512, output);
}

bool avx512_div(const double *input, double *output) {
    __m512d result_m512;
    try {
        result_m512 = _mm512_div_pd(
                _mm512_set_pd(
                        *(input + 0), *(input + 1), *(input + 2), *(input + 3),
                        *(input + 4), *(input + 5), *(input + 6), *(input + 7)
                ),
                _mm512_set_pd(
                        *(input + 8), *(input + 9), *(input + 10), *(input + 11),
                        *(input + 12), *(input + 13), *(input + 14), *(input + 15)
                )
        );
    } catch (...) {
        return false;
    }
    return copy_result(AVX512_OUTPUT_SIZE, (double *) &result_m512, output);
}
#include <intrin.h>

#include "avx.h"
#include "avx512.h"

bool avx512_add(const double *summand, const double *addend, double *output) {
    __m512d result_m512;
    try {
        result_m512 = _mm512_add_pd(
                _mm512_set_pd(
                        *(summand + 0), *(summand + 1), *(summand + 2), *(summand + 3),
                        *(summand + 4), *(summand + 5), *(summand + 6), *(summand + 7)
                        ),
                _mm512_set_pd(
                        *(addend + 0), *(addend + 1), *(addend + 2), *(addend + 3),
                        *(addend + 4), *(addend + 5), *(addend + 6), *(addend + 7)
                        )
        );
    } catch (...) {
        return false;
    }
    return copy_result(AVX256_OUTPUT_SIZE, (double *) &result_m512, output);
}

bool avx512_div(const double *dividend, const double *divisor, double *output) {
    __m512d result_m512;
    try {
        result_m512 = _mm512_div_pd(
                _mm512_set_pd(
                        *(dividend + 0), *(dividend + 1), *(dividend + 2), *(dividend + 3),
                        *(dividend + 4), *(dividend + 5), *(dividend + 6), *(dividend + 7)
                        ),
                _mm512_set_pd(
                        *(divisor + 0), *(divisor + 1), *(divisor + 2), *(divisor + 3),
                        *(divisor + 4), *(divisor + 5), *(divisor + 6), *(divisor + 7)
                        )
        );
    } catch (...) {
        return false;
    }
    return copy_result(AVX512_OUTPUT_SIZE, (double *) &result_m512, output);
}
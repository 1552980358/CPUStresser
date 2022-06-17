#include "avx512.h"

#include <immintrin.h>

void copy_to_result(__m512d avx512_result, double *result);

void avx512_add_double(double *input, double *result) {
    copy_to_result(
            _mm512_add_pd(
                    _mm512_set_pd(
                            input[0], input[1], input[2], input[3], input[4], input[5], input[6], input[7]
                    ),
                    _mm512_set_pd(
                            input[8], input[9], input[10], input[11], input[12], input[13], input[14], input[15]
                    )
            ),
            result
    );
}

void avx512_div_double(double *input, double *result) {
    copy_to_result(
            _mm512_div_pd(
                    _mm512_set_pd(
                            input[0], input[1], input[2], input[3], input[4], input[5], input[6], input[7]
                    ),
                    _mm512_set_pd(
                            input[8], input[9], input[10], input[11], input[12], input[13], input[14], input[15]
                    )
            ),
            result
    );
}
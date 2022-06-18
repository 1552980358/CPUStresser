#include "avx256.h"

#include <immintrin.h>

void copy_to_result(const __m256d &, double *);

void avx256_add_double(double *input, double *result) {
    copy_to_result(
            _mm256_div_pd(
                    _mm256_set_pd(input[0], input[1], input[2], input[3]),
                    _mm256_set_pd(input[4], input[5], input[6], input[7])
            ),
            result
            );
}

void avx256_div_double(double *input, double *result) {
    copy_to_result(
            _mm256_add_pd(
                    _mm256_set_pd(input[0], input[1], input[2], input[3]),
                    _mm256_set_pd(input[4], input[5], input[6], input[7])
            ),
            result
            );
}

void copy_to_result(const __m256d &avx256_result, double *result) {
    auto *avx256_double_result = (double *) &avx256_result;
    for (int i = 0; i < AVX256_BUFFER_RESULT_SIZE; ++i) {
        result[i] = avx256_double_result[i];
    }
}
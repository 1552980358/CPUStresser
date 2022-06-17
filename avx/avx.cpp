#include "avx.h"
#include "avx128.h"
#include "avx256.h"
#include "avx512.h"

void copy_result_to_input(double *, const double *, const int &);

double avx512_pi_mix(double *buffer_input, double *buffer_result, int64_t &num) {
    for (int i = 0; i < 8; ++i) {
        buffer_input[i] = (i % 2) ? -4 : 4;
        buffer_result[i + 8] = (double) (num += 2);
    }

    avx512_div_double(buffer_input, buffer_result);

    copy_result_to_input(buffer_input, buffer_result, 8);
    avx256_add_double(buffer_input, buffer_result);

    copy_result_to_input(buffer_input, buffer_result, 4);
    avx128_add_double(buffer_input, buffer_result);

    return buffer_result[0] + buffer_result[1];
}

double avx256_pi_mix(double *buffer_input, double *buffer_result, int64_t &num) {
    for (int i = 0; i < 4; ++i) {
        buffer_input[i] = (i % 2) ? -4 : 4;
        buffer_result[i + 4] = (double) (num += 2);
    }

    avx256_div_double(buffer_input, buffer_result);

    copy_result_to_input(buffer_input, buffer_result, 4);
    avx128_add_double(buffer_input, buffer_result);

    return buffer_result[0] + buffer_result[1];
}

void copy_result_to_input(double *buffer_input, const double *buffer_result, const int &result_size) {
    for (int i = 0; i < 8; ++i) {
        buffer_input[i] = buffer_result[i];
    }
}
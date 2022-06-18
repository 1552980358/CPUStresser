#include "cpu_stress.h"
#include "avx.h"

void stress_mode_avx1(int64_t *num, double *pi, double *buffer_input, double *buffer_result) {
    *pi += avx128_pi_mix(buffer_input, buffer_result, *num);
}

void stress_mode_avx2(int64_t *num, double *pi, double *buffer_input, double *buffer_result) {
    *pi += avx256_pi_mix(buffer_input, buffer_result, *num);
}

void stress_mode_avx512f(int64_t *num, double *pi, double *buffer_input, double *buffer_result) {
    *pi += avx512_pi_mix(buffer_input, buffer_result, *num);
}
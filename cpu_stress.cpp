#include "cpu_stress.h"
#include "avx.h"

using std::cout;
using std::endl;

void show_mode(const int &mode) {
    cout << "Stress Mode #" << mode << ": ";
    switch (mode) {
        case STRESS_MODE_FPU:
            cout << "FPU stress" << endl;
            break;
        case STRESS_MODE_AVX1_MIX:
            cout << "AVX1 + FPU mix mode stress" << endl;
            break;
        case STRESS_MODE_AVX2_MIX:
            cout << "AVX2 + AVX1 + FPU mix mode stress" << endl;
            break;
        case STRESS_MODE_AVX512F_MIX:
            cout << "AVX512F + AVX2 + AVX1 + FPU mix mode stress" << endl;
            break;
        case STRESS_MODE_AVX1_PURE:
            cout << "AVX1 + FPU pure mode stress" << endl;
            break;
        case STRESS_MODE_AVX2_PURE:
            cout << "AVX2 + FPU pure mode stress" << endl;
            break;
        case STRESS_MODE_AVX512F_PURE:
            cout << "AVX512F + FPU pure mode stress" << endl;
            break;
        default:
            cout << "********UNKNOWN********" << endl;
            break;
    }
}

void stress_mode_fpu(int64_t *num, double *pi, double *, double *) {
    *pi += 4 / (double) (*num += 2);
    *pi -= 4 / (double) (*num += 2);
}

void stress_mode_avx1_mix(int64_t *num, double *pi, double *buffer_input, double *buffer_result) {
    *pi += avx128_pi_mix(buffer_input, buffer_result, *num);
}

void stress_mode_avx2_mix(int64_t *num, double *pi, double *buffer_input, double *buffer_result) {
    *pi += avx256_pi_mix(buffer_input, buffer_result, *num);
}

void stress_mode_avx512f_mix(int64_t *num, double *pi, double *buffer_input, double *buffer_result) {
    *pi += avx512_pi_mix(buffer_input, buffer_result, *num);
}

void stress_mode_avx1_pure(int64_t *num, double *pi, double *buffer_input, double *buffer_result) {
    *pi += avx128_pi_pure(buffer_input, buffer_result, *num);
}

void stress_mode_avx2_pure(int64_t *num, double *pi, double *buffer_input, double *buffer_result) {
    *pi += avx256_pi_pure(buffer_input, buffer_result, *num);
}

void stress_mode_avx512f_pure(int64_t *num, double *pi, double *buffer_input, double *buffer_result) {
    *pi += avx512_pi_pure(buffer_input, buffer_result, *num);
}
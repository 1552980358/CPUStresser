#ifndef CPUSTRESSER_CPU_STRESS_H
#define CPUSTRESSER_CPU_STRESS_H

#include <iostream>

#define STRESS_MODE_FPU         0
#define STRESS_MODE_AVX1_MIX    1
#define STRESS_MODE_AVX2_MIX    2
#define STRESS_MODE_AVX512F_MIX 3
#define STRESS_MODE_AVX1_PURE   4
#define STRESS_MODE_AVX2_PURE   5
#define STRESS_MODE_AVX512F_PURE 6

void show_mode(const int &);

void stress_mode_fpu(int64_t *, double *, double *, double *);

void stress_mode_avx1_mix(int64_t *num, double *pi, double *buffer_input, double *buffer_result);

void stress_mode_avx2_mix(int64_t *num, double *pi, double *buffer_input, double *buffer_result);

void stress_mode_avx512f_mix(int64_t *num, double *pi, double *buffer_input, double *buffer_result);

void stress_mode_avx1_pure(int64_t *num, double *pi, double *buffer_input, double *buffer_result);

void stress_mode_avx2_pure(int64_t *num, double *pi, double *buffer_input, double *buffer_result);

void stress_mode_avx512f_pure(int64_t *num, double *pi, double *buffer_input, double *buffer_result);

#endif //CPUSTRESSER_CPU_STRESS_H

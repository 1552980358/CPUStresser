#ifndef CPUSTRESSER_CPU_STRESS_H
#define CPUSTRESSER_CPU_STRESS_H

#include <iostream>

#define STRESS_MODE_FPU 0
#define STRESS_MODE_AVX1 1
#define STRESS_MODE_AVX2 2
#define STRESS_MODE_AVX512F 3

void stress_mode_avx1(int64_t *, double *, double *, double *);

void stress_mode_avx2(int64_t *, double *, double *, double *);

void stress_mode_avx512f(int64_t *, double *, double *, double *);

#endif //CPUSTRESSER_CPU_STRESS_H

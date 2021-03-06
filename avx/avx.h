#ifndef CPUSTRESSER_AVX_H
#define CPUSTRESSER_AVX_H

#include <iostream>

double avx512_pi_mix(double *, double *, int64_t &);

double avx256_pi_mix(double *, double *, int64_t &);

double avx128_pi_mix(double *, double *, int64_t &);

double avx512_pi_pure(double *, double *, int64_t &);

double avx256_pi_pure(double *, double *, int64_t &);

double avx128_pi_pure(double *, double *, int64_t &);

#endif //CPUSTRESSER_AVX_H

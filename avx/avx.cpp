#include "avx.h"
#include "avx128.h"
#include "avx256.h"
#include "avx512.h"

void assign_input(double *, int64_t &, const int &);

void copy_result_to_input(double *, const double *, const int &);

double double_add_result(const double *, const int & = 2);

double avx512_pi_mix(double *buffer_input, double *buffer_result, int64_t &num) {
    assign_input(buffer_input, num, 8);

    avx512_div_double(buffer_input, buffer_result);

    copy_result_to_input(buffer_input, buffer_result, 8);
    avx256_add_double(buffer_input, buffer_result);

    copy_result_to_input(buffer_input, buffer_result, 4);
    avx128_add_double(buffer_input, buffer_result);

    return double_add_result(buffer_result);
}

double avx256_pi_mix(double *buffer_input, double *buffer_result, int64_t &num) {
    assign_input(buffer_input, num, 4);

    avx256_div_double(buffer_input, buffer_result);

    copy_result_to_input(buffer_input, buffer_result, 4);
    avx128_add_double(buffer_input, buffer_result);

    return double_add_result(buffer_result);
}

double avx128_pi_mix(double *buffer_input, double *buffer_result, int64_t &num) {
    assign_input(buffer_input, num, 2);

    avx128_div_double(buffer_input, buffer_result);

    return double_add_result(buffer_result);
}

double avx512_pi_pure(double *buffer_input, double *buffer_result, int64_t &num) {
    assign_input(buffer_input, num, AVX512_BUFFER_RESULT_SIZE);
    assign_input(buffer_input + AVX512_BUFFER_INPUT_SIZE, num, AVX512_BUFFER_RESULT_SIZE);

    avx512_div_double(buffer_input, buffer_result);
    avx512_div_double(buffer_input + AVX512_BUFFER_INPUT_SIZE, buffer_result + AVX512_BUFFER_RESULT_SIZE);

    copy_result_to_input(buffer_input, buffer_result, AVX512_BUFFER_INPUT_SIZE);
    avx512_add_double(buffer_input, buffer_result);

    return double_add_result(buffer_result, AVX512_BUFFER_RESULT_SIZE);
}

double avx256_pi_pure(double *buffer_input, double *buffer_result, int64_t &num) {
    assign_input(buffer_input, num, AVX256_BUFFER_RESULT_SIZE);
    assign_input(buffer_input + AVX256_BUFFER_INPUT_SIZE, num, AVX256_BUFFER_RESULT_SIZE);

    avx256_div_double(buffer_input, buffer_result);
    avx256_div_double(buffer_input + AVX256_BUFFER_INPUT_SIZE, buffer_result + AVX256_BUFFER_RESULT_SIZE);

    copy_result_to_input(buffer_input, buffer_result, AVX256_BUFFER_INPUT_SIZE);
    avx256_add_double(buffer_input, buffer_result);

    return double_add_result(buffer_result, AVX256_BUFFER_RESULT_SIZE);
}

double avx128_pi_pure(double *buffer_input, double *buffer_result, int64_t &num) {
    assign_input(buffer_input, num, AVX128_BUFFER_RESULT_SIZE);
    assign_input(buffer_input + AVX128_BUFFER_INPUT_SIZE, num, AVX128_BUFFER_RESULT_SIZE);

    avx128_div_double(buffer_input, buffer_result);
    avx128_div_double(buffer_input + AVX128_BUFFER_INPUT_SIZE, buffer_result + AVX128_BUFFER_RESULT_SIZE);

    copy_result_to_input(buffer_input, buffer_result, AVX128_BUFFER_INPUT_SIZE);
    avx128_add_double(buffer_input, buffer_result);

    return double_add_result(buffer_result);
}

void assign_input(double *buffer_input, int64_t &num, const int &repeat) {
    for (int i = 0; i < repeat; ++i) {
        buffer_input[i] = (i % 2) ? -4 : 4;
        buffer_input[i + repeat] = (double) (num += 2);
    }
}

void copy_result_to_input(double *buffer_input, const double *buffer_result, const int &result_size) {
    for (int i = 0; i < result_size; ++i) {
        buffer_input[i] = buffer_result[i];
    }
}

double double_add_result(const double *buffer_result, const int &repeat) {
    if (repeat == 2) {
        return buffer_result[0] + buffer_result[1];
    }
    double sum = 0;
    for (int i = 0; i < repeat; ++i) {
        sum += buffer_result[i];
    }
    return sum;
}
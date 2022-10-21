#include <iostream>

#include "stress_pi.h"
#include "avx.h"
#include "avx128.h"

#define STRESS_PI_COUNT_DIFF 2

bool allocate_mem(double **, const int &);
long count_check(long &);

bool stress_pi_avx128(long &, long double &, double *);

stress_pi_method_t get_stress_pi_method(instruction_set_t *instruction_set, bool enable_avx, double **memory_ptr) {

    if (enable_avx) {

        if (support_avx512(instruction_set)) {
            allocate_mem(memory_ptr, AVX512_INPUT_SIZE + AVX512_OUTPUT_SIZE);
            return nullptr;
        }

        if (support_avx256(instruction_set)) {
            allocate_mem(memory_ptr, AVX256_INPUT_SIZE + AVX256_OUTPUT_SIZE);
            return nullptr;
        }

        if (support_avx128(instruction_set)) {
            allocate_mem(memory_ptr, AVX128_INPUT_SIZE + AVX128_OUTPUT_SIZE);
            return stress_pi_avx128;
        }

    }

    return nullptr;
}

bool stress_pi_avx128(long &count, long double &result, double *memory_ptr) {

    if (count_check(count)) {
        count = -1;
        result = 0;
    }

    for (int i = 0; i < AVX128_INPUT_LOOP_COUNT; ++i) {
        *(memory_ptr + i) = 4 * (i % 2 ? -1 : 1);
        *(memory_ptr + AVX128_INPUT_DIVIDEND_SIZE + i) = count + STRESS_PI_COUNT_DIFF;
    }

    if (!avx128_div(memory_ptr, memory_ptr + AVX128_INPUT_DIVIDEND_SIZE, memory_ptr + AVX128_INPUT_SIZE)
        || !avx128_div(memory_ptr + AVX128_INPUT_DIVIDEND_OFFSET,
                      memory_ptr + AVX128_INPUT_DIVIDEND_SIZE + AVX128_INPUT_DIVISOR_OFFSET,
                      memory_ptr + AVX128_INPUT_SIZE + AVX128_OUTPUT_OFFSET)) {
        count -= AVX128_INPUT_LOOP_COUNT * STRESS_PI_COUNT_DIFF;
        return false;
    }

    for (int i = 0; i < AVX128_OUTPUT_SIZE; ++i) {
        *(memory_ptr + i) = *(memory_ptr + AVX128_INPUT_SIZE);
    }

    if (avx128_add(memory_ptr, memory_ptr + AVX128_OUTPUT_SIZE / 2, memory_ptr + AVX128_INPUT_SIZE)) {
        count -= AVX128_INPUT_LOOP_COUNT * STRESS_PI_COUNT_DIFF;
        return false;
    }

    for (int i = 0; i < AVX128_OUTPUT_SIZE; ++i) {
        result += *(memory_ptr + AVX128_INPUT_SIZE + i);
    }

    return true;
}

bool allocate_mem(double **memory_ptr, const int &size) {
    *memory_ptr = (double *) malloc(size);
    return *memory_ptr;
}

long count_check(long &count) {
    return count == LONG_MAX
           || count + STRESS_PI_COUNT_DIFF == LONG_MAX
           || count + STRESS_PI_COUNT_DIFF * 2 == LONG_MAX
           || count + STRESS_PI_COUNT_DIFF * 3 == LONG_MAX
           || count + STRESS_PI_COUNT_DIFF * 4 == LONG_MAX;
}
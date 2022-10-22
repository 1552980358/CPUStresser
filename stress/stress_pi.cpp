#include <iostream>

#include "stress_pi.h"
#include "avx.h"
#include "avx128.h"

#define STRESS_PI_DEFAULT_COUNT -1
#define STRESS_PI_DEFAULT_RESULT 0
#define STRESS_PI_COUNT_DIFF 2

bool allocate_mem(double **, const int &);
long get_signed_count(const long &);
long count_check(long &);

bool stress_pi_avx128(long &, long double &, double *);
bool stress_pi_fpu(long &, long double &, double *);

void reset_stress_pi_variables(long &count, long double &result) {
    count = STRESS_PI_DEFAULT_COUNT;
    result = STRESS_PI_DEFAULT_RESULT;
}

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

    return stress_pi_fpu;
}

bool stress_pi_avx128(long &count, long double &result, double *memory_ptr) {

    if (count_check(count)) {
        reset_stress_pi_variables(count, result);
    }

    for (int i = 0; i < AVX128_INPUT_LOOP_COUNT; ++i) {
        *(memory_ptr + i) = 4 * (i % 2 ? -1 : 1);
        *(memory_ptr + AVX128_INPUT_DIVIDEND_SIZE + i) = count += STRESS_PI_COUNT_DIFF;
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

    for (int i = 0; i < AVX128_OUTPUT_FINAL; ++i) {
        result += *(memory_ptr + AVX128_INPUT_SIZE + i);
    }

    return true;
}

bool stress_pi_fpu(long &count, long double &result, double *) {
    if (count == LONG_MAX) {
        reset_stress_pi_variables(count, result);
    }
    count += STRESS_PI_COUNT_DIFF;
    result += 4.0 / get_signed_count(count);
    return true;
}

bool allocate_mem(double **memory_ptr, const int &size) {
    *memory_ptr = (double *) malloc(size);
    return *memory_ptr;
}

inline long get_signed_count(const long &count) {
    if (((count + 1) / 2) % 2) {
        return count;
    }
    return -count;
}

long count_check(long &count) {
    return count == LONG_MAX
           || count + STRESS_PI_COUNT_DIFF == LONG_MAX
           || count + STRESS_PI_COUNT_DIFF * 2 == LONG_MAX
           || count + STRESS_PI_COUNT_DIFF * 3 == LONG_MAX
           || count + STRESS_PI_COUNT_DIFF * 4 == LONG_MAX;
}
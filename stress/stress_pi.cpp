#include <iostream>

#include "stress_pi.h"
#include "avx.h"
#include "avx128.h"
#include "avx256.h"
#include "avx512.h"

#define STRESS_PI_DEFAULT_COUNT (-1)
#define STRESS_PI_DEFAULT_RESULT 0
#define STRESS_PI_COUNT_DIFF 2
#define STRESS_PI_DIVIDEND 4.0
#define STRESS_PI_DIVIDEND_NEG (-4.0)
#define STRESS_PI_DIV_REPEAT 2

bool allocate_mem(double **, const int &);
double get_signed_dividend(const int &i);

void reset_stress_pi_variables(long &count, long double &result) {
    count = STRESS_PI_DEFAULT_COUNT;
    result = STRESS_PI_DEFAULT_RESULT;
}

stress_pi_method_t get_stress_pi_method(instruction_set_t *instruction_set, bool enable_avx, double **memory_ptr) {

    if (enable_avx) {

        if (support_avx512(instruction_set)) {
            return nullptr;
        }

        if (support_avx256(instruction_set)) {
            return nullptr;
        }

        if (support_avx128(instruction_set)) {
            return nullptr;
        }

    }

    return nullptr;
}

#define STRESS_AVX512_A_INPUT_DIVIDEND_SIZE 16
#define STRESS_AVX512_A_INPUT_DIVIDEND_DIVIDE (STRESS_AVX512_A_INPUT_DIVIDEND_SIZE / 2)
#define STRESS_AVX512_A_INPUT_DIVISOR_OFFSET STRESS_AVX512_A_INPUT_DIVIDEND_SIZE
#define STRESS_AVX512_A_INPUT_DIVISOR_SIZE 16
#define STRESS_AVX512_A_INPUT_DIVISOR_DIVIDE (STRESS_AVX512_A_INPUT_DIVISOR_SIZE / 2)
#define STRESS_AVX512_A_INPUT_SIZE (STRESS_AVX512_A_INPUT_DIVIDEND_SIZE + STRESS_AVX512_A_INPUT_DIVISOR_SIZE)
#define STRESS_AVX512_A_OUTPUT_OFFSET STRESS_AVX512_A_INPUT_SIZE
#define STRESS_AVX512_A_OUTPUT_SIZE (STRESS_AVX512_A_INPUT_SIZE / 2)
#define STRESS_AVX512_A_OUTPUT_DIVIDER (STRESS_AVX512_A_OUTPUT_SIZE / 2)

#define STRESS_AVX512_B_INPUT_SUMMAND_SIZE (STRESS_AVX512_A_OUTPUT_SIZE / 2)
#define STRESS_AVX512_B_INPUT_ADDEND_OFFSET STRESS_AVX512_B_INPUT_SUMMAND_SIZE
#define STRESS_AVX512_B_INPUT_ADDEND_SIZE (STRESS_AVX512_A_OUTPUT_SIZE / 2)
#define STRESS_AVX512_B_INPUT_SIZE (STRESS_AVX512_B_INPUT_SUMMAND_SIZE + STRESS_AVX512_B_INPUT_ADDEND_SIZE)
#define STRESS_AVX512_B_OUTPUT_OFFSET STRESS_AVX512_B_INPUT_SIZE
#define STRESS_AVX512_B_OUTPUT_SIZE (STRESS_AVX512_B_INPUT_SIZE / 2)

#define STRESS_AVX512_C_INPUT_SUMMAND_SIZE (STRESS_AVX512_B_OUTPUT_SIZE / 2)
#define STRESS_AVX512_C_INPUT_ADDEND_OFFSET STRESS_AVX512_C_INPUT_SUMMAND_SIZE
#define STRESS_AVX512_C_INPUT_ADDEND_SIZE (STRESS_AVX512_B_OUTPUT_SIZE / 2)
#define STRESS_AVX512_C_INPUT_SIZE (STRESS_AVX512_C_INPUT_SUMMAND_SIZE + STRESS_AVX512_C_INPUT_ADDEND_SIZE)
#define STRESS_AVX512_C_OUTPUT_OFFSET STRESS_AVX512_C_INPUT_SIZE
#define STRESS_AVX512_C_OUTPUT_SIZE (STRESS_AVX512_C_INPUT_SIZE / 2)

#define STRESS_AVX512_D_INPUT_SUMMAND_SIZE (STRESS_AVX512_C_OUTPUT_SIZE / 2)
#define STRESS_AVX512_D_INPUT_ADDEND_OFFSET STRESS_AVX512_D_INPUT_SUMMAND_SIZE
#define STRESS_AVX512_D_INPUT_ADDEND_SIZE (STRESS_AVX512_C_OUTPUT_SIZE / 2)
#define STRESS_AVX512_D_INPUT_SIZE (STRESS_AVX512_D_INPUT_SUMMAND_SIZE + STRESS_AVX512_D_INPUT_ADDEND_SIZE)
#define STRESS_AVX512_D_OUTPUT_OFFSET STRESS_AVX512_D_INPUT_SIZE
#define STRESS_AVX512_D_OUTPUT_SIZE (STRESS_AVX512_D_INPUT_SIZE / 2)

bool stress_pi_avx512(long &count, long double &result, double* memory) {
    // AVX 512 Div
    for (int i = 0; i < STRESS_AVX512_A_INPUT_DIVIDEND_SIZE; ++i) {
        *(memory + i) = STRESS_PI_DIVIDEND;
        *(memory + STRESS_AVX512_A_INPUT_DIVISOR_OFFSET + i) = count += STRESS_PI_COUNT_DIFF;
    }
    for (int i = 0; i < STRESS_PI_DIV_REPEAT; ++i) {
        if (!avx512_div(memory + STRESS_AVX512_A_INPUT_DIVIDEND_DIVIDE * i,
                       memory + STRESS_AVX512_A_INPUT_DIVISOR_OFFSET + STRESS_AVX512_A_INPUT_DIVISOR_DIVIDE * i,
                       memory + STRESS_AVX512_A_OUTPUT_OFFSET + STRESS_AVX512_A_OUTPUT_DIVIDER * i
                       )) {
            count -= STRESS_PI_COUNT_DIFF * (i + 1);
            return false;
        }
    }

    // AVX 512 Add
    for (int i = 0; i < STRESS_AVX512_B_INPUT_SIZE; ++i) {
        *(memory + i) = *(memory + STRESS_AVX512_A_OUTPUT_OFFSET + i);
    }
    avx512_add(memory, memory + STRESS_AVX512_B_INPUT_ADDEND_OFFSET, memory + STRESS_AVX512_B_OUTPUT_OFFSET);

    // AVX 256 Add
    for (int i = 0; i < STRESS_AVX512_C_INPUT_SIZE; ++i) {
        *(memory + i) = *(memory + STRESS_AVX512_B_OUTPUT_OFFSET + i);
    }
    avx256_add(memory, memory + STRESS_AVX512_C_INPUT_ADDEND_OFFSET, memory + STRESS_AVX512_C_OUTPUT_OFFSET);

    // AVX 128 Add
    for (int i = 0; i < STRESS_AVX512_D_INPUT_SIZE; ++i) {
        *(memory + i) = *(memory + STRESS_AVX512_C_OUTPUT_OFFSET + i);
    }
    avx128_add(memory, memory + STRESS_AVX512_D_INPUT_ADDEND_OFFSET, memory + STRESS_AVX512_D_OUTPUT_OFFSET);

    // FPU Add
    for (int i = 0; i < STRESS_AVX512_D_OUTPUT_SIZE; ++i) {
        result += *(memory + STRESS_AVX512_D_OUTPUT_OFFSET + i);
    }

    return true;
}

bool allocate_mem(double **memory_ptr, const int &size) {
    *memory_ptr = (double *) malloc(size);
    return *memory_ptr;
}
double get_signed_dividend(const int &i) {
    return (i % 2) ? STRESS_PI_DIVIDEND_NEG : STRESS_PI_DIVIDEND;
}
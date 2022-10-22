#include <iostream>

#include "stress_pi.h"
#include "avx.h"
#include "avx128.h"
#include "avx256.h"
#include "avx512.h"

#define STRESS_PI_DEFAULT_COUNT (-1)
#define STRESS_PI_DEFAULT_RESULT 0
#define STRESS_PI_COUNT_DIFF 2

bool allocate_mem(double **, const int &);

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

bool allocate_mem(double **memory_ptr, const int &size) {
    *memory_ptr = (double *) malloc(size);
    return *memory_ptr;
}
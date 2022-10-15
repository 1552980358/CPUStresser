#include "cpuid_util.h"

/**
 * https://stackoverflow.com/a/8249232/11685230
 **/
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(__MINGW32__)

#include <intrin.h>

bool asm_cpuid(const int &method, int values[CPUID_INT_ARRAY_SIZE]) {
    bool is_success = false;
    try {
        __cpuid(values, method);
        is_success = true;
    } catch (errno_t) { }
    return is_success;
}

bool asm_cpuid(const int &method, int *eax, int *ebx, int *ecx, int *edx) {
    int values[CPUID_INT_ARRAY_SIZE];
    auto is_success = asm_cpuid(method, values);
    if (is_success) {
        if (eax) {
            *eax = values[0];
        }
        if (ebx) {
            *ebx = values[1];
        }
        if (ecx) {
            *ecx = values[2];
        }
        if (edx) {
            *edx = values[3];
        }
    }
    return is_success;
}

#elif defined(__linux__) || defined(linux) || defined(__linux) || defined(unix) || defined(__unix) || defined(__unix__)

#include "cpuid.h"

bool asm_cpuid(const int &method, int values[CPUID_INT_ARRAY_SIZE]) {
    return asm_cpuid(method, values, values + 1, values + 2, values + 3);
}

bool asm_cpuid(const int &method, int *eax, int *ebx, int *ecx, int *edx) {
    int cpuid_eax, cpuid_ebx, cpuid_ecx, cpuid_edx;
    auto is_success = __get_cpuid(method, &cpuid_eax, &cpuid_ebx, &cpuid_ecx, &cpuid_edx);
    if (is_success) {
        if (eax) {
            *eax = cpuid_eax;
        }
        if (ebx) {
            *ebx = cpuid_ebx;
        }
        if (ecx) {
            *ecx = cpuid_ecx;
        }
        if (edx) {
            *edx = cpuid_edx;
        }
    }
    return is_success;
}

#endif

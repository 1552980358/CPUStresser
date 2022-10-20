#include "instruction_set.h"
#include "cpuid_util.h"

#define CPUID_METHOD_ID 0x00000000
#define CPUID_METHOD_FEATURES 0x00000001
#define CPUID_METHOD_EXTENDED_FEATURES_1 0x00000007
#define CPUID_METHOD_EXTENDED_ID 0x80000000
#define CPUID_METHOD_EXTENDED_FEATURES_2 0x80000001

void supported_instruction_set(instruction_set_t *instruction_set) {

    int eax, ebx, ecx, edx;
    asm_cpuid(CPUID_METHOD_ID, &eax, nullptr, nullptr, nullptr);

    if (eax >= CPUID_METHOD_FEATURES) {
        asm_cpuid(CPUID_METHOD_FEATURES, nullptr, nullptr, &ecx, &edx);

        instruction_set->HW_MMX    = (edx & (1 << 23));
        instruction_set->HW_SSE    = (edx & (1 << 25));
        instruction_set->HW_SSE2   = (edx & (1 << 26));
        instruction_set->HW_SSE3   = (ecx & (1 << 0));

        instruction_set->HW_SSSE3  = (ecx & (1 << 9));
        instruction_set->HW_SSE41  = (ecx & (1 << 19));
        instruction_set->HW_SSE42  = (ecx & (1 << 20));
        instruction_set->HW_AES    = (ecx & (1 << 25));

        instruction_set->HW_AVX    = (ecx & (1 << 28));
        instruction_set->HW_FMA3   = (ecx & (1 << 12));

        instruction_set->HW_RDRAND = (ecx & (1 << 30));
    }

    if (eax >= CPUID_METHOD_EXTENDED_FEATURES_1) {
        asm_cpuid(CPUID_METHOD_EXTENDED_FEATURES_1, nullptr, &ebx, &ecx, nullptr);
        instruction_set->HW_AVX2        = (ebx & (1 << 5));

        instruction_set->HW_BMI1        = (ebx & (1 << 3));
        instruction_set->HW_BMI2        = (ebx & (1 << 8));
        instruction_set->HW_ADX         = (ebx & (1 << 19));
        instruction_set->HW_SHA         = (ebx & (1 << 29));
        instruction_set->HW_PREFETCHWT1 = (ecx & (1 <<  0));

        instruction_set->HW_AVX512F     = (ebx & (1 << 16));
        instruction_set->HW_AVX512CD    = (ebx & (1 << 28));
        instruction_set->HW_AVX512PF    = (ebx & (1 << 26));
        instruction_set->HW_AVX512ER    = (ebx & (1 << 27));
        instruction_set->HW_AVX512VL    = (ebx & (1 << 31));
        instruction_set->HW_AVX512BW    = (ebx & (1 << 30));
        instruction_set->HW_AVX512DQ    = (ebx & (1 << 17));
        instruction_set->HW_AVX512IFMA  = (ebx & (1 << 21));
        instruction_set->HW_AVX512VBMI  = (ecx & (1 << 1));
    }

    asm_cpuid(CPUID_METHOD_EXTENDED_ID, &eax, nullptr, nullptr, nullptr);
    if (eax >= CPUID_METHOD_EXTENDED_FEATURES_2) {
        asm_cpuid(CPUID_METHOD_EXTENDED_FEATURES_2, nullptr, &ebx, &ecx, &edx);

        instruction_set->HW_x64   = (edx & (1 << 29));
        instruction_set->HW_ABM   = (ecx & (1 << 5));
        instruction_set->HW_SSE4A = (ecx & (1 << 6));
        instruction_set->HW_FMA4  = (ecx & (1 << 16));
        instruction_set->HW_XOP   = (ecx & (1 << 11));
    }
}

bool support_avx512(instruction_set_t *instruction_set) {
    return instruction_set->HW_AVX512F || instruction_set->HW_AVX512CD || instruction_set->HW_AVX512PF
           || instruction_set->HW_AVX512ER || instruction_set->HW_AVX512VL || instruction_set->HW_AVX512BW
           || instruction_set->HW_AVX512DQ || instruction_set->HW_AVX512IFMA || instruction_set->HW_AVX512VBMI
}

bool support_avx256(instruction_set_t *instruction_set) {
    return instruction_set->HW_AVX2;
}

bool support_avx128(instruction_set_t *instruction_set) {
    return instruction_set->HW_AVX;
}
#include "system_util.h"

#include <iostream>
using std::cout;
using std::endl;

#include <thread>
using std::thread;

#include <cpuid.h>

/**
 * Src: https://stackoverflow.com/a/7495023
 **/
#ifdef _WIN32
#define cpuid(cpu_id, leaf) __cpuidex(cpu_id, leaf, 0)
#else
#define cpuid(cpu_id, level) __cpuid_count(level, 0, cpu_id[0], cpu_id[1], cpu_id[2], cpu_id[3])
#endif

int get_cpu_max_threads() {
    int threads;
    if (!(threads = (int) thread::hardware_concurrency())) {    // == 0
        threads = 1;
    }
    return threads;
}

void check_instructions_supported(struct cpu_instructions *instructions) {
    int cpu_id[4];

    cpuid(cpu_id, 0);
    int nIds = cpu_id[0];

    cpuid((int *) &cpu_id, 0x80000000);
    unsigned nExIds = cpu_id[0];
    
    // Detect Features
    if (nIds >= 0x00000001){
        cpuid((int *) &cpu_id, 0x00000001);
        instructions->HW_MMX = (cpu_id[3] & ((int) 1 << 23)) != 0;
        instructions->HW_SSE    = (cpu_id[3] & ((int) 1 << 25)) != 0;
        instructions->HW_SSE2   = (cpu_id[3] & ((int) 1 << 26)) != 0;
        instructions->HW_SSE3   = (cpu_id[2] & ((int) 1 <<  0)) != 0;

        instructions->HW_SSSE3  = (cpu_id[2] & ((int) 1 <<  9)) != 0;
        instructions->HW_SSE41  = (cpu_id[2] & ((int) 1 << 19)) != 0;
        instructions->HW_SSE42  = (cpu_id[2] & ((int) 1 << 20)) != 0;
        instructions->HW_AES    = (cpu_id[2] & ((int) 1 << 25)) != 0;

        instructions->HW_AVX    = (cpu_id[2] & ((int) 1 << 28)) != 0;
        instructions->HW_FMA3   = (cpu_id[2] & ((int) 1 << 12)) != 0;

        instructions->HW_RDRAND = (cpu_id[2] & ((int) 1 << 30)) != 0;
    }
    if (nIds >= 0x00000007){
        cpuid((int *) &cpu_id, 0x00000007);
        instructions->HW_AVX2   = (cpu_id[1] & ((int) 1 <<  5)) != 0;

        instructions->HW_BMI1        = (cpu_id[1] & ((int) 1 <<  3)) != 0;
        instructions->HW_BMI2        = (cpu_id[1] & ((int) 1 <<  8)) != 0;
        instructions->HW_ADX         = (cpu_id[1] & ((int) 1 << 19)) != 0;
        instructions->HW_SHA         = (cpu_id[1] & ((int) 1 << 29)) != 0;
        instructions->HW_PREFETCHWT1 = (cpu_id[2] & ((int) 1 <<  0)) != 0;

        instructions->HW_AVX512F     = (cpu_id[1] & ((int) 1 << 16)) != 0;
        instructions->HW_AVX512CD    = (cpu_id[1] & ((int) 1 << 28)) != 0;
        instructions->HW_AVX512PF    = (cpu_id[1] & ((int) 1 << 26)) != 0;
        instructions->HW_AVX512ER    = (cpu_id[1] & ((int) 1 << 27)) != 0;
        instructions->HW_AVX512VL    = (cpu_id[1] & ((int) 1 << 31)) != 0;
        instructions->HW_AVX512BW    = (cpu_id[1] & ((int) 1 << 30)) != 0;
        instructions->HW_AVX512DQ    = (cpu_id[1] & ((int) 1 << 17)) != 0;
        instructions->HW_AVX512IFMA  = (cpu_id[1] & ((int) 1 << 21)) != 0;
        instructions->HW_AVX512VBMI  = (cpu_id[2] & ((int) 1 <<  1)) != 0;
    }
    if (nExIds >= 0x80000001){
        cpuid((int *) &cpu_id, 0x80000001);
        instructions->HW_x64   = (cpu_id[3] & ((int) 1 << 29)) != 0;
        instructions->HW_ABM   = (cpu_id[2] & ((int) 1 <<  5)) != 0;
        instructions->HW_SSE4A = (cpu_id[2] & ((int) 1 <<  6)) != 0;
        instructions->HW_FMA4  = (cpu_id[2] & ((int) 1 << 16)) != 0;
        instructions->HW_XOP   = (cpu_id[2] & ((int) 1 << 11)) != 0;
    }
}

void show_supported_instructions(struct cpu_instructions *instructions) {
    struct cpu_instructions instr = *instructions;

    if (instr.HW_MMX || instr.HW_x64 || instr.HW_ABM || instr.HW_RDRAND || instr.HW_BMI1
        || instr.HW_BMI2 || instr.HW_ADX || instr.HW_PREFETCHWT1) {
        cout << "Misc: " << endl;

        if (instr.HW_MMX) {
            cout << "MMX ";
        }
        if (instr.HW_x64) {
            cout << "x64 ";
        }
        if (instr.HW_ABM) {
            cout << "ABM ";
        }
        if (instr.HW_RDRAND) {
            cout << "RDRAND ";
        }
        if (instr.HW_BMI1) {
            cout << "BMI1 ";
        }
        if (instr.HW_BMI2) {
            cout << "BMI2 ";
        }
        if (instr.HW_ADX) {
            cout << "ADX ";
        }
        if (instr.HW_PREFETCHWT1) {
            cout << "PREFETCHWT1 ";
        }

        cout << endl;
    }

    if (instr.HW_SSE || instr.HW_SSE2 || instr.HW_SSSE3 || instr.HW_SSE41 || instr.HW_SSE42
        || instr.HW_SSE4A || instr.HW_AES || instr.HW_SHA) {
        cout << endl
             << "SIMD 128-bit: "
             << endl;

        if (instr.HW_SSE) {
            cout << "SSE ";
        }
        if (instr.HW_SSE2) {
            cout << "SSE2 ";
        }
        if (instr.HW_SSE3) {
            cout << "SSE3 ";
        }
        if (instr.HW_SSSE3) {
            cout << "SSSE3 ";
        }
        if (instr.HW_SSE41) {
            cout << "SSE4.1 ";
        }
        if (instr.HW_SSE42) {
            cout << "SSE4.2 ";
        }
        if (instr.HW_SSE4A) {
            cout << "SSE4A ";
        }
        if (instr.HW_AES) {
            cout << "AES ";
        }
        if (instr.HW_SHA) {
            cout << "SHA ";
        }

        cout << endl;
    }

    if (instr.HW_AVX || instr.HW_XOP || instr.HW_FMA3 || instr.HW_FMA4 || instr.HW_AVX2) {
        cout << endl
             << "SIMD 256-bit: "
             << endl;

        if (instr.HW_AVX) {
            cout << "AVX ";
        }
        if (instr.HW_XOP) {
            cout << "XOP ";
        }
        if (instr.HW_FMA3) {
            cout << "FMA3 ";
        }
        if (instr.HW_FMA4) {
            cout << "FMA4 ";
        }
        if (instr.HW_AVX2) {
            cout << "AVX2 ";
        }

        cout << endl;
    }

    if (instr.HW_AVX512F || instr.HW_AVX512CD || instr.HW_AVX512PF || instr.HW_AVX512ER
            || instr.HW_AVX512VL || instr.HW_AVX512BW || instr.HW_AVX512DQ || instr.HW_AVX512IFMA
            || instr.HW_AVX512VBMI) {
        cout << endl
             << "SIMD 512-bit: "
             << endl;

        if (instr.HW_AVX512F) {
            cout << "AVX512F ";
        }
        if (instr.HW_AVX512CD) {
            cout << "AVX512CD ";
        }
        if (instr.HW_AVX512PF) {
            cout << "AVX512PF ";
        }
        if (instr.HW_AVX512ER) {
            cout << "AVX512ER ";
        }
        if (instr.HW_AVX512VL) {
            cout << "HW_AVX512VL ";
        }
        if (instr.HW_AVX512BW) {
            cout << "AVX512BW ";
        }
        if (instr.HW_AVX512DQ) {
            cout << "AVX512DQ ";
        }
        if (instr.HW_AVX512IFMA) {
            cout << "AVX512IFMA ";
        }
        if (instr.HW_AVX512VBMI) {
            cout << "AVX512VBMI ";
        }

        cout << endl;
    }

}
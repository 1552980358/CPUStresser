#include "environment.h"
#include "processor_util.h"

environment::environment() {
    _processor_vendor = processor_get_vendor();
    _processor_name = processor_get_name();
    _processor_threads = processor_get_threads();
    _processor_cache.l1 = processor_get_cache_l1();
    processor_get_cache_l2_l3(&_processor_cache);
    supported_instruction_set(&_instruction_set);
}

string environment::get_processor_vendor() const {
    return _processor_vendor;
}

string environment::get_processor_name() const {
    return _processor_name;
}

int environment::get_processor_threads() const {
    return _processor_threads;
}

processor_cache_t environment::get_processor_cache() const {
    return _processor_cache;
}

instruction_set_t environment::get_instruction_set() const {
    return _instruction_set;
}

#include <iostream>
using std::cout;
using std::endl;

void show_instruction_set(const instruction_set_t &);

void show_environment(const environment_t &environment) {
    cout << "==================== Processor ====================" << endl;
    cout << "      Processor Vendor : " << environment.get_processor_vendor() << endl;
    cout << "        Processor Name : " << environment.get_processor_name() << endl;
    cout << "Processor Thread Count : " << environment.get_processor_threads() << endl;
    auto processor_cache = environment.get_processor_cache();
    cout << "    Processor Cache L1 : " << processor_cache.l1 << " KB" << endl;
    cout << "    Processor Cache L2 : " << processor_cache.l2 << " KB" << endl;
    cout << "    Processor Cache L3 : " << processor_cache.l3 << " KB" << endl;
    cout << "       Instruction Set : ";
    show_instruction_set(environment.get_instruction_set());
}

void show_instruction_set(const instruction_set_t &instruction_set) {
    bool misc = false, simd_128 = false, simd_256 = false;
    if (instruction_set.HW_MMX || instruction_set.HW_x64 || instruction_set.HW_ABM
        || instruction_set.HW_RDRAND || instruction_set.HW_BMI1 || instruction_set.HW_BMI2
        || instruction_set.HW_ADX || instruction_set.HW_PREFETCHWT1) {

        misc = true;
        cout << "Misc < ";

        if (instruction_set.HW_MMX) {
            cout << "MMX ";
        }
        if (instruction_set.HW_x64) {
            cout << "x64 ";
        }
        if (instruction_set.HW_ABM) {
            cout << "ABM ";
        }
        if (instruction_set.HW_RDRAND) {
            cout << "RDRAND ";
        }
        if (instruction_set.HW_BMI1) {
            cout << "BMI1 ";
        }
        if (instruction_set.HW_BMI2) {
            cout << "BMI2 ";
        }
        if (instruction_set.HW_ADX) {
            cout << "ADX ";
        }
        if (instruction_set.HW_PREFETCHWT1) {
            cout << "PREFETCHWT1 ";
        }

        cout << ">" << endl;
    }

    if (instruction_set.HW_SSE || instruction_set.HW_SSE2 || instruction_set.HW_SSSE3
        || instruction_set.HW_SSE41 || instruction_set.HW_SSE42 || instruction_set.HW_SSE4A
        || instruction_set.HW_AES || instruction_set.HW_SHA) {

        if (misc) {
            cout << "                         ";
        }

        simd_128 = true;
        cout << "SIMD 128-bit < ";
        
        if (instruction_set.HW_SSE) {
            cout << "SSE";
        }
        if (instruction_set.HW_SSE2) {
            cout << "SSE2 ";
        }
        if (instruction_set.HW_SSE3) {
            cout << "SSE3 ";
        }
        if (instruction_set.HW_SSSE3) {
            cout << "SSSE3 ";
        }
        if (instruction_set.HW_SSE41) {
            cout << "SSE4.1 ";
        }
        if (instruction_set.HW_SSE42) {
            cout << "SSE4.2 ";
        }
        if (instruction_set.HW_SSE4A) {
            cout << "SSE4A ";
        }
        if (instruction_set.HW_AES) {
            cout << "AES ";
        }
        if (instruction_set.HW_SHA) {
            cout << "SHA ";
        }

        cout << ">" << endl;
    }

    if (instruction_set.HW_AVX || instruction_set.HW_XOP || instruction_set.HW_FMA3
        || instruction_set.HW_FMA4 || instruction_set.HW_AVX2) {

        if (misc || simd_128) {
            cout << "                         ";
        }

        simd_256 = true;
        cout << "SIMD 256-bit < ";

        if (instruction_set.HW_AVX) {
            cout << "AVX ";
        }
        if (instruction_set.HW_XOP) {
            cout << "XOP ";
        }
        if (instruction_set.HW_FMA3) {
            cout << "FMA3 ";
        }
        if (instruction_set.HW_FMA4) {
            cout << "FMA4 ";
        }
        if (instruction_set.HW_AVX2) {
            cout << "AVX2 ";
        }

        cout << ">" << endl;
    }

    if (instruction_set.HW_AVX512F || instruction_set.HW_AVX512CD || instruction_set.HW_AVX512PF
        || instruction_set.HW_AVX512ER || instruction_set.HW_AVX512VL || instruction_set.HW_AVX512BW
        || instruction_set.HW_AVX512DQ || instruction_set.HW_AVX512IFMA || instruction_set.HW_AVX512VBMI) {

        if (misc || simd_128 || simd_256) {
            cout << "                         ";
        }

        cout << "SIMD 512-bit ";
        
        if (instruction_set.HW_AVX512F) {
            cout << "AVX512F ";
        }
        if (instruction_set.HW_AVX512CD) {
            cout << "AVX512CD ";
        }
        if (instruction_set.HW_AVX512PF) {
            cout << "AVX512PF ";
        }
        if (instruction_set.HW_AVX512ER) {
            cout << "AVX512ER ";
        }
        if (instruction_set.HW_AVX512VL) {
            cout << "HW_AVX512VL ";
        }
        if (instruction_set.HW_AVX512BW) {
            cout << "AVX512BW ";
        }
        if (instruction_set.HW_AVX512DQ) {
            cout << "AVX512DQ ";
        }
        if (instruction_set.HW_AVX512IFMA) {
            cout << "AVX512IFMA ";
        }
        if (instruction_set.HW_AVX512VBMI) {
            cout << "AVX512VBMI ";
        }
    }
}
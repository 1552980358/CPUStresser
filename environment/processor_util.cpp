#include <thread>
using std::thread;

#include "processor_util.h"
#include "processor_cache.h"
#include "cpuid_util.h"

int processor_get_threads() {
    int threads;
    if (!(threads = (int) thread::hardware_concurrency())) {    // == 0
        threads = 1;
    }
    return threads;
}

/**
 * Src: https://stackoverflow.com/a/21642909/11685230
 **/
#define VENDOR_EXTENDED 0
#define CPU_VENDOR_LENGTH 0xD
#define CPU_VENDOR_PTR new char[CPU_VENDOR_LENGTH]()

char *processor_get_vendor() {
    auto vendor = CPU_VENDOR_PTR;
    int ebx, ecx, edx;
    asm_cpuid(VENDOR_EXTENDED, nullptr, &ebx, &ecx, &edx);
    memcpy(vendor, &ebx, 4);   // copy EBX
    memcpy(vendor + 4, &edx, 4); // copy EDX
    memcpy(vendor + 8, &ecx, 4); // copy ECX
    vendor[12] = '\0';
    return vendor;
}

/**
 * Src: https://stackoverflow.com/a/7495023
 **/
#define MODEL_EXTENDED 0x80000000
#define MODEL_EXTENDED_BRAND_2 0x80000002
#define MODEL_EXTENDED_BRAND_3 0x80000003
#define MODEL_EXTENDED_BRAND_4 0x80000004
#define CPU_NAME_LENGTH 0x40
#define CPU_NAME_PTR new char[CPU_NAME_LENGTH]()

char *processor_get_name() {

    auto processor_name = CPU_NAME_PTR;

    // Get the information associated with each extended ID.
    int cpu_id[4];
    asm_cpuid(MODEL_EXTENDED, cpu_id);
    if (cpu_id[0] >= MODEL_EXTENDED_BRAND_4) {
        asm_cpuid(MODEL_EXTENDED_BRAND_2, cpu_id);
        memcpy(processor_name, cpu_id, sizeof(int) * 4);
        asm_cpuid(MODEL_EXTENDED_BRAND_3, cpu_id);
        memcpy(processor_name + 16, cpu_id, sizeof(int) * 4);
        asm_cpuid(MODEL_EXTENDED_BRAND_4, cpu_id);
        memcpy(processor_name + 32, cpu_id, sizeof(int) * 4);
    }

    return processor_name;
}

/**
 * For AMD Processors, Cache L1 Info refers to https://www.amd.com/system/files/TechDocs/25481.pdf
 * Page 23
 **/
#define PROCESSOR_CACHE_L1 0x80000005
uint32_t processor_get_cache_l1() {
    int eax, ebx, ecx, edx;
    asm_cpuid(PROCESSOR_CACHE_L1, &eax, &ebx, &ecx, &edx);
    return (ecx >> 24 & 0xFF) * (ecx >> 16 & 0xFF)      // L1DcSize: L1 data cache size in KB. L1 data cache size in KB
                + (edx >> 24 & 0xFF) * (edx >> 16 & 0xFF);   // L1IcSize: L1 instruction cache size KB. L1 instruction cache size KB.
}

#define PROCESSOR_CACHE_L2_L3 0x80000006
#define CACHE_L2_OFFSET 16
#define CACHE_L3_OFFSET 18
#define CACHE_L3_MULTIPLE 512
#define CACHE_L2_L3_ASSOCIATIVITY_OFFSET 12
#define ASSOCIATIVITY_MAP_SIZE 16
void processor_get_cache_l2_l3(processor_cache_t *processor_cache) {
    // Lambda filling associativity map
    auto fill_associativity_map = [](int *associativity_map) {
        /**
         * Refers to https://www.amd.com/system/files/TechDocs/25481.pdf
         * Page 24, Table 4
         *
         * Value definition:
         * 0: Disabled
         * 1: Reserved
         * else value: Specified by Document Table 4
         **/
        std::fill(associativity_map, associativity_map + ASSOCIATIVITY_MAP_SIZE, 1);
        associativity_map[0b0000] = 0;
        associativity_map[0b0001] = 1;
        associativity_map[0b0010] = 2;
        associativity_map[0b0100] = 4;
        associativity_map[0b0110] = 8;
        associativity_map[0b1000] = 16;
        associativity_map[0b1010] = 32;
        associativity_map[0b1011] = 48;
        associativity_map[0b1100] = 64;
        associativity_map[0b1101] = 96;
        associativity_map[0b1110] = 128;
    };

    int eax, ebx, ecx, edx;
    asm_cpuid(PROCESSOR_CACHE_L2_L3, &eax, &ebx, &ecx, &edx);

    /**
     * Refers to https://www.amd.com/system/files/TechDocs/25481.pdf
     * Page 25
     **/
    int associativity_map[ASSOCIATIVITY_MAP_SIZE];
    fill_associativity_map(associativity_map);

    auto associativity = ecx >> CACHE_L2_L3_ASSOCIATIVITY_OFFSET & 0xF;

    processor_cache->l2 = ((ecx >> CACHE_L2_OFFSET) & 0xFFFF) * associativity_map[associativity];

    associativity = edx >> CACHE_L2_L3_ASSOCIATIVITY_OFFSET & 0xF;
    processor_cache->l3 = ((edx >> CACHE_L3_OFFSET) & 0xFFF) * CACHE_L3_MULTIPLE * associativity_map[associativity];

}
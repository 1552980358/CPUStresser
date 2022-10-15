#ifndef CPUSTRESS_CPUID_UTIL_H
#define CPUSTRESS_CPUID_UTIL_H

#define CPUID_INT_ARRAY_SIZE 4

bool asm_cpuid(const int &, int[CPUID_INT_ARRAY_SIZE]);

bool asm_cpuid(const int &, int *, int *, int *, int *);

#endif //CPUSTRESS_CPUID_UTIL_H

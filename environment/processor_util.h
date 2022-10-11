#ifndef CPUSTRESS_PROCESSOR_UTIL_H
#define CPUSTRESS_PROCESSOR_UTIL_H

#include <iostream>
#include "processor_cache.h"

int processor_get_threads();

char *processor_get_vendor();

char *processor_get_name();

uint32_t processor_get_cache_l1();

void processor_get_cache_l2_l3(processor_cache_t *);

#endif //CPUSTRESS_PROCESSOR_UTIL_H

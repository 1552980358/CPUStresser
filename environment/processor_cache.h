#ifndef CPUSTRESS_PROCESSOR_CACHE_H
#define CPUSTRESS_PROCESSOR_CACHE_H

#include <iostream>

typedef struct processor_cache {

    uint32_t l1;

    uint32_t l2 = 0;

    uint32_t l3 = 0;

} processor_cache_t;

#endif //CPUSTRESS_PROCESSOR_CACHE_H

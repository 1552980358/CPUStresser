#include "environment.h"
#include "processor_util.h"

environment::environment() {
    _processor_vendor = processor_get_vendor();
    _processor_name = processor_get_name();
    _processor_threads = processor_get_threads();
    _processor_cache.l1 = processor_get_cache_l1();
    processor_get_cache_l2_l3(&_processor_cache);
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
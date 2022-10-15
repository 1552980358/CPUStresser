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

#include <iostream>
using std::cout;
using std::endl;
void show_environment(const environment_t &environment) {
    cout << "==================== Processor ====================" << endl;
    cout << "      Processor Vendor : " << environment.get_processor_vendor() << endl;
    cout << "        Processor Name : " << environment.get_processor_name() << endl;
    cout << "Processor Thread Count : " << environment.get_processor_threads() << endl;
    auto processor_cache = environment.get_processor_cache();
    cout << "    Processor Cache L1 : " << processor_cache.l1 << " KB" << endl;
    cout << "    Processor Cache L2 : " << processor_cache.l2 << " KB" << endl;
    cout << "    Processor Cache L3 : " << processor_cache.l3 << " KB" << endl;
}
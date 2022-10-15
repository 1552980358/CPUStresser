#ifndef CPUSTRESS_ENVIRONMENT_H
#define CPUSTRESS_ENVIRONMENT_H

#include <string>
using std::string;

#include "processor_cache.h"

typedef class environment {

private:
    char *_processor_vendor;
    char *_processor_name;
    int _processor_threads;
    processor_cache_t _processor_cache;

public:
    environment();
    [[nodiscard]] string get_processor_vendor() const;
    [[nodiscard]] string get_processor_name() const;
    [[nodiscard]] int get_processor_threads() const;
    [[nodiscard]] processor_cache_t get_processor_cache() const;

} environment_t;

void show_environment(const environment_t &);

#endif //CPUSTRESS_ENVIRONMENT_H

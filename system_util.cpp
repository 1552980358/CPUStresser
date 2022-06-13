#include "system_util.h"

#include <thread>
using std::thread;

int get_cpu_max_threads() {
    int threads;
    if (!(threads = (int) thread::hardware_concurrency())) {    // == 0
        threads = 1;
    }
    return threads;
}
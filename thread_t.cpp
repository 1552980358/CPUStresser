#include "thread_t.h"
#include "cpu_stress.h"
#include "avx128.h"
#include "avx256.h"
#include "avx512.h"

#include <iostream>
using std::cout;
using std::endl;

void thread_runnable(thread_t *thread_ptr, const int &stress_mode, const int &id) {
    thread_ptr->started();
    void (*stress_function)(int64_t *, double *, double *, double *);
    double *buffer_input = nullptr;
    double *buffer_result = nullptr;

    switch (stress_mode) {
        case STRESS_MODE_FPU:
            stress_function = stress_mode_fpu;
            break;
        case STRESS_MODE_AVX1_MIX:
            buffer_input = (double *) malloc(sizeof(double) * AVX128_BUFFER_INPUT_SIZE);
            buffer_result = (double *) malloc(sizeof(double) * AVX128_BUFFER_RESULT_SIZE);
            stress_function = stress_mode_avx1_mix;
            break;
        case STRESS_MODE_AVX2_MIX:
            buffer_input = (double *) malloc(sizeof(double) * AVX256_BUFFER_INPUT_SIZE);
            buffer_result = (double *) malloc(sizeof(double) * AVX256_BUFFER_RESULT_SIZE);
            stress_function = stress_mode_avx2_mix;
            break;
        case STRESS_MODE_AVX512F_MIX:
            buffer_input = (double *) malloc(sizeof(double) * AVX512_BUFFER_INPUT_SIZE);
            buffer_result = (double *) malloc(sizeof(double) * AVX512_BUFFER_RESULT_SIZE);
            stress_function = stress_mode_avx512f_mix;
            break;
        case STRESS_MODE_AVX1_PURE:
            buffer_input = (double *) malloc(sizeof(double) * AVX128_BUFFER_INPUT_SIZE * 2);
            buffer_result = (double *) malloc(sizeof(double) * AVX128_BUFFER_RESULT_SIZE * 2);
            stress_function = stress_mode_avx1_pure;
            break;
        case STRESS_MODE_AVX2_PURE:
            buffer_input = (double *) malloc(sizeof(double) * AVX256_BUFFER_INPUT_SIZE * 2);
            buffer_result = (double *) malloc(sizeof(double) * AVX256_BUFFER_RESULT_SIZE * 2);
            stress_function = stress_mode_avx2_pure;
            break;
        case STRESS_MODE_AVX512F_PURE:
            buffer_input = (double *) malloc(sizeof(double) * AVX512_BUFFER_INPUT_SIZE * 2);
            buffer_result = (double *) malloc(sizeof(double) * AVX512_BUFFER_RESULT_SIZE * 2);
            stress_function = stress_mode_avx512f_pure;
            break;
    }

    while (thread_ptr->is_run()) {
        stress_function((int64_t *) &thread_ptr->num, (double *) &thread_ptr->pi, buffer_input, buffer_result);
    }

    if (buffer_input) {
        free(buffer_input);
    }
    if (buffer_result) {
        free(buffer_result);
    }
}

thread_t::thread_t(thread_t *prev, const int &stress_mode, const int &id) {
    _prev = prev;
    if (prev) {
        prev->_next = this;
    }
    _next = nullptr;

    _id = id;
    pi = 0;
    num = -1;

    _is_started = false;
    _is_run = true;

    _thread = new thread(thread_runnable, this, stress_mode, id);
}

void thread_t::stop() {
    if (_is_run) {
        _is_run = false;
    }
    if (_thread && _thread->joinable()) {
        _thread->join();
    }
    _thread = nullptr;
}

thread_t::~thread_t() {
    stop();
}

void thread_t::set_prev(thread_t *prev) {
    _prev = prev;
}

void thread_t::set_next(thread_t *next) {
    _next = next;
}

thread_t *thread_t::get_prev() {
    return _prev;
}

thread_t *thread_t::get_next() {
    return _next;
}

bool thread_t::is_run() const {
    return _is_run;
}

bool thread_t::is_started() const {
    return _is_started;
}

void thread_t::started() {
    _is_started = true;
}

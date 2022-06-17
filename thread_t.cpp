#include "thread_t.h"

#include <iostream>
using std::cout;
using std::endl;

#include <immintrin.h>

void avx256_double_div_infinitive(double *result, const __m256d &format, int64_t &num) {
    __m256d result_div_infinitive = _mm256_div_pd(format, _mm256_set_pd((double) num, (double) (num + 2), (double) (num + 4), (double) (num + 6)));
    auto * result_div = (double *) &result_div_infinitive;
    for (int i = 0; i < 4; ++i) {
        result[i] = result_div[i];
    }
    num += 8;
}

double avx128_double_sum(double *result_avx256) {
    __m128d result_avx128 = _mm_add_pd(
            _mm_set_pd(result_avx256[0], result_avx256[1]),
            _mm_set_pd(result_avx256[2], result_avx256[3])
            );
    auto result = (double *) &result_avx128;
    return result[0] + result[1];
}

void thread_runnable(thread_t *thread_ptr, const int &id) {
    thread_ptr->started();
    auto format = _mm256_set_pd((double) 4, (double) -4, (double) 4, (double) -4);
    int64_t num = 1;
    double pi = 0;
    double buffer[4];
    while (thread_ptr->is_run()) {
        avx256_double_div_infinitive((double *) &buffer, format, num);
        pi += avx128_double_sum((double *) &buffer);
    }
}

thread_t::thread_t(thread_t *prev, const int &id) {
    _prev = prev;
    if (prev) {
        prev->_next = this;
    }
    _next = nullptr;

    _id = id;

    _is_started = false;
    _is_run = true;

    _thread = new thread(thread_runnable, this, id);
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

bool thread_t::is_run() {
    return _is_run;
}

bool thread_t::is_started() const {
    return _is_started;
}

void thread_t::started() {
    _is_started = true;
}

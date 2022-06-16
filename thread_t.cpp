#include "thread_t.h"

#include <iostream>
using std::cout;
using std::endl;

void thread_runnable(thread_t *thread_ptr, const int &id) {
    thread_ptr->started();
    while (thread_ptr->is_run()) {
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

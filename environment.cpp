#include "environment.h"

#include <iostream>
using std::cout;
using std::endl;
using std::all_of;

#include <iomanip>
using std::left;
using std::right;
using std::setfill;
using std::setw;

#include <string>
using std::to_string;

#include "system_util.h"
#include "cpu_stress.h"

#define INITIAL_THREAD_SIZE 0
#define START_THREAD_STATE_FILL '.'
#define START_THREAD_STATE_W 5

environment::environment() {
    _is_start = false;
    _thread_size = INITIAL_THREAD_SIZE;
    _threads_first = nullptr;
    _threads_last = nullptr;
    _stress_mode = STRESS_MODE_AVX2;
}

void environment::start() {
    if (!_is_start) {
        if (_thread_size == INITIAL_THREAD_SIZE) {
            _thread_size = get_cpu_max_threads();
        }
        _is_start = true;

        cout << "Now starting " << _thread_size << " thread(s)..." << endl;
        thread_t *current_thread_ptr = nullptr;
        for (int i = 0; i < _thread_size; ++i) {
            cout << left << setfill(START_THREAD_STATE_FILL) << setw(START_THREAD_STATE_W) << "Launching thread #" + to_string(i);
            current_thread_ptr = new thread_t(current_thread_ptr, _stress_mode, i);
            if (!_threads_first) {
                _threads_first = current_thread_ptr;
            }
            cout << "Launching";
            while (!current_thread_ptr->is_started());
            cout << "\b\b\b\b\b\b\b\b\bDone     " << endl;
        }
        _threads_last = current_thread_ptr;
    }
}

void environment::set(const int &set_size) {
    if (!_is_start) {
        _thread_size = set_size;
        return;
    }
    if (_thread_size > set_size) {
        remove(_thread_size - set_size);
    } else if (_thread_size < set_size) {
        add(set_size - _thread_size);
    }
}

void environment::add(const int &add_size) {
    if (!_is_start) {
        _thread_size += add_size;
        return;
    }
    thread_t *current_thread_t = _threads_last;
    for (int i = 0; i < add_size; ++i) {
        current_thread_t = new thread_t(current_thread_t, _stress_mode, _thread_size + i);
    }
    _threads_last = current_thread_t;
    if (!_threads_first) {
        while (current_thread_t->get_prev()) {
            current_thread_t = current_thread_t->get_prev();
        }
        _threads_first = current_thread_t;
    }
    _thread_size += add_size;
}

void environment::remove(const int &remove_size) {
    if (!_is_start) {
        _thread_size = _thread_size < remove_size ? 0 : _thread_size - remove_size;
        return;
    }
    if (remove_size >= _thread_size) {
        return remove_all();
    }
    thread_t *current_thread_t = _threads_last;
    thread_t *last;
    for (int i = 0; i < remove_size; ++i) {
        last = current_thread_t->get_prev();
        delete(current_thread_t);
        current_thread_t = last;
    }
    current_thread_t->set_next(nullptr);
    _threads_last = current_thread_t;
    _thread_size -= remove_size;
}

void environment::remove_all() {
    thread_t *current_thread_t = _threads_first;
    thread_t *next;
    for (int i = 0; i < _thread_size; ++i) {
        next = current_thread_t->get_next();
        current_thread_t->stop();
        delete(current_thread_t);
        current_thread_t = next;
    }
    _thread_size = INITIAL_THREAD_SIZE;
}

void environment::set_mode(const int &mode) {
    _stress_mode = mode;
}

int environment::get_mode() const {
    return _stress_mode;
}

void environment::show_thread_size() const {
    if (_is_start) {
        cout << "Now " << _thread_size << " thread(s) running." << endl;
    } else {
        cout << "Now " << _thread_size << " thread(s) set. " << endl;
    }
}

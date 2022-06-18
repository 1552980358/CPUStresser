#ifndef CPUSTRESSER_ENVIRONMENT_H
#define CPUSTRESSER_ENVIRONMENT_H

#include "thread_t.h"

class environment {

private:
    int _thread_size;
    thread_t *_threads_first;
    thread_t *_threads_last;

    bool _is_start;

    int _stress_mode;

public:
    environment();

    void start();

    void set(const int &);
    void add(const int &);
    void remove(const int &);
    void remove_all();

    void set_mode(const int &);
    int get_mode() const;

    void show_thread_size() const;
};

#endif //CPUSTRESSER_ENVIRONMENT_H

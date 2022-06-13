#ifndef CPUSTRESSER_ENVIRONMENT_H
#define CPUSTRESSER_ENVIRONMENT_H

#include "thread_t.h"

class environment {

private:
    int _thread_size;
    thread_t *_threads_first;
    thread_t *_threads_last;

    bool _is_start;

public:
    environment();

    void start();

    void set(const int &);
    void add(const int &);
    void remove(const int &);
    void remove_all();

    void show_thread_size() const;
};

#endif //CPUSTRESSER_ENVIRONMENT_H

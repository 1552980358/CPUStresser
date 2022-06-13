#ifndef CPUSTRESSER_THREAD_T_H
#define CPUSTRESSER_THREAD_T_H

#include <thread>
using std::thread;

class thread_t {

private:
    int _id;
    thread *_thread;
    bool _is_run;

    thread_t *_prev;
    thread_t *_next;

public:
    explicit thread_t(thread_t *, const int &);
    ~thread_t();

    void stop();

    void set_prev(thread_t *);
    void set_next(thread_t *);

    thread_t *get_prev();
    thread_t *get_next();

    bool is_run();
};


#endif //CPUSTRESSER_THREAD_T_H

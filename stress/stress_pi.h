#ifndef CPUSTRESS_PI_H
#define CPUSTRESS_PI_H

#include "../environment/instruction_set.h"

typedef bool (*stress_pi_method_t)(long &, long double &, double *);

stress_pi_method_t get_stress_pi_method(instruction_set_t *instruction_set, bool enable_avx, double **memory_ptr);

#endif //CPUSTRESS_PI_H

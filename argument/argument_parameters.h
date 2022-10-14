#ifndef CPUSTRESS_ARGUMENT_PARAMETERS_H
#define CPUSTRESS_ARGUMENT_PARAMETERS_H

#include "string"
using std::string;

typedef enum argument_parameters {

    ARGUMENT_INIT,

    ARGUMENT_UNKNOWN,

} argument_parameters_t;

argument_parameters_t resolve_argument(const string &);

#endif //CPUSTRESS_ARGUMENT_PARAMETERS_H

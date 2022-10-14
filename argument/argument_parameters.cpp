#include "argument_parameters.h"

#define ARGUMENT_INIT_SHORT "-i"
#define ARGUMENT_INIT_LONG "--init"

argument_parameters_t resolve_argument(const string &argument) {
    if (argument == ARGUMENT_INIT_SHORT || argument == ARGUMENT_INIT_LONG) {
        return ARGUMENT_INIT;
    }

    return ARGUMENT_UNKNOWN;
}
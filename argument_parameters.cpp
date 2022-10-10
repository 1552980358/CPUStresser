#include "argument_parameters.h"

#define ARGUMENT_CONFIG_SHORT "-c"
#define ARGUMENT_CONFIG_LONG "--config"

argument_parameters_t resolve_argument(const string &argument) {
    if (argument == ARGUMENT_CONFIG_SHORT || argument == ARGUMENT_CONFIG_LONG) {
        return ARGUMENT_CONFIG;
    }

    return ARGUMENT_UNKNOWN;
}
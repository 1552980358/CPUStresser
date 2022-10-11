#include <iostream>

#include "argument_parameters.h"
#include "exit_code.h"

bool resolve_arguments(const int &, const char **);

int main(int argc, char **argv) {

    if (argc > 1) {    // has argument(s)
        if (!resolve_arguments(argc, (const char **) argv)) {
            return EXIT_CODE_UNKNOWN_ARGUMENT;
        }
    }

    return EXIT_CODE_CORRECT;
}

bool resolve_arguments(const int &argc, const char **argv) {
    auto count = 1;
    while (++count < argc) {
        switch (resolve_argument(argv[count])) {
            case ARGUMENT_CONFIG:
                break;
            case ARGUMENT_UNKNOWN:
                return false;
        }
    }
    return true;
}
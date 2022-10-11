#include <iostream>
using std::cout;
using std::endl;

#include "argument_parameters.h"
#include "exit_code.h"

#include "environment/environment.h"

bool resolve_arguments(const int &, const char **);
void show_environment(const environment_t &);

int main(int argc, char **argv) {

    if (argc > 1) {    // has argument(s)
        if (!resolve_arguments(argc, (const char **) argv)) {
            return EXIT_CODE_UNKNOWN_ARGUMENT;
        }
    }

    environment_t environment;
    show_environment(environment);

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

void show_environment(const environment_t &environment) {
    cout << "==================== Processor ====================" << endl;
    cout << "      Processor Vendor : " << environment.get_processor_vendor() << endl;
    cout << "        Processor Name : " << environment.get_processor_name() << endl;
    cout << "Processor Thread Count : " << environment.get_processor_threads() << endl;
    auto processor_cache = environment.get_processor_cache();
    cout << "    Processor Cache L1 : " << processor_cache.l1 << " KB" << endl;
    cout << "    Processor Cache L2 : " << processor_cache.l2 << " KB" << endl;
    cout << "    Processor Cache L3 : " << processor_cache.l3 << " KB" << endl;
}
#include <iostream>
using std::cout;
using std::endl;
#include <filesystem>
namespace filesystem = std::filesystem;
using filesystem::exists;
using filesystem::path;

#include "argument/argument_parameters.h"
#include "argument/argument_init.h"
#include "exit_code.h"

#include "environment/environment.h"

bool resolve_arguments(const string &executable_dir, const int &, const char **);
void show_environment(const environment_t &);

int main(int argc, char **argv) {

    if (argc > 1) {    // has argument(s)
        auto executable_path = string(*argv);
        auto executable_dir = executable_path.substr(0, executable_path.find_last_of(path::preferred_separator));
        if (!resolve_arguments(executable_dir, argc, (const char **) argv)) {
            return EXIT_CODE_UNKNOWN_ARGUMENT;
        }
    }

    environment_t environment;
    show_environment(environment);

    return EXIT_CODE_CORRECT;
}

bool resolve_arguments(const string &executable_dir, const int &argc, const char **argv) {
    auto count = 1;
    while (count < argc) {
        switch (resolve_argument(argv[count++])) {
            case ARGUMENT_INIT:
                argument_init(executable_dir);
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
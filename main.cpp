#include <iostream>
using std::cout;
using std::endl;
#include <filesystem>
namespace filesystem = std::filesystem;
using filesystem::exists;
using filesystem::path;

#include "exit_code.h"

#include "environment/environment.h"

void show_environment(const environment_t &);

int main(int argc, char **argv) {



    return EXIT_CODE_CORRECT;
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
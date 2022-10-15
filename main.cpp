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
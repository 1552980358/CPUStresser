#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

#include "argument_init.h"
#include "../winring0/winring0_dlls.h"

void argument_init(const string &executable_dir) {
    cout << "Initialize CPUStress..." << endl;
    copy_win_ring0_dlls(executable_dir);
}
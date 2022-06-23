#include "command_help.h"

void command_help(vector<string> *, environment *) {
    cout << "Commands: { help | start | stop | exit | # | set | + | add | - | rm }" << endl
         << endl
         << "Command <help>: Show help message" << endl
         << endl
         << "Command <start>: Start thread(s)" << endl
         << endl
         << "Command <stop>: Stop all thread(s)" << endl
         << endl
         << "Command <exit>: Stop all thread(s) and leave program" << endl
         << endl;
    set_help();
    cout << endl;
    add_help();
    cout << endl;
    remove_help();
    cout << endl;
    mode_help();
}

void set_help() {
    cout << "Command <#/set> <NUMBER>: Set <NUMBER> threads" << endl
         << "    Example: set 4 => Set 4 threads" << endl
         << "    Example: # 4   => Set 4 threads" << endl;
}

void add_help() {
    cout << "Command <+/add> <NUMBER>: Add <NUMBER> threads" << endl
         << "    Example: add 4 => Add 4 more threads" << endl
         << "    Example: + 4   => Add 4 more threads" << endl;
}

void remove_help() {
    cout << "Command <-/rm> <NUMBER>: Remove <NUMBER> threads" << endl
         << "    Example: rm 4 =>  Remove 4 already added threads" << endl
         << "    Example: - 4  => Remove 4 already added threads" << endl;
}

void mode_help() {
    cout << "Command <$/mode> <NUMBER>: Set stress mode" << endl
         << "    MODE 0 => FPU stress" << endl
         << "    MODE 1 => AVX1 + FPU mix mode stress" << endl
         << "    MODE 2 => AVX2 + AVX1 + FPU mix mode stress" << endl
         << "    MODE 3 => AVX512 + AVX2 + AVX1 + FPU mix mode stress" << endl;
}
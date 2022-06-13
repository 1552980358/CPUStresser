#include "command_help.h"

void command_help() {
    cout << "Commands: { help | start | stop | exit | # | set | + | add | - | rm }" << endl
         << endl
         << "Command <help>: Show help message" << endl
         << endl
         << "Command <start>: Start thread(s)"
         << endl
         << "Command <stop>: Stop all thread(s)" << endl
         << endl
         << "Command <exit>: Stop all thread(s) and leave program" << endl;
    set_help();
    add_help();
    remove_help();
}

void set_help() {
    cout << "<#/set> <NUMBER>: Set <NUMBER> threads" << endl
         << "    Example: set 4 => Set 4 threads" << endl
         << "    Example: # 4   => Set 4 threads" << endl;
}

void add_help() {
    cout << "<+/add> <NUMBER>: Add <NUMBER> threads" << endl
         << "    Example: add 4 => Add 4 more threads" << endl
         << "    Example: + 4   => Add 4 more threads" << endl;
}

void remove_help() {
    cout << "Command <-/rm> <NUMBER>: Remove <NUMBER> threads" << endl
         << "    Example: rm 4 =>  Remove 4 already added threads" << endl
         << "    Example: - 4  => Remove 4 already added threads" << endl;
}
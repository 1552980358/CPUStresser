#ifndef CPUSTRESSER_COMMAND_HELP_H
#define CPUSTRESSER_COMMAND_HELP_H

#include "environment.h"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

void command_help(vector<string> *, environment *);
void set_help();
void add_help();
void remove_help();
void mode_help();

#endif //CPUSTRESSER_COMMAND_HELP_H

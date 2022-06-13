#include "command_decode.h"

#include <iostream>
using std::cin;
using std::cout;
using std::istringstream;
using std::move;
using std::endl;

#include <string>
using std::getline;
using std::string;

#include <vector>
#include <sstream>

using std::vector;

#include "string_util.h"
#include "command_help.h"

#define DELIM ' '
#define COMMAND_START "start"
#define COMMAND_STOP "stop"
#define COMMAND_EXIT "exit"
#define COMMAND_SET_STR "set"
#define COMMAND_SET_SIGN "#"
#define COMMAND_ADD_STR "add"
#define COMMAND_ADD_SIGN "+"
#define COMMAND_REMOVE_STR "rm"
#define COMMAND_REMOVE_SIGN "-"

vector<string> *split_str(const string &, const char & = DELIM);
vector<string> *analysis_string_vector(vector<string> *, environment *);

bool read_command(environment *env_ptr) {
    cout << "Command >";
    string line;
    getline(cin, line);
    if (line == COMMAND_EXIT) {
        return false;
    }

    delete(analysis_string_vector(split_str(line), env_ptr));
    cout << endl;
    return true;
}

vector<string> *split_str(const string &str, const char &delim) {
    auto *result = new vector<string>;

    istringstream string_stream(str);
    string tmp;
    while (getline(string_stream, tmp, delim)) {
        if (!tmp.empty()) {
            result->emplace_back(move(tmp));
        }
    }

    return result;
}

#define COMMAND_HELP "help"

void command_start(environment *);
void command_stop(environment *);
void command_set(vector<string> *, environment *);
void command_add(vector<string> *, environment *);
void command_remove(vector<string> *, environment *);

vector<string> *analysis_string_vector(vector<string> *string_vector, environment *env_ptr) {
    string command;
    if (string_vector->empty() || (command = string_vector->at(0)) == COMMAND_HELP) {
        command_help();
    } else if (command == COMMAND_START) {
        command_start(env_ptr);
    } else if (command == COMMAND_STOP) {
        command_stop(env_ptr);
    } else if (command == COMMAND_SET_SIGN || command == COMMAND_SET_STR) {
        command_set(string_vector, env_ptr);
    } else if (command == COMMAND_ADD_SIGN || command == COMMAND_ADD_STR) {
        command_add(string_vector, env_ptr);
    } else if (command == COMMAND_REMOVE_SIGN || command == COMMAND_REMOVE_STR) {
        command_remove(string_vector, env_ptr);
    }
    return string_vector;
}

void command_start(environment *env_ptr) {
    env_ptr->start();
}

void command_stop(environment *env_ptr) {
    env_ptr->remove_all();
}

void command_set(vector<string> *string_vector, environment *env_ptr) {
    int set_number;
    if (string_vector->size() != 2 || (set_number = str_to_int(string_vector->at(1))) == CONVERT_ERROR_INT) {
        return set_help();
    }
    env_ptr->set(set_number);
    cout << "Set " << set_number << " thread(s)." << endl;
    env_ptr->show_thread_size();
}

void command_add(vector<string> *string_vector, environment *env_ptr) {
    int add_number;
    if (string_vector->size() != 2 || (add_number = str_to_int(string_vector->at(1))) == CONVERT_ERROR_INT) {
        return add_help();
    }
    env_ptr->add(add_number);
    cout << "Newly add " << add_number << " thread(s)." << endl;
    env_ptr->show_thread_size();
}

void command_remove(vector<string> *string_vector, environment *env_ptr) {
    int remove_number;
    if (string_vector->size() != 2 || (remove_number = str_to_int(string_vector->at(1))) == CONVERT_ERROR_INT) {
        return set_help();
    }
    env_ptr->remove(remove_number);
    cout << "Remove " << remove_number << " thread(s)." << endl;
    env_ptr->show_thread_size();
}
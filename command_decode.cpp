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
#include "cpu_stress.h"
#include "system_util.h"

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
#define COMMAND_MODE_STR "mode"
#define COMMAND_MODE_SIGN "$"
#define COMMAND_CHECK "check"

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

void command_start(vector<string> *, environment *);
void command_stop(vector<string> *, environment *);
void command_set(vector<string> *, environment *);
void command_add(vector<string> *, environment *);
void command_remove(vector<string> *, environment *);
void command_mode(vector<string> *, environment *);
void command_check(vector<string> *, environment *);

vector<string> *analysis_string_vector(vector<string> *string_vector, environment *env_ptr) {
    string command;
    void (*command_method)(vector<string> *, environment *);
    if (command == COMMAND_START) {
        command_method = command_start;
    } else if (command == COMMAND_STOP) {
        command_method = command_stop;
    } else if (command == COMMAND_SET_SIGN || command == COMMAND_SET_STR) {
        command_method = command_set;
    } else if (command == COMMAND_ADD_SIGN || command == COMMAND_ADD_STR) {
        command_method = command_add;
    } else if (command == COMMAND_REMOVE_SIGN || command == COMMAND_REMOVE_STR) {
        command_method = command_remove;
    } else if (command == COMMAND_MODE_STR || command == COMMAND_MODE_SIGN) {
        command_method = command_mode;
    } else if (command == COMMAND_CHECK) {
        command_method = command_check;
    } else {
        command_method = command_help;
    }
    command_method(string_vector, env_ptr);
    return string_vector;
}

void command_start(vector<string> *, environment *env_ptr) {
    env_ptr->start();
}

void command_stop(vector<string> *, environment *env_ptr) {
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

void command_mode(vector<string> *string_vector, environment *env_ptr) {
    if (string_vector->size() == 1) {
        return show_mode(env_ptr->get_mode());
    }
    int mode_number;

    cpu_instructions_t instructions;
    check_instructions_supported((cpu_instructions_t *) &instructions);

    switch (mode_number = str_to_int(string_vector->at(1))) {
        case STRESS_MODE_FPU:
        case STRESS_MODE_AVX1_MIX:
        case STRESS_MODE_AVX2_MIX:
        case STRESS_MODE_AVX1_PURE:
        case STRESS_MODE_AVX2_PURE:
            break;
        case STRESS_MODE_AVX512F_MIX:
            if (instructions.HW_AVX512F) {
                env_ptr->set_mode(mode_number);
            } else {
                cout << "AVX512F instruction set is not supported by your processor." << endl
                     << "Force enabling may cause crash when operating." << endl
                     << "Force enable <Y/N>? [default: N] ";
                switch (getchar()) {
                    case 'Y':
                    case 'y':
                        cout << "AVX512F + AVX2 + AVX1 + FPU mix mode enabled." << endl;
                        break;
                    case 'N':
                    case 'n':
                        cout << "AVX512F + AVX2 + AVX1 + FPU mix mode disabled." << endl;
                        break;
                    default:
                        cout << "Unknown key. Disable AVX512F + AVX2 + AVX1 + FPU mix mode by default." << endl;
                        break;
                }
            }
            break;
        case STRESS_MODE_AVX512F_PURE:
            if (instructions.HW_AVX512F) {
                env_ptr->set_mode(mode_number);
            } else {
                cout << "AVX512F instruction set is not supported by your processor." << endl
                     << "Force enabling may cause crash when operating." << endl
                     << "Force enable <Y/N>? [default: N] ";
                switch (getchar()) {
                    case 'Y':
                    case 'y':
                        cout << "AVX512F + FPU pure mode enabled." << endl;
                        break;
                    case 'N':
                    case 'n':
                        cout << "AVX512F + FPU pure mode disabled." << endl;
                        break;
                    default:
                        cout << "Unknown key. Disable AVX512F + FPU pure mode by default." << endl;
                        break;
                }
            }
            break;
        default:
            mode_help();
            break;
    }
}

void command_check(vector<string> *, environment *) {
    show_processor_name();

    // Instruction sets
    struct cpu_instructions instructions{};
    check_instructions_supported((cpu_instructions_t *) &instructions);
    show_supported_instructions((cpu_instructions_t *) &instructions);
}
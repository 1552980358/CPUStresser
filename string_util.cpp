#include "string_util.h"

using std::all_of;
using std::stoi;

#define CHAR_0 '0'
#define CHAR_9 '9'

bool check_is_digits(const string &str) {
    return all_of(str.begin(), str.end(), [](char c) { return c >= CHAR_0 && c <= CHAR_9; });
}

int str_to_int(const string &str) {
    if (!check_is_digits(str)) {
        return CONVERT_ERROR_INT;
    }
    return stoi(str);
}
#include <iostream>
using std::cerr;
using std::endl;

#include "avx.h"

bool copy_result(const int &size, const double *result, double *output) {
    try {
        for (int i = 0; i < size; ++i) {
            *(output + i) = *(result + (size - 1 - i));
        }
        return true;
    } catch (...) {
        cerr << "Pointer Out of Bounds at " << output << endl;
    }
    return false;
}
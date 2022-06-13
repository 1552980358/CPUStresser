#include <iostream>
#include <thread>

#include "command_decode.h"
#include "environment.h"

int main() {
    environment config;
    while (read_command(&config)) {

    }
    return 0;
}

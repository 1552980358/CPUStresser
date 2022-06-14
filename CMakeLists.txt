cmake_minimum_required(VERSION 3.22)
project(CPUStresser)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories()

add_executable(CPUStresser main.cpp command_decode.cpp environment.cpp thread_t.cpp string_util.cpp command_help.cpp system_util.cpp)

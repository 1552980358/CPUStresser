cmake_minimum_required(VERSION 3.23)
project(CPUStress)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(environment)

add_executable(
        CPUStress
        main.cpp
        argument_parameters.cpp argument_parameters.h
        exit_code.h
)

target_link_libraries(CPUStress environment)
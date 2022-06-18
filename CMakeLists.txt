cmake_minimum_required(VERSION 3.22)
project(CPUStresser)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_FLAGS "-mavx512f -mavx -mavx2")

include_directories(avx)

add_executable(CPUStresser
        main.cpp
        command_decode.cpp
        environment.cpp
        thread_t.cpp
        string_util.cpp
        command_help.cpp
        system_util.cpp
        avx/avx128.cpp
        avx/avx256.cpp
        avx/avx512.cpp
        avx/avx.cpp
        cpu_stress.cpp
        )

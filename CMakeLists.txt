cmake_minimum_required(VERSION 3.23)
project(CPUStress)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS " -static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(environment)
add_subdirectory(argument)

include(CMakeRC.cmake)

cmrc_add_resource_library(
        winring0 NAMESPACE winring0
        lib/WinRing0x64.dll lib/WinRing0.dll
        lib/WinRing0x64.sys lib/WinRing0.sys
)

add_executable(
        CPUStress
        main.cpp
        exit_code.h
        winring0/winring0.cpp winring0/winring0.h
        winring0/winring0_dlls.cpp winring0/winring0_dlls.h
)

target_link_libraries(CPUStress PRIVATE argument environment winring0)
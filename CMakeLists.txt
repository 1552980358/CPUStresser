cmake_minimum_required(VERSION 3.23)
project(CPUStress)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS " -static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include(CMakeRC.cmake)
cmrc_add_resource_library(
        winring0dll NAMESPACE winring0dll
        WHENCE winring0/lib
        PREFIX winring0
        winring0/lib/WinRing0x64.dll winring0/lib/WinRing0.dll
        winring0/lib/WinRing0x64.sys winring0/lib/WinRing0.sys
)

add_subdirectory(environment)

add_executable(
        CPUStress
        main.cpp
        exit_code.h
        winring0/winring0.cpp winring0/winring0.h
        winring0/winring0_dlls.cpp winring0/winring0_dlls.h
)

target_link_libraries(CPUStress PRIVATE environment winring0dll)
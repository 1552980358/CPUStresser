add_library(
        winring0
        winring0.cpp winring0.h
        winring0_dlls.cpp winring0_dlls.h
)

target_include_directories(winring0 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
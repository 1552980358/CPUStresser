add_library(
        stress
        stress.cpp stress_pi.h
)

target_include_directories(stress PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(avx)
add_library(
        avx
        avx.cpp avx.cpp
        avx128.cpp avx128.h
        avx256.cpp avx256.h
        avx512.cpp avx512.h
)

target_include_directories(avx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(stress avx)
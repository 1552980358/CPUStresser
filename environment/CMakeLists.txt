add_library(
        environment
        environment.cpp environment.h
        processor_util.cpp processor_util.h
        processor_cache.h
        cpuid_util.cpp cpuid_util.h
        process_privilege_util.cpp process_privilege_util.h)

target_include_directories(environment PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
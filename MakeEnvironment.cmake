cmake_host_system_information(RESULT PROCESSOR_NAME QUERY PROCESSOR_NAME)
cmake_host_system_information(RESULT NUMBER_OF_PHYSICAL_CORES QUERY NUMBER_OF_PHYSICAL_CORES)
cmake_host_system_information(RESULT NUMBER_OF_LOGICAL_CORES QUERY NUMBER_OF_LOGICAL_CORES)

cmake_host_system_information(RESULT TOTAL_VIRTUAL_MEMORY QUERY TOTAL_VIRTUAL_MEMORY)
cmake_host_system_information(RESULT AVAILABLE_VIRTUAL_MEMORY QUERY AVAILABLE_VIRTUAL_MEMORY)
cmake_host_system_information(RESULT TOTAL_PHYSICAL_MEMORY QUERY TOTAL_PHYSICAL_MEMORY)
cmake_host_system_information(RESULT AVAILABLE_PHYSICAL_MEMORY QUERY AVAILABLE_PHYSICAL_MEMORY)
cmake_host_system_information(RESULT PROCESSOR_DESCRIPTION QUERY PROCESSOR_DESCRIPTION)
cmake_host_system_information(RESULT OS_PLATFORM QUERY OS_PLATFORM)

message("")
message("-- CMake build environment")
message("===================== Processor =====================")
message("            Name : ${PROCESSOR_NAME}")
message("            Arch : ${CMAKE_SYSTEM_PROCESSOR}")
message("      Core Count : ${NUMBER_OF_PHYSICAL_CORES}")
message("    Thread Count : ${NUMBER_OF_LOGICAL_CORES}")
message("====================== Memory ======================")
message("  Virtual Memory : ${TOTAL_VIRTUAL_MEMORY} MB, ${AVAILABLE_VIRTUAL_MEMORY} MB available")
message(" Physical Memory : ${TOTAL_PHYSICAL_MEMORY} MB, ${AVAILABLE_PHYSICAL_MEMORY} MB available")
message("================= Operating System =================")
message("         OS Name : ${CMAKE_SYSTEM_NAME}")
message("         Version : ${CMAKE_SYSTEM_VERSION}")
message("        Platform : ${OS_PLATFORM}")
message("====================== CMake ======================")
message("    C++ Standard : ${CMAKE_CXX_STANDARD}")
MESSAGE("Output Directory : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message("")
cmake_minimum_required(VERSION 3.23)
project(CPUStress)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS " -static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include(MakeEnvironment.cmake)

# Common method
add_subdirectory(environment)
add_subdirectory(stress)

# Lists
list(APPEND executable-src main.cpp exit_code.h)
list(APPEND libraries environment stress)

# Extra content for Windows
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

    # Token from https://github.com/KDAB/GammaRay/issues/458#issuecomment-337830420
    if (${MSVC})
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO")
        set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /MANIFEST:NO")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO")
    endif ()

    # WinRing0 accessing methods
    list(
            APPEND executable-src
            winring0/winring0.cpp winring0/winring0.h
            winring0/winring0_dlls.cpp winring0/winring0_dlls.h
            CPUStress.manifest
    )

    # CMakeRC.cmake for including WinRing0 dll with sys
    include(CMakeRC.cmake)
    cmrc_add_resource_library(
            winring0dll NAMESPACE winring0dll
            WHENCE winring0/lib
            PREFIX winring0
            winring0/lib/WinRing0.dll winring0/lib/WinRing0x64.dll
            winring0/lib/WinRing0.sys winring0/lib/WinRing0x64.sys
    )
    list(APPEND libraries winring0dll)

endif ()

add_executable(CPUStress ${executable-src})
target_link_libraries(CPUStress PRIVATE ${libraries})
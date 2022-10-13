#include "winring0_dlls.h"

#include <iostream>
#include <filesystem>
namespace filesystem = std::filesystem;
using filesystem::exists;

#include "cmrc/cmrc.hpp"
CMRC_DECLARE(winring0);
using cmrc::winring0::get_filesystem;

#include "winring0.h"

#define CMRC_RES_WIN_RING0 "lib/WinRing0.dll"
#define CMRC_RES_WIN_RING0_X64 "lib/WinRing0x64.dll"

#define DLL_FILE_OPEN_MODE "wb+"
void write_dll_to_file(FILE *, char *, const char *);

void copy_win_ring0_dlls() {
    if (!exists(WIN_RING0)) {
        auto win_ring0 = get_filesystem().open(CMRC_RES_WIN_RING0);
        if (win_ring0.size()) {
            write_dll_to_file(
                    fopen(WIN_RING0, DLL_FILE_OPEN_MODE),
                    (char *) win_ring0.begin(),
                    win_ring0.end()
            );
        }
    }
    if (!exists(WIN_RING0_X64)) {
        auto win_ring0_x64 = get_filesystem().open(CMRC_RES_WIN_RING0_X64);
        if (win_ring0_x64.size()) {
            write_dll_to_file(
                    fopen(WIN_RING0_X64, DLL_FILE_OPEN_MODE),
                    (char *) win_ring0_x64.begin(),
                    win_ring0_x64.end()
            );
        }
    }
}

void write_dll_to_file(FILE *output_file, char *file_begin, const char *file_end) {
    for (; file_begin < file_end;) {
        fputc(*file_begin++, output_file);
    }
    fflush(output_file);
    fclose(output_file);
}
#include "winring0_dlls.h"

#include <iostream>
#include <filesystem>
namespace filesystem = std::filesystem;
using filesystem::exists;
using filesystem::path;
#include <sstream>
using std::stringstream;

#include "cmrc/cmrc.hpp"
CMRC_DECLARE(winring0);
using cmrc::winring0::get_filesystem;

#include "winring0.h"

#define CMRC_RES_WIN_RING0 "lib/WinRing0.dll"
#define CMRC_RES_WIN_RING0_X64 "lib/WinRing0x64.dll"

#define WIN_RING0_SYS "WinRing0.sys"
#define WIN_RING0_X64_SYS "WinRing0x64.sys"
#define CMRC_RES_WIN_RING0_SYS "lib/WinRing0.sys"
#define CMRC_RES_WIN_RING0_X64_SYS "lib/WinRing0x64.sys"

#define DLL_FILE_OPEN_MODE "wb+"
void write_dll_to_file(const char *, char *, const char *);

void copy_win_ring0_dlls(const string &executable_dir) {

    auto output_file = executable_dir + char(path::preferred_separator) + WIN_RING0;
    if (!exists(output_file)) {
        auto win_ring0 = get_filesystem().open(CMRC_RES_WIN_RING0);
        if (win_ring0.size()) {
            write_dll_to_file(output_file.c_str(), (char *) win_ring0.begin(),win_ring0.end());
        }
    }

    output_file = executable_dir + char(path::preferred_separator) + WIN_RING0_SYS;
    if (!exists(output_file)) {
        auto win_ring0 = get_filesystem().open(CMRC_RES_WIN_RING0_SYS);
        if (win_ring0.size()) {
            write_dll_to_file(output_file.c_str(), (char *) win_ring0.begin(), win_ring0.end());
        }
    }

    output_file = executable_dir + char(path::preferred_separator) + WIN_RING0_X64;
    if (!exists(output_file)) {
        auto win_ring0_x64 = get_filesystem().open(CMRC_RES_WIN_RING0_X64);
        if (win_ring0_x64.size()) {
            write_dll_to_file(output_file.c_str(), (char *) win_ring0_x64.begin(), win_ring0_x64.end());
        }
    }

    output_file = executable_dir + char(path::preferred_separator) + WIN_RING0_X64_SYS;
    if (!exists(output_file)) {
        auto win_ring0 = get_filesystem().open(CMRC_RES_WIN_RING0_X64_SYS);
        if (win_ring0.size()) {
            write_dll_to_file(output_file.c_str(), (char *) win_ring0.begin(), win_ring0.end());
        }
    }
}

void write_dll_to_file(const char *output_file_path, char *file_begin, const char *file_end) {
    auto output_file = fopen(output_file_path, DLL_FILE_OPEN_MODE);
    for (; file_begin < file_end;) {
        fputc(*file_begin++, output_file);
    }
    fflush(output_file);
    fclose(output_file);
}
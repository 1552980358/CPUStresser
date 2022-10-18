#include "process_privilege_util.h"

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(__MINGW32__)

#ifdef _MSC_VER
#include <ShlObj.h>
#else
#include <shlobj.h>
#endif

bool check_privilege_elevated() {
    return IsUserAnAdmin();
}

#elif defined(__linux__) || defined(linux) || defined(__linux) || defined(unix) || defined(__unix) || defined(__unix__)

#include <unistd.h>

bool check_privilege_elevated() {
    return getuid() == 0 && geteuid() == 0;
}

#endif
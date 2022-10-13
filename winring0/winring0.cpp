//-----------------------------------------------------------------------------
//     Author : hiyohiyo
//       Mail : hiyohiyo@crystalmark.info
//        Web : http://openlibsys.org/
//    License : The modified BSD license
//
//                     Copyright 2007-2009 OpenLibSys.org. All rights reserved.
//-----------------------------------------------------------------------------
// for WinRing0 1.3.x

//-----------------------------------------------------------------------------
//  Modified Author : 1552980358
//              Web : https://github.com/1552980358
//-----------------------------------------------------------------------------

#include "winring0.h"

#ifdef _WIN64
#define WIN_RING0_LIB WIN_RING0_X64
#else
#ifdef _WIN32
#define WIN_RING0_LIB WIN_RING0
#endif
#endif

HINSTANCE win_ring0_dll = nullptr;

void load_win_ring0() {
    if (!win_ring0_dll) {
        win_ring0_dll = ::LoadLibrary(WIN_RING0_LIB);
    }
}

#define GET_DLL_STATUS "GetDllStatus"
typedef DWORD WINAPI (*GetDllStatus)();
DWORD WINAPI get_dll_status() {
    load_win_ring0();
    return ((GetDllStatus) GetProcAddress(win_ring0_dll, GET_DLL_STATUS))();
}

typedef DWORD WINAPI (*VERSION_METHOD)(PBYTE, PBYTE, PBYTE, PBYTE);

#define GET_DLL_VERSION "GetDllVersion"
typedef VERSION_METHOD GetDllVersion;
DWORD WINAPI get_dll_version(PBYTE major, PBYTE minor, PBYTE revision, PBYTE release) {
    load_win_ring0();
    return ((GetDllVersion) GetProcAddress(win_ring0_dll, GET_DLL_VERSION))(
            major, minor, revision, release
            );
}

#define GET_DRIVER_VERSION "GetDriverVersion"
typedef VERSION_METHOD GetDriverVersion;
DWORD WINAPI get_driver_version(PBYTE major, PBYTE minor, PBYTE revision, PBYTE release) {
    load_win_ring0();
    return ((GetDriverVersion) GetProcAddress(win_ring0_dll, GET_DRIVER_VERSION))(
            major, minor, revision, release
            );
}

typedef BOOL WINAPI (*BOOL_METHOD)();

#define GET_DRIVER_TYPE "GetDriverType"
typedef BOOL_METHOD GetDriverType;
DWORD WINAPI get_driver_type() {
    load_win_ring0();
    return ((GetDriverType) GetProcAddress(win_ring0_dll, GET_DRIVER_TYPE))();
}

#define INITIALIZE_OLS "InitializeOls"
typedef BOOL_METHOD InitializeOls;
BOOL WINAPI initialize_ols() {
    load_win_ring0();
    return ((InitializeOls) GetProcAddress(win_ring0_dll, INITIALIZE_OLS))();
}

//-----------------------------------------------------------------------------
// IsCpuid
//-----------------------------------------------------------------------------
#define IS_CPUID "IsCpuid"
typedef BOOL_METHOD IsCpuid;
BOOL WINAPI is_cpuid() {
    load_win_ring0();
    return ((IsCpuid) GetProcAddress(win_ring0_dll, IS_CPUID))();
}

//-----------------------------------------------------------------------------
// IsMsr
//-----------------------------------------------------------------------------
#define IS_MSR "IsMsr"
typedef BOOL_METHOD IsMsr;
BOOL WINAPI is_msr() {
    load_win_ring0();
    return ((IsMsr) GetProcAddress(win_ring0_dll, IS_MSR))();
}

#define IS_TSC "IsTsc"
typedef BOOL_METHOD IsTsc;
BOOL WINAPI is_tsc() {
    load_win_ring0();
    return ((IsTsc) GetProcAddress(win_ring0_dll, IS_TSC))();
}

#define RDMSR "Rdmsr"
typedef BOOL WINAPI (*Rdmsr)(DWORD, PDWORD, PDWORD);
BOOL WINAPI rdmsr(DWORD index, PDWORD eax, PDWORD edx) {
    return ((Rdmsr) GetProcAddress(win_ring0_dll, RDMSR))(index, eax, edx);
}

#define RDMSR_TX "RdmsrTx"
typedef BOOL WINAPI (*RdmsrTx)(DWORD, PDWORD, PDWORD, DWORD_PTR);
BOOL WINAPI rdmsr_tx(DWORD index, PDWORD eax, PDWORD edx, DWORD_PTR threadAffinityMask) {
    return ((RdmsrTx) GetProcAddress(win_ring0_dll, RDMSR))(index, eax, edx, threadAffinityMask);
}
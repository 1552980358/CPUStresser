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

template<typename MethodPointer>
MethodPointer get_method(LPCSTR lpProcName) {
    return (MethodPointer) GetProcAddress(win_ring0_dll, lpProcName);
}

#define GET_DLL_STATUS "GetDllStatus"
typedef DWORD WINAPI (*GetDllStatus)();
DWORD WINAPI get_dll_status() {
    load_win_ring0();
    return get_method<GetDllStatus>(GET_DLL_STATUS)();
}

typedef DWORD WINAPI (*VERSION_METHOD)(PBYTE, PBYTE, PBYTE, PBYTE);

#define GET_DLL_VERSION "GetDllVersion"
typedef VERSION_METHOD GetDllVersion;
DWORD WINAPI get_dll_version(PBYTE major, PBYTE minor, PBYTE revision, PBYTE release) {
    load_win_ring0();
    return get_method<GetDllVersion>(GET_DLL_VERSION)(major, minor, revision, release);
}

#define GET_DRIVER_VERSION "GetDriverVersion"
typedef VERSION_METHOD GetDriverVersion;
DWORD WINAPI get_driver_version(PBYTE major, PBYTE minor, PBYTE revision, PBYTE release) {
    load_win_ring0();
    return get_method<GetDriverVersion>(GET_DRIVER_VERSION)(major, minor, revision, release);
}

typedef BOOL WINAPI (*BOOL_METHOD)();

#define GET_DRIVER_TYPE "GetDriverType"
typedef BOOL_METHOD GetDriverType;
DWORD WINAPI get_driver_type() {
    load_win_ring0();
    return get_method<GetDriverType>(GET_DRIVER_TYPE)();
}

#define INITIALIZE_OLS "InitializeOls"
typedef BOOL_METHOD InitializeOls;
BOOL WINAPI initialize_ols() {
    load_win_ring0();
    return get_method<InitializeOls>(INITIALIZE_OLS)();
}

#define IS_CPUID "IsCpuid"
typedef BOOL_METHOD IsCpuid;
BOOL WINAPI is_cpuid() {
    load_win_ring0();
    return get_method<IsCpuid>(IS_CPUID)();
}

#define IS_MSR "IsMsr"
typedef BOOL_METHOD IsMsr;
BOOL WINAPI is_msr() {
    load_win_ring0();
    return get_method<IsMsr>(IS_MSR)();
}

#define IS_TSC "IsTsc"
typedef BOOL_METHOD IsTsc;
BOOL WINAPI is_tsc() {
    load_win_ring0();
    return get_method<IsTsc>(IS_TSC)();
}

typedef BOOL WINAPI (*RD_METHOD)(DWORD, PDWORD, PDWORD);
typedef BOOL WINAPI (*RD_METHOD_TX_PX)(DWORD, PDWORD, PDWORD, DWORD_PTR);

typedef BOOL WINAPI (*WR_METHOD)(DWORD, DWORD, DWORD);
typedef BOOL WINAPI (*WR_METHOD_TX_PX)(DWORD, DWORD, DWORD, DWORD_PTR);

#define RDMSR "Rdmsr"
typedef RD_METHOD Rdmsr;
BOOL WINAPI rdmsr(DWORD index, PDWORD eax, PDWORD edx) {
    return get_method<Rdmsr>(RDMSR)(index, eax, edx);
}

#define RDMSR_TX "RdmsrTx"
typedef RD_METHOD_TX_PX RdmsrTx;
BOOL WINAPI rdmsr_tx(DWORD index, PDWORD eax, PDWORD edx, DWORD_PTR thread_affinity_mask) {
    return get_method<RdmsrTx>(RDMSR_TX)(index, eax, edx, thread_affinity_mask);
}

#define RDMSR_PX "RdmsrPx"
typedef RD_METHOD_TX_PX RdmsrPx;
BOOL WINAPI rdmsr_px(DWORD index, PDWORD eax, PDWORD edx, DWORD_PTR process_affinity_mask) {
    return get_method<RdmsrPx>(RDMSR_PX)(index, eax, edx, process_affinity_mask);
}

#define WRMSR "Wrmsr"
typedef WR_METHOD Wrmsr;
BOOL WINAPI wrmsr(DWORD index, DWORD eax, DWORD edx) {
    return get_method<Wrmsr>(WRMSR)(index, eax, edx);
}

#define WRMSR_TX "WrmsrTx"
typedef WR_METHOD_TX_PX WrmsrTx;
BOOL WINAPI wrmsr_tx(DWORD index, DWORD eax, DWORD edx, DWORD_PTR thread_affinity_mask) {
    return get_method<WrmsrTx>(WRMSR_TX)(index, eax, edx, thread_affinity_mask);
}

#define WRMSR_PX "WrmsrPx"
typedef WR_METHOD_TX_PX WrmsrPx;
BOOL WINAPI wrmsr_px(DWORD index, DWORD eax, DWORD edx, DWORD_PTR process_affinity_mask) {
    return get_method<WrmsrPx>(WRMSR_PX)(index, eax, edx, process_affinity_mask);
}

#define RDPMC "Rdpmc"
typedef RD_METHOD Rdpmc;
BOOL WINAPI rdpmc(DWORD index, PDWORD eax, PDWORD edx) {
    return get_method<Rdpmc>(RDPMC)(index, eax, edx);
}

#define RDPMC_TX "RdpmcTx"
typedef RD_METHOD_TX_PX RdpmcTx;
BOOL WINAPI rdpmc_tx(DWORD index, PDWORD eax, PDWORD edx, DWORD_PTR thread_affinity_mask) {
    return get_method<RdpmcTx>(RDPMC_TX)(index, eax, edx, thread_affinity_mask);
}

#define RDPMC_PX "RdpmcPx"
typedef RD_METHOD_TX_PX RdpmcPx;
BOOL WINAPI rdpmc_px(DWORD index, PDWORD eax, PDWORD edx, DWORD_PTR process_affinity_mask) {
    return get_method<RdpmcPx>(RDPMC_PX)(index, eax, edx, process_affinity_mask);
}

#define CPUID "Cpuid"
typedef BOOL WINAPI (*Cpuid)(DWORD, PDWORD, PDWORD, PDWORD, PDWORD);
BOOL WINAPI cpuid(DWORD index, PDWORD eax, PDWORD ebx, PDWORD ecx, PDWORD edx) {
    return get_method<Cpuid>(CPUID)(index, eax, ebx, ecx, edx);
}

typedef BOOL WINAPI (*CPUID_TX_PX)(DWORD, PDWORD, PDWORD, PDWORD, PDWORD, DWORD_PTR);

#define CPUID_TX "CpuidTx"
typedef CPUID_TX_PX CpuidTx;
BOOL WINAPI cpuid_tx(
        DWORD index,
        PDWORD eax, PDWORD ebx, PDWORD ecx, PDWORD edx,
        DWORD_PTR thread_affinity_mask
        ) {
    return get_method<CpuidTx>(CPUID_TX)(index, eax, ebx, ecx, edx, thread_affinity_mask);
}

#define CPUID_PX "CpuidPx"
typedef CPUID_TX_PX CpuidPx;
BOOL WINAPI cpuid_px(
        DWORD index,
        PDWORD eax, PDWORD ebx, PDWORD ecx, PDWORD edx,
        DWORD_PTR process_affinity_mask
        ) {
    return get_method<CpuidPx>(CPUID_PX)(index, eax, ebx, ecx, edx, process_affinity_mask);
}

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

template<typename method_ptr>
method_ptr get_method(LPCSTR lpProcName) {
    return (method_ptr) GetProcAddress(win_ring0_dll, lpProcName);
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

#define RDTSC "Rdtsc"
typedef BOOL WINAPI (*Rdtsc)(PDWORD, PDWORD);
BOOL WINAPI rdtsc(PDWORD eax, PDWORD edx) {
    return get_method<Rdtsc>(RDTSC)(eax, edx);
}

typedef BOOL WINAPI (*RDTSC_TX_PX)(PDWORD, PDWORD, DWORD_PTR);

#define RDTSC_TX "RdtscTx"
typedef RDTSC_TX_PX RdtscTx;
BOOL WINAPI rdtsc_tx(PDWORD eax, PDWORD edx, DWORD_PTR thread_affinity_mask) {
    return get_method<RdtscTx>(RDTSC_TX)(eax, edx, thread_affinity_mask);
}

#define RDTSC_PX "RdtscPx"
typedef RDTSC_TX_PX RdtscPx;
BOOL WINAPI rdtsc_px(PDWORD eax, PDWORD edx, DWORD_PTR process_affinity_mask) {
    return get_method<RdtscPx>(RDTSC_PX)(eax, edx, process_affinity_mask);
}

#define HLT "Hlt"
typedef BOOL_METHOD Hlt;
BOOL WINAPI hlt() {
    return get_method<Hlt>(HLT)();
}

typedef BOOL WINAPI (*HLT_TX_PX)(DWORD_PTR);

#define HLT_TX "HltTx"
typedef HLT_TX_PX HltTx;
BOOL WINAPI hlt_tx(DWORD_PTR thread_affinity_mask) {
    return get_method<HltTx>(HLT_TX)(thread_affinity_mask);
}

#define HLT_PX "HltPx"
typedef HLT_TX_PX HltPx;
BOOL WINAPI hlt_px(DWORD_PTR process_affinity_mask) {
    return get_method<HltPx>(HLT_PX)(process_affinity_mask);
}

#define READ_IO_PORT_BYTE "ReadIoPortByte"
typedef BYTE WINAPI (*ReadIoPortByte)(WORD);
BYTE WINAPI read_io_port_byte(WORD port) {
    return get_method<ReadIoPortByte>(READ_IO_PORT_BYTE)(port);
}

#define READ_IO_PORT_WORD "ReadIoPortWord"
typedef WORD WINAPI (*ReadIoPortWord)(WORD);
WORD WINAPI read_io_oort_word(WORD port) {
    return get_method<ReadIoPortWord>(READ_IO_PORT_WORD)(port);
}

#define READ_IO_PORT_DWORD "ReadIoPortDword"
typedef DWORD WINAPI (*ReadIoPortDword)(WORD);
DWORD WINAPI read_io_oort_dword(WORD port) {
    return get_method<ReadIoPortDword>(READ_IO_PORT_DWORD)(port);
}

#define READ_IO_PORT_BYTE_EX "ReadIoPortByteEx"
typedef BOOL WINAPI (*ReadIoPortByteEx)(WORD, PBYTE);
BOOL WINAPI read_io_port_byte_ex(WORD port, PBYTE value) {
    return get_method<ReadIoPortByteEx>(READ_IO_PORT_BYTE_EX)(port, value);
}

#define READ_IO_PORT_EX "ReadIoPortWordEx"
typedef BOOL WINAPI (*ReadIoPortWordEx)(WORD, PWORD);
BOOL WINAPI read_io_port_word_ex(WORD port, PWORD value) {
    return get_method<ReadIoPortWordEx>(READ_IO_PORT_EX)(port, value);
}

#define READ_IO_PORT_DWORD_EX "ReadIoPortDwordEx"
typedef BOOL WINAPI(*ReadIoPortDwordEx)(WORD, PDWORD);
BOOL WINAPI read_io_port_dword_ex(WORD port, PDWORD value) {
    return get_method<ReadIoPortDwordEx>(READ_IO_PORT_DWORD_EX)(port, value);
}

#define WRITE_IO_PORT_BYTE "WriteIoPortByte"
typedef VOID WINAPI(*WriteIoPortByte)(WORD, BYTE);
VOID WINAPI write_io_port_byte(WORD port, BYTE value) {
    return get_method<WriteIoPortByte>(WRITE_IO_PORT_BYTE)(port, value);
}

#define WRITE_IO_PORT_DWORD "WriteIoPortDword"
typedef VOID WINAPI(*WriteIoPortDword)(WORD, BYTE);
VOID WINAPI write_io_port_dword(WORD port,DWORD value) {
    return get_method<WriteIoPortDword>(WRITE_IO_PORT_DWORD)(port, value);
}

#define WRITE_IO_PORT_WORD "WriteIoPortWord"
typedef VOID WINAPI(*WriteIoPortWord)(WORD, BYTE);
VOID WINAPI write_io_port_word(WORD port, WORD value) {
    return get_method<WriteIoPortWord>(WRITE_IO_PORT_WORD)(port, value);
}

#define WRITE_IO_PORT_BYTE_EX "WriteIoPortByteEx"
typedef BOOL WINAPI(*WriteIoPortByteEx)(WORD, BYTE);
BOOL WINAPI write_io_port_byte_ex(WORD port, BYTE value) {
    return get_method<WriteIoPortByteEx>(WRITE_IO_PORT_BYTE_EX)(port, value);
}

#define WRITE_IO_PORT_WORD_EX "WriteIoPortWordEx"
typedef BOOL WINAPI(*WriteIoPortWordEx)(WORD, BYTE);
BOOL WINAPI write_io_port_word_ex(WORD port, WORD value) {
    return get_method<WriteIoPortWordEx>(WRITE_IO_PORT_WORD_EX)(port, value);
}

#define WRITE_IO_PORT_DWORD_EX "WriteIoPortDwordEx"
typedef BOOL WINAPI(*WriteIoPortDwordEx)(WORD, BYTE);
BOOL WINAPI write_io_port_dword_ex(WORD port, DWORD value) {
    return get_method<WriteIoPortDwordEx>(WRITE_IO_PORT_DWORD_EX)(port, value);
}

#define SET_PCI_MAX_BUS_INDEX "SetPciMaxBusNo"
typedef VOID WINAPI (*SetPciMaxBusNo)(BYTE);
VOID WINAPI set_pci_max_bus_index(BYTE max) {
    return get_method<SetPciMaxBusNo>(SET_PCI_MAX_BUS_INDEX)(max);
}

#define READ_PCI_CONFIG_BYTE "ReadPciConfigByte"
typedef BYTE WINAPI(*ReadPciConfigByte)(DWORD, BYTE);
BYTE WINAPI read_pci_config_byte(DWORD pci_address, BYTE reg_address) {
    return get_method<ReadPciConfigByte>(READ_PCI_CONFIG_BYTE)(pci_address, reg_address);
}

#define READ_PCI_CONFIG_WORD "ReadPciConfigWord"
typedef WORD WINAPI(*ReadPciConfigWord)(DWORD, BYTE);
WORD WINAPI read_pci_config_word(DWORD pci_address, BYTE reg_address) {
    return get_method<ReadPciConfigWord>(READ_PCI_CONFIG_WORD)(pci_address, reg_address);
}

#define READ_PCI_CONFIG_DWORD "ReadPciConfigDword"
typedef DWORD WINAPI(*ReadPciConfigDword)(DWORD, BYTE);
DWORD WINAPI read_pci_config_dword(DWORD pci_address, BYTE reg_address) {
    return get_method<ReadPciConfigDword>(READ_PCI_CONFIG_DWORD)(pci_address, reg_address);
}

#define READ_PCI_CONFIG_BYTE_EX "ReadPciConfigByteEx"
typedef BOOL WINAPI(*ReadPciConfigByteEx)(DWORD, DWORD, PBYTE);
BOOL WINAPI read_pci_config_byte_ex(DWORD pci_address, DWORD reg_address, PBYTE value) {
    return get_method<ReadPciConfigByteEx>(READ_PCI_CONFIG_BYTE_EX)(pci_address, reg_address, value);
}

#define READ_PCI_CONFIG_WORD_EX "ReadPciConfigWordEx"
typedef BOOL WINAPI(*ReadPciConfigWordEx)(DWORD, DWORD, PWORD);
BOOL WINAPI read_pci_config_word_ex(DWORD pci_address, DWORD reg_address, PWORD value) {
    return get_method<ReadPciConfigWordEx>(READ_PCI_CONFIG_WORD_EX)(pci_address, reg_address, value);
}

#define READ_PCI_CONFIG_DWORD_EX "ReadPciConfigDwordEx"
typedef BOOL WINAPI(*ReadPciConfigDwordEx)(DWORD, DWORD, PDWORD);
BOOL WINAPI read_pci_config_dword_ex(DWORD pci_address, DWORD reg_address, PDWORD value) {
    return get_method<ReadPciConfigDwordEx>(READ_PCI_CONFIG_DWORD_EX)(pci_address, reg_address, value);
}

#define WRITE_PCI_CONFIG_BYTE "WritePciConfigByte"
typedef VOID WINAPI(*WritePciConfigByte)(DWORD, BYTE, BYTE);
VOID WINAPI write_pci_config_byte(DWORD pci_address, BYTE reg_address, BYTE value) {
    return get_method<WritePciConfigByte>(WRITE_PCI_CONFIG_BYTE)(pci_address, reg_address, value);
}

#define WRITE_PCI_CONFIG_WORD "WritePciConfigWord"
typedef VOID WINAPI(*WritePciConfigWord)(DWORD, BYTE, DWORD);
VOID WINAPI write_pci_config_word(DWORD pci_address, BYTE reg_address, WORD value) {
    return get_method<WritePciConfigWord>(WRITE_PCI_CONFIG_WORD)(pci_address, reg_address, value);
}

#define WRITE_PCI_CONFIG_DWORD "WritePciConfigDword"
typedef VOID WINAPI(*WritePciConfigDword)(DWORD, BYTE, DWORD);
VOID WINAPI write_pci_config_dword(DWORD pci_address, BYTE reg_address, DWORD value) {
    return get_method<WritePciConfigDword>(WRITE_PCI_CONFIG_DWORD)(pci_address, reg_address, value);
}

#define WRITE_PCI_CONFIG_BYTE_EX "WritePciConfigByteEx"
typedef BOOL WINAPI(*WritePciConfigByteEx)(DWORD, DWORD, BYTE);
BOOL WINAPI write_pci_config_byte_ex(DWORD pci_address, DWORD reg_address, BYTE value) {
    return get_method<WritePciConfigByteEx>(WRITE_PCI_CONFIG_BYTE_EX)(pci_address, reg_address, value);
}

#define WRITE_PCI_CONFIG_WORD_EX "WritePciConfigWordEx"
typedef BOOL WINAPI(*WritePciConfigWordEx)(DWORD, DWORD, WORD);
BOOL WINAPI write_pci_config_word_ex(DWORD pci_address, DWORD reg_address, WORD value) {
    return get_method<WritePciConfigWordEx>(WRITE_PCI_CONFIG_WORD_EX)(pci_address, reg_address, value);
}

#define WRITE_PCI_CONFIG_DWORD_EX "WritePciConfigDwordEx"
typedef BOOL WINAPI(*WritePciConfigDwordEx)(DWORD, DWORD, DWORD);
BOOL WINAPI write_pci_config_dword_ex(DWORD pci_address, DWORD reg_address, DWORD value) {
    return get_method<WritePciConfigDwordEx>(WRITE_PCI_CONFIG_DWORD_EX)(pci_address, reg_address, value);
}

#define FIND_PCI_DEVICE_BY_ID "FindPciDeviceById"
typedef DWORD WINAPI(*FindPciDeviceById)(WORD, WORD, BYTE);
DWORD WINAPI find_pci_device_by_id(WORD vendor_id, WORD device_id, BYTE index) {
    return get_method<FindPciDeviceById>(FIND_PCI_DEVICE_BY_ID)(vendor_id, device_id, index);
}

#define FIND_PCI_DEVICE_BY_CLASS "FindPciDeviceByClass"
typedef DWORD WINAPI(*FindPciDeviceByClass)(BYTE, BYTE, BYTE, BYTE);
DWORD WINAPI find_pci_device_by_class(BYTE base_class, BYTE sub_class, BYTE program_interface, BYTE index) {
    return get_method<FindPciDeviceByClass>(FIND_PCI_DEVICE_BY_CLASS)(
            base_class, sub_class, program_interface, index
            );
}
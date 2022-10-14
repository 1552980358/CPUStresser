#ifndef CPUSTRESS_WINRING0_H
#define CPUSTRESS_WINRING0_H

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

#include <windows.h>

#define WIN_RING0 "WinRing0.dll"
#define WIN_RING0_X64 "WinRing0x64.dll"

/******************************************************************************
**
** DLL Information
**
******************************************************************************/

//-----------------------------------------------------------------------------
// GetDllStatus
//-----------------------------------------------------------------------------
DWORD // DLL Status, defined OLS_DLL_****
WINAPI get_dll_status();

//-----------------------------------------------------------------------------
// GetDllVersion
//-----------------------------------------------------------------------------
DWORD // DLL Version, defined OLS_VERSION
WINAPI get_dll_version(
        PBYTE major,		// major version
PBYTE minor,		// minor version
PBYTE revision,		// revision
PBYTE release		// release/build
);

//-----------------------------------------------------------------------------
// GetDriverVersion
//-----------------------------------------------------------------------------
DWORD // Device Driver Version, defined OLS_DRIVER_VERSION
WINAPI get_driver_version(
        PBYTE major,		// major version
PBYTE minor,		// minor version
PBYTE revision,		// revision
PBYTE release		// release/build
);

//-----------------------------------------------------------------------------
// GetDriverType
//-----------------------------------------------------------------------------
DWORD // Device Driver Type, defined OLS_DRIVER_TYPE_****
WINAPI get_driver_type();

//-----------------------------------------------------------------------------
// InitializeOls
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI initialize_ols();

//-----------------------------------------------------------------------------
// DeinitializeOls
//-----------------------------------------------------------------------------
VOID WINAPI deinitialize_ols();

/******************************************************************************
**
** CPU
**
******************************************************************************/

//-----------------------------------------------------------------------------
// IsCpuid
//-----------------------------------------------------------------------------
BOOL // TRUE: support CPUID instruction, FALSE: not support CPUID instruction
WINAPI is_cpuid();

//-----------------------------------------------------------------------------
// IsMsr
//-----------------------------------------------------------------------------
BOOL // TRUE: support MSR(Model-Specific Register), FALSE: not support MSR
WINAPI is_msr();

//-----------------------------------------------------------------------------
// IsTsc
//-----------------------------------------------------------------------------
BOOL // TRUE: support TSC(Time Stamp Counter), FALSE: not support TSC
WINAPI is_tsc();

//-----------------------------------------------------------------------------
// Rdmsr
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI rdmsr(
        DWORD index,					// MSR index
        PDWORD eax,						// bit  0-31
        PDWORD edx						// bit 32-63
);

//-----------------------------------------------------------------------------
// RdmsrTx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI rdmsr_tx(
        DWORD index,					// MSR index
        PDWORD eax,						// bit  0-31
        PDWORD edx,						// bit 32-63
        DWORD_PTR thread_affinity_mask
);

//-----------------------------------------------------------------------------
// RdmsrPx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI rdmsr_px(
        DWORD index,					// MSR index
        PDWORD eax,						// bit  0-31
        PDWORD edx,						// bit 32-63
        DWORD_PTR process_affinity_mask
);

//-----------------------------------------------------------------------------
// Wrmsr
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI wrmsr(
        DWORD index,					// MSR index
        DWORD eax,						// bit  0-31
        DWORD edx						// bit 32-63
);

//-----------------------------------------------------------------------------
// WrmsrTx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI wrmsrTx(
        DWORD index,					// MSR index
        DWORD eax,						// bit  0-31
        DWORD edx,						// bit 32-63
        DWORD_PTR thread_affinity_mask
);

//-----------------------------------------------------------------------------
// WrmsrPx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI wrmsr_px(
        DWORD index,					// MSR index
        DWORD eax,						// bit  0-31
        DWORD edx,						// bit 32-63
        DWORD_PTR process_affinity_mask
);

//-----------------------------------------------------------------------------
// Rdpmc
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI rdpmc(
        DWORD index,					// PMC index
        PDWORD eax,						// bit  0-31
        PDWORD edx						// bit 32-63
);

//-----------------------------------------------------------------------------
// RdmsrTx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI rdpmc_tx(
        DWORD index,					// PMC index
        PDWORD eax,						// bit  0-31
        PDWORD edx,						// bit 32-63
        DWORD_PTR thread_affinity_mask
);

//-----------------------------------------------------------------------------
// RdmsrPx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI rdpmc_px(
        DWORD index,					// PMC index
        PDWORD eax,						// bit  0-31
        PDWORD edx,						// bit 32-63
        DWORD_PTR process_affinity_mask
);

//-----------------------------------------------------------------------------
// Cpuid
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI cpuid(
        DWORD index,					// CPUID index
        PDWORD eax,
        PDWORD ebx,
        PDWORD ecx,
        PDWORD edx
);

//-----------------------------------------------------------------------------
// CpuidTx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI cpuid_tx(
        DWORD index,					// CPUID index
        PDWORD eax,
        PDWORD ebx,
        PDWORD ecx,
        PDWORD edx,
        DWORD_PTR thread_affinity_mask
);

//-----------------------------------------------------------------------------
// CpuidPx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI cpuid_px(
        DWORD index,					// CPUID index
        PDWORD eax,
        PDWORD ebx,
        PDWORD ecx,
        PDWORD edx,
        DWORD_PTR process_affinity_mask
);

//-----------------------------------------------------------------------------
// Rdtsc
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI rdtsc(
        PDWORD eax,						// bit  0-31
    PDWORD edx						// bit 32-63
);

//-----------------------------------------------------------------------------
// RdmsrTx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI rdtsc_tx(
        PDWORD eax,						// bit  0-31
        PDWORD edx,						// bit 32-63
        DWORD_PTR thread_affinity_mask
);

//-----------------------------------------------------------------------------
// RdmsrPx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI rdtsc_px(
        PDWORD eax,						// bit  0-31
        PDWORD edx,						// bit 32-63
        DWORD_PTR process_affinity_mask
);

//-----------------------------------------------------------------------------
// Hlt
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI hlt();

//-----------------------------------------------------------------------------
// HltTx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI hlt_tx(
        DWORD_PTR thread_affinity_mask
);

//-----------------------------------------------------------------------------
// HltPx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI hlt_px(
        DWORD_PTR process_affinity_mask
);

/******************************************************************************
**
** I/O
**
******************************************************************************/

//-----------------------------------------------------------------------------
// ReadIoPortByte
//-----------------------------------------------------------------------------
BYTE // Read Value
WINAPI read_io_port_byte(
        WORD port			// I/O port address
);

//-----------------------------------------------------------------------------
// ReadIoPortWord
//-----------------------------------------------------------------------------
WORD // Read Value
WINAPI read_io_oort_word(
        WORD port			// I/O port address
);

//-----------------------------------------------------------------------------
// ReadIoPortDword
//-----------------------------------------------------------------------------
DWORD // Read Value
WINAPI read_io_oort_dword(
        WORD port			// I/O port address
);

//-----------------------------------------------------------------------------
// ReadIoPortByteEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI read_io_port_byte_ex(
        WORD port,			// I/O port address
        PBYTE value			// Read Value
);
//-----------------------------------------------------------------------------
// ReadIoPortWordEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI read_io_port_word_ex(
        WORD port,			// I/O port address
        PWORD value			// Read Value
);
//-----------------------------------------------------------------------------
// ReadIoPortDwordEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI read_io_port_dword_ex(
        WORD port,			// I/O port address
        PDWORD value		// Read Value
);

//-----------------------------------------------------------------------------
// WriteIoPortByte
//-----------------------------------------------------------------------------
VOID WINAPI write_io_port_byte(
        WORD port,			// I/O port address
        BYTE value			// Write Value
);

//-----------------------------------------------------------------------------
// WriteIoPortDword
//-----------------------------------------------------------------------------
VOID WINAPI write_io_port_dword(
        WORD port,			// I/O port address
        DWORD value			// Write Value
);


//-----------------------------------------------------------------------------
// WriteIoPortWord
//-----------------------------------------------------------------------------
VOID WINAPI write_io_port_word(
        WORD port,			// I/O port address
        WORD value			// Write Value
);

//-----------------------------------------------------------------------------
// WriteIoPortByteEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI write_io_port_byte_ex(
        WORD port,			// I/O port address
        BYTE value			// Write Value
);

//-----------------------------------------------------------------------------
// WriteIoPortWordEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI write_io_port_word_ex(
        WORD port,			// I/O port address
        WORD value			// Write Value
);


//-----------------------------------------------------------------------------
// WriteIoPortDwordEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI write_io_port_dword_ex(
        WORD port,			// I/O port address
        DWORD value			// Write Value
);

/******************************************************************************
**
** PCI
**
******************************************************************************/
// pci_address
//  0- 2: Function Number
//  3- 7: Device Number
//  8-15: PCI Bus Number
// 16-31: Reserved
// 0xFFFFFFFF : Error

//-----------------------------------------------------------------------------
// SetPciMaxBusNo
//-----------------------------------------------------------------------------
VOID WINAPI set_pci_max_bus_index(
        BYTE max			// Max PCI Bus to Scan
);

//-----------------------------------------------------------------------------
// ReadPciConfigByte
//-----------------------------------------------------------------------------
BYTE // Read Value
WINAPI read_pci_config_byte(
        DWORD pci_address,	// PCI Device Address
        BYTE reg_address		// Configuration Address 0-255
);

//-----------------------------------------------------------------------------
// ReadPciConfigWord
//-----------------------------------------------------------------------------
WORD // Read Value
WINAPI read_pci_config_word(
        DWORD pci_address,	// PCI Device Address
        BYTE reg_address		// Configuration Address 0-255
);

//-----------------------------------------------------------------------------
// ReadPciConfigDword
//-----------------------------------------------------------------------------
DWORD // Read Value
WINAPI read_pci_config_dword(
        DWORD pci_address,	// PCI Device Address
        BYTE reg_address		// Configuration Address 0-255
);

//-----------------------------------------------------------------------------
// ReadPciConfigByteEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI read_pci_config_byte_ex(
        DWORD pci_address,	// PCI Device Address
        DWORD reg_address,	// Configuration Address 0-whatever
        PBYTE value			// Read Value
);

//-----------------------------------------------------------------------------
// ReadPciConfigWordEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI read_pci_config_word_ex(
        DWORD pci_address,	// PCI Device Address
        DWORD reg_address,	// Configuration Address 0-whatever
        PWORD value			// Read Value
);

//-----------------------------------------------------------------------------
// ReadPciConfigDwordEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI read_pci_config_dword_ex(
        DWORD pci_address,	// PCI Device Address
        DWORD reg_address,	// Configuration Address 0-whatever
        PDWORD value		// Read Value
);

//-----------------------------------------------------------------------------
// WritePciConfigByte
//-----------------------------------------------------------------------------
VOID WINAPI write_pci_config_byte(
        DWORD pci_address,	// PCI Device Address
        BYTE reg_address,	// Configuration Address 0-255
        BYTE value			// Write Value
);

//-----------------------------------------------------------------------------
// WritePciConfigWord
//-----------------------------------------------------------------------------
VOID WINAPI write_pci_config_word(
        DWORD pci_address,	// PCI Device Address
        BYTE reg_address,	// Configuration Address 0-255
        WORD value			// Write Value
);

//-----------------------------------------------------------------------------
// WritePciConfigDword
//-----------------------------------------------------------------------------
VOID WINAPI write_pci_config_dword(
        DWORD pci_address,	// PCI Device Address
        BYTE reg_address,	// Configuration Address 0-255
        DWORD value			// Write Value
);

//-----------------------------------------------------------------------------
// WritePciConfigByteEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI write_pci_config_byte_ex(
        DWORD pci_address,	// PCI Device Address
        DWORD reg_address,	// Configuration Address 0-whatever
        BYTE value			// Write Value
);

//-----------------------------------------------------------------------------
// WritePciConfigWordEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI write_pci_config_word_ex(
        DWORD pci_address,	// PCI Device Address
        DWORD reg_address,	// Configuration Address 0-whatever
        WORD value			// Write Value
);

//-----------------------------------------------------------------------------
// WritePciConfigDwordEx
//-----------------------------------------------------------------------------
BOOL // TRUE: success, FALSE: failure
WINAPI write_pci_config_dword_ex(
        DWORD pci_address,	// PCI Device Address
        DWORD reg_address,	// Configuration Address 0-whatever
        DWORD value			// Write Value
);

//-----------------------------------------------------------------------------
// FindPciDeviceById
//-----------------------------------------------------------------------------
DWORD // pci_address, 0xFFFFFFFF: failure
WINAPI find_pci_device_by_id(
        WORD vendor_id,		// Vendor ID
        WORD device_id,		// Device ID
        BYTE index			// Index
);

//-----------------------------------------------------------------------------
// FindPciDeviceByClass
//-----------------------------------------------------------------------------
DWORD // pci_address, 0xFFFFFFFF: failure
WINAPI find_pci_device_by_class(
        BYTE base_class,		// Base Class
        BYTE sub_class,		    // Sub Class
        BYTE program_interface,	// Program Interface
        BYTE index			    // Index
);

/******************************************************************************
**
** Memory (Special API)
**
******************************************************************************/

#ifdef _PHYSICAL_MEMORY_SUPPORT
//-----------------------------------------------------------------------------
// ReadDmiMemory
//-----------------------------------------------------------------------------
DWORD // Read size(byte), 0: failure
WINAPI ReadDmiMemory(
	PBYTE buffer,		// Buffer
	DWORD count,		// Count
	DWORD unitSize		// Unit Size (BYTE, WORD, DWORD)
);

//-----------------------------------------------------------------------------
// ReadPhysicalMemory
//-----------------------------------------------------------------------------
DWORD // Read size(byte), 0: failure
WINAPI ReadPhysicalMemory(
	DWORD_PTR address,	// Physical Memory Address
	PBYTE buffer,		// Buffer
	DWORD count,		// Count
	DWORD unitSize		// Unit Size (BYTE, WORD, DWORD)
);

//-----------------------------------------------------------------------------
// WritePhysicalMemory
//-----------------------------------------------------------------------------
DWORD // Write size(byte), 0: failure
WINAPI WritePhysicalMemory(
	DWORD_PTR address,	// Physical Memory Address
	PBYTE buffer,		// Buffer
	DWORD count,		// Count
	DWORD unitSize		// Unit Size (BYTE, WORD, DWORD)
);
#endif

#endif //CPUSTRESS_WINRING0_H

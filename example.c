#include <ntifs.h>
#include <ntdef.h>
#include <wdf.h>
#include "Functions.h"

DRIVER_INITIALIZE DriverEntry;

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT  DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	NTSTATUS status;
	WDF_DRIVER_CONFIG config;

	status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &config, WDF_NO_HANDLE);

	HANDLE ProcessId = 0xEA0;
	DWORD32 Buffer = 1234;
  
	KAPC_STATE apc = AttachProcess(ProcessId);
  status = WriteMemory((PVOID)0x00400000, &Buffer, sizeof(DWORD32), PAGE_READONLY, UserMode);
	DetachProcess(&apc);
  
	return status;
}

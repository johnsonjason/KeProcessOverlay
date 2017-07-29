#ifndef SIGNATURESCAN
#define SIGNATURESCAN

#include <ntifs.h>
#include <ntdef.h>
#include <wdf.h>


typedef struct _Signature
{
	DWORD64 val1;
	DWORD64 val2;
} Signature;

PVOID GetSignatureBase(HANDLE ProcessId, DWORD64 BaseStart, 
		       DWORD64 BaseEnd, Signature ScanSignature, 
		       ULONG PageProtect, SIZE_T RegionSize, ULONG Type)

#endif

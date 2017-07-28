#ifndef SIGNATURESCAN
#define SIGNATURESCAN

typedef struct _Signature
{
	DWORD64 val1;
	DWORD64 val2;
} Signature;

PVOID GetSignatureBase(HANDLE ProcessId, DWORD64 BaseStart, 
		       DWORD64 BaseEnd, Signature ScanSignature, 
		       SIZE_T RegionSize, DWORD32 Type);

#endif

#ifndef FUNCTIONS
#define FUNCTIONS

KAPC_STATE AttachProcess(HANDLE ProcessId);

NTSTATUS WriteMemory(PVOID Destination, PVOID Buffer, SIZE_T BufferSize, ULONG fProtect, KPROCESSOR_MODE ProcessorMode);

NTSTATUS ReadMemory(PVOID Buffer, PVOID MemoryToRead, SIZE_T Size);

void DetachProcess(KAPC_STATE* apc);

#endif

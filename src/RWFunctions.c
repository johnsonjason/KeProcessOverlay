// By jasonfish4

KAPC_STATE AttachProcess(HANDLE ProcessId) // Switch to UM Address Space
{
	KAPC_STATE apc;
	PEPROCESS Process;
	PsLookupProcessByProcessId(ProcessId, &Process); // Get EPROCESS from the Id
	KeStackAttachProcess(Process, &apc); // attach the thread to the usermode address space
	return apc;
}

//Use UserMode as KPROCESSOR_MODE when attaching to a usermode process
NTSTATUS WriteMemory(PVOID Destination, PVOID Buffer, SIZE_T BufferSize, ULONG fProtect, KPROCESSOR_MODE ProcessorMode) // Write memory
{

	PMDL mdl = IoAllocateMdl(Destination, BufferSize, FALSE, FALSE, NULL); // Allocate Memory Descriptor
	// Many MDL functions must be enclosed in a try/except statement
	__try
	{
		MmProbeAndLockPages(mdl, ProcessorMode, IoReadAccess); 
		Destination = MmGetSystemAddressForMdlSafe(mdl, HighPagePriority);

		MmProtectMdlSystemAddress(mdl, PAGE_EXECUTE_READWRITE); // Set the page rights to R/W/X
		RtlCopyMemory(Destination, Buffer, sizeof(DWORD32)); // Write Memory
		MmProtectMdlSystemAddress(mdl, fProtect); // Set back to old page rights
		
		MmUnmapLockedPages(Destination, mdl);
		MmUnlockPages(mdl);
		IoFreeMdl(mdl); // free MDL
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return 1;
	}
	
	return 0;
}

// Read Memory
NTSTATUS ReadMemory(PVOID Buffer, PVOID MemoryToRead, SIZE_T Size)
{
	RtlCopyMemory(MemoryToRead, Buffer, Size); // Copy from src to dest
}


void DetachProcess(KAPC_STATE* apc) // Switch back to KM Address Space
{
	KeUnstackDetachProcess(&apc); // Detach thread from address space
}

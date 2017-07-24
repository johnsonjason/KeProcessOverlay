// By jasonfish4

KAPC_STATE AttachProcess(HANDLE ProcessId) // Switch to UM Address Space
{
	KAPC_STATE apc;
	PEPROCESS Process;
	PsLookupProcessByProcessId(ProcessId, &Process); // Get EPROCESS from the Id
	KeStackAttachProcess(Process, &apc); // attach the thread to the usermode address space
	return apc;
}

NTSTATUS WriteMemory(PVOID Destination, PVOID Buffer, SIZE_T BufferSize, ULONG fProtect)
{

	PMDL mdl = IoAllocateMdl(Destination, BufferSize, FALSE, FALSE, NULL); // Allocate Memory Descriptor
	__try
	{
		MmInitializeMdl(mdl, Destination, BufferSize); 
		MmProbeAndLockPages(mdl, UserMode, IoReadAccess); 
		Destination = MmGetSystemAddressForMdlSafe(mdl, HighPagePriority);

		if (Destination != NULL)
		{
			MmProtectMdlSystemAddress(mdl, PAGE_EXECUTE_READWRITE); // Set the page rights to R/W/X
			RtlCopyMemory(Destination, Buffer, sizeof(DWORD32)); // Write Memory
			MmProtectMdlSystemAddress(mdl, fProtect); // Set back to old page rights
		}
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

NTSTATUS ReadMemory(PVOID Buffer, PVOID MemoryToRead, SIZE_T Size)
{
	RtlCopyMemory(MemoryToRead, Buffer, Size);
}


void DetachProcess(KAPC_STATE* apc) // Switch back to KM Address Space
{
	KeUnstackDetachProcess(&apc);
}

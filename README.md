# KeProcessOverlay
These are just functions that make writing/reading memory in a different process a lot easier, it's by common means using KeStackAttachProcess to attach a kernel mode thread to a usermode address space and then using an MDL and setting the protection rights with MmProtectMdlSystemAddress, this just shortens the code

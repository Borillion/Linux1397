To compile run the command:
    $  gcc read_mem.c -o read_mem

This program opens the /proc/mem_map file contain information about the physical
address of the systems virtual memory map. It also opens /dev/mem with mmap and 
returns a pointer to the first page.

We can check to see this page is flagged as reserved by using we would use 
because mmap returns a virtual address. We could write a second module to handle
this look and transfer of the address from user to kernel memory space.

	#include <asm/io.h>
        virt_addr = phys_to_virt(phys_addr);
 

/* We can check to see this page is flagged as reserved by using we would use 
because mmap returns a virtual address. We could write a second module to handle
this look and transfer of the address from user to kernel memory space.

	#include <asm/io.h>
        virt_addr = phys_to_virt(phys_addr);
*/

#include </usr/include/stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

#define PAGE_SIZE 4096
#define MAP_MASK (PAGE_SIZE-1)

struct page *mem_base = 0;
unsigned long target = 0;

int main(void) {

	int fd;
	FILE * fd_proc;
	int num;

	struct page *mem_base = 0;
	unsigned long  target = 0;


	char proc_line[128];
	
	char *map_base;
	
	fd_proc = fopen("/proc/mem_map", "r" );
	
	fscanf(fd_proc, "%s %s %s %x", &proc_line,  &proc_line, &proc_line, &target);
        printf("%x\n", target);

 	fd = open("/dev/mem", O_RDWR);	

	if(fd == 0){
		perror("Error opening file /dev/mem");
		return -1;
	}

		
	mem_base = mmap(0, PAGE_SIZE, PROT_READ|PROT_WRITE,MAP_SHARED,fd, target&~MAP_MASK);

	if( mem_base == (void *)-1){
		perror("Error mapping");
		return -2;
	}
		
	
	printf("Value in memory page %p\n", map_base);
	
	return 0;
}



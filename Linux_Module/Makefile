
obj-m += memory.o

all:
	make -C /home/babak/code/linux-3.19.5 SUBDIRS=$(PWD) modules
	gcc -o wrMemory wrMemory.c
clean:
	make -C /home/babak/code/linux-3.19.5
	rm wrMemory
 SUBDIRS=$(PWD) clean


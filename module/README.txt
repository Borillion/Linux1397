Read Me
===========
This module was built and tested under linux kernel 3.19.5


Contents
=============
mem_map.c - proc file kernel module source code
Makefile - make file instructions for the compiler

Compilation
===============
Clone linux-3.15.9 from kernel.org and copy the contents
of this directory "module" relative to the kernel.

Example:

─── code
    ├── linux-3.19.5
    └── module
        ├── Makefile
	└── mem_map.c
	
To compile issue: $ make

Module insertion and use:
============================
To load the module into your kernel issue:

$ sudo insmod mem_map.ko
$ dmesg | tail

This should display a message similar to below:

[  247.835157] Loaded mem_map module 

Indicating succsessful insertion

To show kernel mem_map information simply cat the new proc file

$ cat /proc/mem_map

Outputting:
mem_map virt addr: ffffffff81f6d5a8      <---- Beginning virtual memory address of the kernel mem_map structure
mem_map phys addr: 131941395333120       <---- The corresponding physical location in memory
mem_map phys pages: 18446744072101797888 <---- The number of 4 Kb physical memory pages (Intel x86)

Removal
=============
To remove issue $ sudo rmmod mem_map.ko

This should display a message similar to below:

[25829.175534] <1> Proc file unloaded 

Indicating succsessful removal 

Indicating succsessful insertion

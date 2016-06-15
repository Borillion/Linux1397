SRCS = mem_map.c
OBJS = $(SRCS:.c=.o)

obj-m += $(OBJS)

all:
	make -C /home/babak/code/linux-3.19.5 M=$(PWD) modules
clean:
	make -C /home/babak/code/linux-3.19.5 M=$(PWD) clean
	$(RM) Module.markers modules.order


obj-m+=my_module.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) random_n.c -o randomNumber
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm random_n
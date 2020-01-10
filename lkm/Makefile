obj-m += version.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install:
	sudo cp version.rules /etc/udev/rules.d/
	lsmod | grep version > /dev/null && sudo rmmod version || echo -n
	sudo insmod version.ko

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

obj-m += uglyrandom.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	insmod ./uglyrandom.ko
	ls /dev/uglyrandom || mknod /dev/uglyrandom c 42 0
	chmod 777 /dev/uglyrandom

uninstall:
	rmmod uglyrandom

.PHONY: all options clean install uninstall

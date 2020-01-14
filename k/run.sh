#!/bin/bash

if [ "$1" == "debug" ]
then
	qemu-system-i386 -cdrom k.iso -serial stdio -s -S &
	gdb -ix connection.gdb k/k
else
	qemu-system-i386 -cdrom k.iso -serial stdio
fi

#!/bin/sh
sudo apt-get install gcc-3.4 libsdl1.2debian-all libsdl1.2-dev zlib1g-dev
wget http://fabrice.bellard.free.fr/qemu/qemu-0.9.0.tar.gz
tar zxf qemu-0.9.0.tar.gz 
cd qemu-0.9.0/
./configure --cc=/usr/bin/gcc-3.4 --host-cc=/usr/bin/gcc-3.4 --target-list=arm-softmmu
make

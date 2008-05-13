=====================
Lab 4 製作 bootloader
=====================

.. 目前還在嘗試用QEMU跑 uboot 的方法，因此這次實驗內容還不確定

1. 什麼是 bootloader
====================

2. 使用 bootloader
==================

2.1 下載 u-boot
---------------
::

  #下載u-boot的source code
  wget http://jaist.dl.sourceforge.net/sourceforge/u-boot/u-boot-1.1.6.tar.bz2
  #解壓縮
  tar jxf u-boot-1.1.6.tar.bz2


2.2 編譯 u-boot
---------------
::

  make cp920t_config
  make CROSS_COMPILE = arm-linux- 


2.3 用 QEMU 執行
----------------
::

  <QEMU>/arm-softmmu/qemu-system-arm -kernel <U-BOOT> \
          -initrd <ARM_TEST>/arm_root.img -nographic -append "console=ttyAMA0"

.. note::
   - <QEMU> = qemu 的根目錄 （如 qemu-0.9.1/ ）
   - <U-BOOT> = 的位置 （如 u-boot-1.1.6/u-boot.bin）
   - <ARM_TEST> = arm-test 的位置


3. 載入 kernel
==================

3.1 把 kernel 轉成 uImage 格式
------------------------------
(u-boot 用的image格式稱為uImage)
::

    -objcopy -O binary -R .note -R .comment -S linux/arch/arm/boot/compressed/vmlinux linux.bin 

    gzip -9 linux.bin 

    (u-boot)/tools/mkimage -A arm -O linux -T kernel -C gzip \
    -a 0x0008000 -e 0x0008000 -n "(kernel name)" -d linux.bin.gz ./uImage


3.2 tftp 相關設置
-----------------

本機端
::

    /etc/init.d/tftpd start

u-boot
::

    #設置 host 端 IP
    <uboot> setenv serverip 192.168.0.1
    #設置 guest 端 IP
    <uboot> setenv ipaddr 192.168.0.2


3.3 載入 kernel 並啟動
----------------------
**卡在這個步驟**
::

    #抓kernel
    <uboot> tftp 100000 uImage
    #boot kernel
    <uboot> bootm 100000


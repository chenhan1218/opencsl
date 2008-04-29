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





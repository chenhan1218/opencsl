=====================
Lab 8 device driver
=====================

Driver 是程式和硬體元件溝通的橋樑。本次實驗將介紹在 Linux 中撰寫/使用 driver 的兩種方法，並另外補充關於 module 、 device 的基本知識。

1. 什麼是 device driver
========================

1.1 device driver
------------------
Device driver 是介於實體設備與程式間的橋樑，它是 kernel 的一部分，user program 可以透過 driver 來使用實體設備。 Driver 大致可以分為 Block Device Driver 和 Character Device Driver，前者每次會傳輸固定的資料量，而後者的資料量則不需固定。

1.2 device
-----------
在 Linux 中，所有的設備都是一個檔案，每個檔案都有自己特殊的編號和型態，我們可以在 /dev 中找到目前系統所有的 device ，這些 device 不一定是實際存在的硬體，也有可能是以虛擬的方式掛載上去的。例如，如果想要了解目前系統中總共有多少的 SATA 硬碟以及分割區，可以在終端機下鍵入：

::

  ls -l /dev/sd*

如果想知道更多關於 device 、 device driver 的資訊，可以參考 Wikipedia [#]_ 。

.. [#] 
  device : http://en.wikipedia.org/wiki/Device_node

  device driver: http://en.wikipedia.org/wiki/Device_driver

2. 撰寫 driver
===============

2.1 driver 程式的基本結構
-------------------------

Driver 作為程式和元件之間的橋樑，它必須提供一些基本的使用介面，如讀、寫或是其他控制元件的指令，本節將介紹撰寫一個 driver 所需的最基本架構。

Driver 主要由兩部份構成：初始化、結束元件以及使用元件。Driver 在初始化以及結束使用元件時必須向系統註冊或釋放元件；而在使用元件方面，Linux提供一個統一的 structure 來描述對元件的控制指令，分別定義了read、write、ioctl（IO control）、open 以及 release 五個函式的 function pointer，讓系統知道每個 driver 要用到的 function 分別是哪些。

2.2 撰寫 driver 程式
---------------------

以下分三段介紹 driver 程式的內容，原始的程式碼請到 data/demo.c 下載。

1. 引入標頭檔

   在撰寫 driver 前必須先 include 一些標頭檔：

   ::

     #include <linux/init.h>
     #include <linux/kernel.h>
     #include <linux/module.h>
     #include <linux/fs.h>

2. 撰寫控制元件的函式

   struct file_operations 即為定義各個 function pointer 的 structure。

   ::

    static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos)
     {
        printk("device read\n");
        return count;
     }

     static ssize_t drv_write(struct file *filp, const char *buf, size_t count, loff_t *ppos) 
     {	
        printk("device write\n");
        return count;
     }

     static int drv_open(struct inode *inode, struct file *filp)
     {
        printk("device open\n");
        return 0;
     }

     int drv_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg) 
     {
        printk("device ioctl\n");
        return 0;
     }

     static int drv_release(struct inode *inode, struct file *filp)
     {
        printk("device close\n");
        return 0;
     }
     
     struct file_operations drv_fops = 
     {
        read:		drv_read,
        write:		drv_write,
        ioctl:		drv_ioctl,
        open:		drv_open,
        release:	drv_release,
     };

 

3. 撰寫初始化、結束元件的函式

   ::

     #define MAJOR_NUM		60
     #define MODULE_NAME		"DEMO"
     static int demo_init(void) {
        if (register_chrdev(MAJOR_NUM, "demo", &drv_fops) < 0) {
           printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM);
           return (-EBUSY);
        }
        printk("<1>%s: started\n", MODULE_NAME);
        return 0;
     }
     static void demo_exit(void) {
        unregister_chrdev(MAJOR_NUM, "demo");
        printk("<1>%s: removed\n", MODULE_NAME);	
     }
     module_init(demo_init);
     module_exit(demo_exit);

   其中 MAJOR_NUM 即為 driver 所對應的 device 的 major number

3. 將 driver 掛載到 kernel 上
==============================

3.1 方法一：用 module 的方式撰寫 driver
-----------------------------------------

3.1.1 調整 kernel 為接受 module
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

3.1.2 編譯 driver module
~~~~~~~~~~~~~~~~~~~~~~~~~

3.1.3 掛載 driver
~~~~~~~~~~~~~~~~~~

3.2 方法二：將 driver 寫成 kernel 的一部分
-------------------------------------------

若想要將 driver 編成 kernel 的一部分，在開機時就直接掛載到 Linux 上，要先將 driver 程式放在 kernel source 裡，並將 Makefile 作一些調整使編譯 kernrl 時能夠將 driver 囊括進去。

3.2.1 編輯 driver source
~~~~~~~~~~~~~~~~~~~~~~~~~

請將在 2.2 完成的 driver source 放到 <linux> [#]_ /driver/char/ 目錄中，這裡放的是 linux character device driver 的程式碼。

.. [#] <linux> 為 linux source 的根目錄路徑

3.2.2 調整 Kconfig
~~~~~~~~~~~~~~~~~~~~~

接下來，我們要調整 Kconfig 使 make menuconfig 時出現 demo driver 的選項。 <linux>/driver/char/Kconfig 是定義 menuconfig 的檔案，請跳到最後一行，並在 endmenu 前加入

::

  config DEMO
     tristate "DEMO driver for OPENCSL"
     default n

其中 config DEMO 是宣告一個新的選項叫做 DEMO ，它的說明為 DEMO driver for OPENCSL ， menuconfig 的預設是沒有選取。

3.2.3 調整 Makefile
~~~~~~~~~~~~~~~~~~~~

再來是調整 Makefile ，使 driver 能夠在編譯時被包含到 kernel 中。在 <linux>/driver/char/Makefile 這個關於 character device driver 的 Makefile 中找到 

::

  obj-$(CONFIG_TCG_TPM) += tpm/ 

並在其下一行加入

::

  obj-$(CONFIG_DEMO)   += demo.o

即可。

3.2.4 重新編譯 kernel
~~~~~~~~~~~~~~~~~~~~~

最後，使用 cross-compiler 重新編譯 kernel ，即可產生包含 DEMO driver 的 kernel image 。

3.3 測試 driver
-----------------

3.3.1 新增 device
~~~~~~~~~~~~~~~~~~

3.3.2 使用 driver
~~~~~~~~~~~~~~~~~~

4. 關於本文件
=============

本文件以 `reStructuredText`_ 格式編撰，並可使用 `docutils`_ 工具轉換成 `HTML`_ 或 LaTeX 各類格式。

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _docutils: http://docutils.sourceforge.net/
.. _HTML: http://www.hosting4u.cz/jbar/rest/rest.html



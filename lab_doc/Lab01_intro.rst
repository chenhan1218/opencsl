==============
Lab 1 環境設定
==============

.. 操作環境先以 Linux 為範例，完成八成草稿後，再加入 Windows 環境的操作範例。
.. 目前toolchain未定，希望能找到一套可以符合所有需求的toolchain

1. 實驗簡介
===========

1.1 什麼是嵌入式系統？
----------------------

1.2 實驗操作環境介紹
---------------------
在本套實驗中，我們使用軟體來模擬嵌入式系統的環境，希望對嵌入式系統有興趣的人能夠在自己的電腦上完成所有實驗。本套實驗使用的各項環境如下：
I.   作業系統：ubuntu 7.10
II.  模擬軟體：QEMU
III. toolchain：arm-known-gcc、buildroot（未定）


2. 準備操作環境
===============

2.1 Ubuntu 7.10
---------------
Ubuntu [#]_  是由 Debian 的分支發展出來的一套 linux distribution，可以直接從官方網站 [#]_ 上下載到安裝/ 試用光碟。

.. [#] http://zh.wikipedia.org/wiki/Ubuntu
.. [#] http://www.ubuntu.org.tw/

2.2 QEMU
--------
QEMU 是一套 emulator [#]_ 軟體，能在 PC 系統上模擬其他 processor 的運作方式，在 Linux 或 Windows 上都能執行。
QEMU 的相關介紹可參考維基百科或是其官方網站 [#]_ 

.. [#] http://en.wikipedia.org/wiki/Emulator
.. [#] http://fabrice.bellard.free.fr/qemu 

2.2.1 在 Ubuntu 7.10 上安裝 QEMU
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
QEMU的i386執行檔可以直接從官方網站上下載，或是直接下載原始碼來編譯。
若需下載原始碼，可開啟 Ubuntu 終端機視窗，並執行以下指令：

1. 安裝編譯時所須的套件
..

  sudo apt-get install gcc-3.4 libsdl1.2debian-all libsdl1.2-dev zlib1g-dev


2. 在欲安裝的目錄下，下載原始碼
..

  wget http://fabrice.bellard.free.fr/qemu/qemu-0.9.0.tar.gz


3. 解壓縮原始碼包裹
..

  tar zxf qemu-0.9.0.tar.gz


4. 編譯 QEMU
..

  cd qemu-0.9.0/
  ./configure --cc=/usr/bin/gcc-3.4 --host-cc=/usr/bin/gcc-3.4 --target-list=arm-softmmu
  make


經上述步驟，我們可以編譯出一個能夠執行 ARM 指令集的 QEMU emulator。

2.3 toolchain
-------------


3. 參考資料
===========

3.1 Linux 版本狀況
-------------------

An extremely rushed history of the Linux kernel

======= =============
version released date
======= =============
0.01    Sep, 1991
1.0.0   Mar, 1994
1.2.0   Mar, 1995
2.0.0   Jun, 1996
2.2.0   Jan, 1999
2.4.0   Jan, 2001
2.6.0   Dec, 2003
2.6.14  Oct 27, 2005
2.6.15  Jan 2, 2006
2.6.16  Mar 19, 2006
2.6.17  Jun 17, 2006
2.6.18  Sep 19, 2006
2.6.19  Nov 29, 2006
2.6.20  Feb 4, 2007
2.6.21  Apr 21, 2007
2.6.22  Jul 8, 2007
2.6.23  Oct 9, 2007
======= =============

`Linux Kernel Version History`_ tracks all release records before year 2000.

.. _`Linux Kernel Version History`: http://ftp.cdut.edu.cn/pub2/linux/kernel/history/Master.html

4. 關於本文件
=============

本文件以 `reStructuredText`_ 格式編撰，並可使用 `docutils`_ 工具轉換成 `HTML`_ 或 LaTeX 各類格式。

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _docutils: http://docutils.sourceforge.net/
.. _HTML: http://www.hosting4u.cz/jbar/rest/rest.html

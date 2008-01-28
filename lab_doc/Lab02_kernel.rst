=================
Lab 2 編譯 kernel
=================

1- 什麼是 Linux kernel
======================

1.1 Kernel 結構
---------------
kernel 是作業系統的核心元件，負責處理應用程式和硬體之間的溝通。關於 kernel 的詳細介紹可以參考 wikipedia [#]_。

.. [#] http://en.wikipedia.org/wiki/Kernel_%28computer_science%29

1.2 Linux kernel 簡介
---------------------
Linux kernel 是 Linux 作業系統的 kernel，目前的最新版本是 2.6.*。關於 Linux kernel 的詳細介紹可參考 wikipedia [#]_。

.. [#] http://en.wikipedia.org/wiki/Linux_kernel

1.3 Patch
---------
在 kernel 中，為符合不同計算機結構的需求，可能需要對 kernel source 作一些調整，如調整 memory mapped I/O 或增加專屬於該結構的特殊功能。patch 的目的就是在將將想要更改的程式原始碼自動更新在原來的原始碼上。關於 patch 的詳細介紹可參考 wikipedia [#]_。

.. [#] patch http://en.wikipedia.org/wiki/Patch_%28computing%29
       patch in unix http://en.wikipedia.org/wiki/Patch_%28Unix%29

2- 編譯 kernel
==============

2.1 下載 kernel 原始檔
----------------------

2.2 編譯步驟
------------
1. make mrproper
2. make menuconfig
3. make

3- 執行新的 kernel
==================

3.1 下載 file system
--------------------

3.2 用QEMU執行
--------------

4. 關於本文件
=============

本文件以 `reStructuredText`_ 格式編撰，並可使用 `docutils`_ 工具轉換成 `HTML`_ 或 LaTeX 各類格式。

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _docutils: http://docutils.sourceforge.net/
.. _HTML: http://www.hosting4u.cz/jbar/rest/rest.html


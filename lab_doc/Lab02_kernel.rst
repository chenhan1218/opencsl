=================
Lab 2 編譯 kernel
=================

1- 什麼是 Linux kernel
======================

1.1 Kernel 結構
---------------
kernel 是作業系統的核心元件，負責處理應用程式和硬體之間的溝通。關於 kernel 的詳細介紹可以參考 wikipedia [#]_ 。

.. [#] http://en.wikipedia.org/wiki/Kernel_%28computer_science%29

1.2 Linux kernel 簡介
---------------------
Linux kernel 是 Linux 作業系統的 kernel，目前的最新版本是 2.6.*。關於 Linux kernel 的詳細介紹可參考 wikipedia [#]_ 。

.. [#] http://en.wikipedia.org/wiki/Linux_kernel

1.3 Patch
---------
在 kernel 中，為符合不同計算機結構的需求，可能需要對 kernel source 作一些調整，如調整 memory mapped I/O 或增加專屬於該結構的特殊功能。patch 的目的就是在將將想要更改的程式原始碼自動更新在原來的原始碼上。關於 patch 的詳細介紹可參考 wikipedia [#]_ 。

.. [#] patch http://en.wikipedia.org/wiki/Patch_%28computing%29
       
       patch in unix http://en.wikipedia.org/wiki/Patch_%28Unix%29

2- 編譯 kernel
==============

2.1 下載 kernel 原始檔
----------------------
Linux kernel 的檔案庫是在 http://www.kernel.org/ ，目前所有的 linux kernel 版本都可以在這裡下載。
本次實驗中使用的是 linux kernel 2.6.18.1，可在終端機上直接用 wget 下載。

::

  # 下載
  wget http://www.kernel.org/pub/linux/kernel/v2.6/linux-2.6.18.1.tar.bz2
  # 解壓縮
  tar jvxf linux-2.6.18.1.tar.bz2
  # 切換到 linux kernel 目錄
  cd linux-2.6.18.1

2.2 編譯步驟
------------

編譯 kernel 的步驟和編譯一般的應用程式差不多，都需要經過 make configure、make的過程。

1. make mrproper
   make mrproper 會將所有編譯出來的檔案（包含 configure ）都清除，這個動作可以確保這次編譯的kernel
   不會被之前的設定所影響。
2. make menuconfig
   make menuconfig 是圖性化介面的 configure 模式，configure 是將 linux kernel 調整成適合目標系統使用的手段。
3. make ARCH=arm CROSS_COMPILE=arm-linux-uclibc-

.. 需補上 menuconfig 的選項
.. toolchain 需確認，用上述選項邊不出來

在編譯完成之後，可以在 arch/arm/boot/ 底下發現編譯完成的 kernel image -- zImage。
若編譯失敗，或想重新編譯，可以打 make clean 來清除所有除了 config 以外的編譯出來的檔案。

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


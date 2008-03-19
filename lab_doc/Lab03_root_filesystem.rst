==========================
Lab 3 製作 root filesystem
==========================

.. 將來可以介紹 ramdisk 是什麼，還有 linux 的開機流程

除了 kernel 之外，讓作業系統能順利運作還需要另外一項元素-- filesystem，它紀錄了一個作業系統在運作的過程中所需的程式、資料紀錄等，本次實驗將介紹如何從無到有建立一個最基本的 filesystem ，並學習透過網路使用 filesystem 。

1. 什麼是 root filesystem
=========================

Root filesystem 是構成 filesystem 的最小集合，它包含所有 Linux 開機時需要的檔案及資料夾，如 initrd 、init.d裡的各項服務，、/etc、/proc、/lib等，而且位置全都是從根目錄（ / ）開始，它可以算是整個 filesystem 的源頭。在嵌入式系統中， root filesystem 通常包含了能滿足各種基本使用的工具，如 ls 、 mount 等，之後如果需要額外的儲存空間或檔案則是再透過 mount 來把其他的儲存裝置掛載進來。

2. 製作 root filesystem
=======================

Root filesystem 大致上包含三部份-- 各種常用的工具、一些關於系統組態的設定檔、基本的資料夾結構。以下我們主要使用 busybox 來製作各項工具及生成基本的資料夾。

2.1.1 下載原始碼
~~~~~~~~~~~~~~~~~

Busybox 是一套常被嵌入式系統使用的程式，它主要的功能是提供了各種常用的指令來操作系統，並且將所有指令包成一個執行檔，因為他的各項指令經過改寫，編譯出來的執行檔大小會較一般 Linux 上使用的指令來得小，很適合在嵌入式系統這種資源有限的情況下使用。

2.1 編譯 busybox
-----------------

2.1.2 調整編譯選項
~~~~~~~~~~~~~~~~~~

2.1.3 編譯及產生 root filesystem
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

2.2 製作所需檔案、目錄
-----------------------

3. 使用新的 root filesystem
===========================

3.1 設定 host 端的 NFS 環境
---------------------------

3.2 用QEMU執行
--------------

4. 關於本文件
=============

本文件以 `reStructuredText`_ 格式編撰，並可使用 `docutils`_ 工具轉換成 `HTML`_ 或 LaTeX 各類格式。

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _docutils: http://docutils.sourceforge.net/
.. _HTML: http://www.hosting4u.cz/jbar/rest/rest.html


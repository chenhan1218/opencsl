==========================
Lab 3 製作 root filesystem
==========================

.. 將來可以介紹 ramdisk 是什麼，還有 linux 的開機流程

除了 kernel 之外，讓作業系統能順利運作還需要另外一項元素-- filesystem，它紀錄了一個作業系統在運作的過程中所需的程式、資料紀錄等，本次實驗將介紹如何從無到有建立一個最基本的 filesystem ，並學習透過網路使用 filesystem 。

1. 什麼是 root filesystem
=========================

Root filesystem 是構成 filesystem 的最小集合，它包含所有 Linux 開機時需要的檔案，如 initrd 、init.d裡的各項服務，而且位置全都是從根目錄（ / ）開始，它可以算是整個 filesystem 的源頭。在嵌入式系統中， root filesystem 通常包含了能滿足各種基本使用的工具，如 ls 、 mount 等，之後如果需要額外的儲存空間或檔案則是再透過 mount 來把其他的儲存裝置掛載進來。

2. 製作 root filesystem
=======================

Root filesystem 大致上包含兩部份-- 各種常用的工具以及一些

2.1 編譯 busybox
-----------------

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


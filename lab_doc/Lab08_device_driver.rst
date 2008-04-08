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

2. 方法一：用 module 的方式撰寫 driver
==============================

2.1 driver 程式的基本結構
-------------------------

2.2 撰寫 driver 程式（module）
-----------------------------

2.3 將 driver 掛載到 kernel 上
------------------------------

2.3.1 調整 kernel 為接受 module
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

2.4 測試 driver
-----------------

2.4.1 新增 device
~~~~~~~~~~~~~~~~~~

2.4.2 掛載 driver
~~~~~~~~~~~~~~~~~~

3. 方法二：將 driver 寫成 kernel 的一部分
===========================================

3.1 調整 kernel 、 makefile
----------------------------

3.2 測試新 kernel
------------------

4. 關於本文件
=============

本文件以 `reStructuredText`_ 格式編撰，並可使用 `docutils`_ 工具轉換成 `HTML`_ 或 LaTeX 各類格式。

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _docutils: http://docutils.sourceforge.net/
.. _HTML: http://www.hosting4u.cz/jbar/rest/rest.html



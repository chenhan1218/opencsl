======================
Lab 7 timer interrupt
======================

Timer interrupt 是 interrupt 的一種，負責和系統時間相關的處理任務。本次實驗將介紹 timer interrupt 在 Linux kernel 中扮演的意義，以及如何用軟體的方式調整 timer interrupt ；另外，我們也將介紹在 Linux kernel 中處理 interrupt 的技巧-- top half 和 bottom half。

1. 什麼是 timer interrupt
==========================

1.1 timer interrupt 的運作機制
-------------------------------

1.2 timer interrupt 的意義
----------------------------

1.3 timer interrupt 的處理流程
-------------------------------

2. 調整 timer interrupt
========================

2.1 調整 kernel
----------------

2.2 撰寫 user program
-----------------------

2.2 用 QEMU 測試
-----------------

3. 觀察 top/bottom half
=========================

3.1 調整 kernel 
----------------

3.2 用 QEMU 執行觀察
---------------------

4. 關於本文件
=============

本文件以 `reStructuredText`_ 格式編撰，並可使用 `docutils`_ 工具轉換成 `HTML`_ 或 LaTeX 各類格式。

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _docutils: http://docutils.sourceforge.net/
.. _HTML: http://www.hosting4u.cz/jbar/rest/rest.html


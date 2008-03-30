=============================
Lab 6 interrupt 和 exception
=============================

一個系統的運作除了單一程式的執行外，還必須讓程式能夠和硬體以及系統溝通， interrupt 和 exception 在這個目的上扮演了重要的角色。本次實驗將介紹 Linux 中 interrupt 和 exception 的運作機制，以及如何撰寫/ 修改它們。

1. 什麼是 interrupt 和 exception
================================

1.1 interrupt 和 exception 的功能
---------------------------------

Interrupt 和 exception 是兩種改變系統執行程式順序的方式，分別透過不同的元件觸發。當 interrupt 或 exception 被觸發時，系統會經由查表找到相對應的處理程式（ ISR: Interrupt Service Routine ），並中斷原本在執行的程式，讓 CPU 執行 ISR 的內容，之後才再轉回原來的程式中。這是多工（ multi-tasking ）環境中常常用到的技術。

在此， interrupt 指的是由硬體發出的中斷訊號，而 exception 指的是由軟體或系統所產生的中斷訊號。和 interrupt 、 exception 相關的更多訊息可以參見 wikipedia [#]_ 。

.. [#] http://en.wikipedia.org/wiki/Interrupt

1.2 interrupt 的使用時機
------------------------

1.3 exception 的使用時機
------------------------

2. 觀察 Linux 中的 interrupt
============================

2.1 interrupt 的處理方法
-------------------------

2.2 加入自己的 interrupt
-------------------------

2.3 用 QEMU 測試
-----------------

3. Linux 中的 exception
=======================

3.1 system call 的撰寫方法
---------------------------

3.2 加入自己的 system call
---------------------------

3.2 用 QEMU 測試
-----------------


4. 關於本文件
=============

本文件以 `reStructuredText`_ 格式編撰，並可使用 `docutils`_ 工具轉換成 `HTML`_ 或 LaTeX 各類格式。

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _docutils: http://docutils.sourceforge.net/
.. _HTML: http://www.hosting4u.cz/jbar/rest/rest.html


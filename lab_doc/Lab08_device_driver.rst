=====================
Lab 8 device driver
=====================

1. 什麼是 device driver
========================

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



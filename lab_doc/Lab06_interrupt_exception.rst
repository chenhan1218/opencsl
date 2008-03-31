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

Linux 通常使用兩種方式與與外部元件溝通： polling 以及 interrupt ，前者是 kernel 會定期去偵測外部元件的狀況；而後者是當外不元件有狀況時會馬上通知 kernel 。對於某些發生頻率不高的外部元件（如鍵盤）而言， interrupt 常常是較不影響系統效能的機制。當 interrupt 發生時，系統會如本文件 1.1 所說的優先處理 interrupt ，然後才讓 CPU 切回原本執行的程式。

1.3 exception 的使用時機
------------------------

Exception 依照發生的場合可以分為兩種類型： 程式執行錯誤或例外事件，前者是發生在程式執行錯誤時，如被除數為零、 overflow 等；後者則像是 system call 等作業系統所提供的服務。本實驗將針對 exception 中的 system call 來介紹。

System call 是作業系統提供給 user program 服務的介面，例如處理 I/O 或是使用額外的記憶體，它的目的是為了保護系統的穩定，防止 user program 惡意或者不小心對系統造成的傷害。 System call 實際的運作機制和 Interrupt 相同，它也是透過同樣的對照表來採取對應的處理。

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

要新增 system call 除了撰寫程式本身之外，還需要向 Linux 註冊讓 kernel 知道它的存在 ，這樣 user program 才能夠透過 kernel 呼叫 system call。

註冊 system call 的步驟如下：

1. 增加 system call 的名字

2. 定義新 system call 的代碼

3. 調整 Makefile ，使 systam call 被包含在 kernel 中

4. 增加 system call 的 header file ，讓 user program 能夠 include

另外在撰寫 system call 程式方面，因為程式是在 kernel space 執行，要注意所使用的函式和一般的 user program 不同，使用上也必須特別小心，像是

- 使用 printk 而不是 print

- 使用 kmalloc、kfree 而不是 malloc、free

.. 應該加個如何寫 sys call 的連結

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


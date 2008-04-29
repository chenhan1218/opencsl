=============================
Lab 6 interrupt 和 exception
=============================

.. contents:: 文件目錄
        :depth: 2

一個系統的運作除了單一程式的執行外，還必須讓程式能夠和硬體以及系統溝通， interrupt 和 exception 在這個目的上扮演了重要的角色。本次實驗將介紹 Linux 中 interrupt 和 exception 的運作機制，以及如何撰寫/ 修改它們。

1. 什麼是 interrupt 和 exception
================================

1.1 interrupt 和 exception 的功能
---------------------------------

Interrupt 和 exception 是兩種改變系統執行程式順序的方式，分別透過不同的元件觸發。當 interrupt 或 exception 被觸發時，系統會經由查表找到相對應的處理程式（ ISR: Interrupt Service Routine，或稱 interrupt handler ），並中斷原本在執行的程式，讓 CPU 執行 ISR 的內容，之後才再轉回原來的程式中。這是多工（ multi-tasking ）環境中常常用到的技術。

在此， interrupt 指的是由硬體發出的中斷訊號，而 exception 指的是由軟體或系統所產生的中斷訊號。和 interrupt 、 exception 相關的更多訊息可以參見 wikipedia [#]_ 。

.. [#] http://en.wikipedia.org/wiki/Interrupt

1.2 interrupt 的使用時機
------------------------

Linux 通常使用兩種方式與與外部元件溝通： polling 以及 interrupt ，前者是 kernel 會定期去偵測外部元件的狀況；而後者是當外部元件有狀況時會馬上通知 kernel 。對於某些發生頻率不高的外部元件（如鍵盤）而言， interrupt 常常是較不影響系統效能的機制。當 interrupt 發生時，系統會如本文件 1.1 所說的優先處理 interrupt ，然後才讓 CPU 切回原本執行的程式。

1.3 exception 的使用時機
------------------------

Exception 依照發生的場合可以分為兩種類型： 程式執行錯誤或例外事件，前者是發生在程式執行錯誤時，如被除數為零、 overflow 等；後者則像是 system call 等作業系統所提供的服務。本實驗將針對 exception 中的 system call 來介紹。

System call 是作業系統提供給 user program 服務的介面，例如處理 I/O 或是使用額外的記憶體，它的目的是為了保護系統的穩定，防止 user program 惡意或者不小心對系統造成的傷害。 System call 實際的運作機制和 Interrupt 相同，它也是透過同樣的對照表來採取對應的處理。

2. 觀察 Linux 中的 interrupt
============================

2.1 interrupt 的處理方法
-------------------------

外部元件可能會隨著時間而改變需要的 interrupt 個數，再加上由於硬體資源的限制，同一時間能夠存在的 interrupt 並不是無限而且不一定是可分享的 [#]_ ，所以我們需要一套註冊和釋放的機制來使用 interrupt 。

以下介紹最基本的兩個函數，讓我們可以用 c 程式語言，在系統執行時動態使用 interrupt 資源。關於 interrupt 的詳細使用方法，請參考 TLDP [#]_

1. request_irq() ：向系統註冊使用某一個 interrupt ，並指定負責處理該 interrupt 的 ISR 。

2. free_irq() ：告知系統釋放特定的 interrupt 。

以下我們將藉由觀察 interrupt 在實際程式運作的情況來加強 上面所提的觀念。

.. [#] 我們可以在 <linux>/include/asm-arm/irqs.h 、 <linux>/include/arch/irqs.h 中找到系統上已有的 interrupt以及 NR_IRQ ，它定義了 ARM CPU 中 interrupt 的個數，。

.. [#] http://tldp.org/LDP/tlk/dd/interrupts.html

2.2 觀察實際的 interrupt
-------------------------

在此，我們用 ARM 的 SD Card Host Controller driver 來當作觀察的對象。在該 driver 部份的程式碼 <linux> [#]_ /driver/mmc/mmci.c 的 mmci_probe() 中，我們可以找到一行指令：

::

  ret = request_irq(dev->irq[0], mmci_irq, IRQF_SHARED, DRIVER_NAME " (cmd)", host);

其中 dev->irq[0] 即為該裝置所要使用的其中一個 interrupt ， mmci_irq 則是所要註冊的 ISR ，我們可以在同一個檔案中找到 mmci_irq 這個函式。

為了觀察方便，我們可以在 mmci_irq 中加入一些訊息，在函式的開頭加入

::

   printk("\n---------------------------\nInvoke mmci_irq()\n---------------------------\n");

接著再回到 <linux> 來 compile kernel 

::

   make CROSS_COMPILE=arm-linux-uclibc- ARCH=arm 

就可以製作出一個當 mmc 需要的那個 interrupt 被觸發時，就印出相關訊息的 kernel 。
 
.. [#] 在本文件中， <linux> 皆為 linux kernel 的原始碼位置

2.3 用 QEMU 測試
-----------------

我們可以將新編譯出來的 kernel image 放到 QEMU 中執行，就可以在開機時發現我們剛才想要顯示的訊息。

3. Linux 中的 exception
=======================

3.1 system call 的撰寫方法
---------------------------

要新增 system call 除了撰寫程式本身之外，還需要向 Linux 註冊讓 kernel 知道它的存在 ，這樣 user program 才能夠透過 kernel 呼叫 system call。

註冊 system call 的步驟如下：

1. 註冊 system call 的名字

2. 定義新 system call 的代碼

3. 調整 Makefile ，使 systam call 被包含在 kernel 中

4. 增加 system call 的 header file ，讓 user program 能夠 include


另外在撰寫 system call 程式方面，因為程式是在 kernel space 執行， user program 和 system call 所使用的記憶體位置是無法直接互通的，所使用的函式也和一般的 user program 不同，使用上也必須特別小心，像是

- 使用 printk 而不是 print

- 使用 kmalloc、kfree 而不是 malloc、free

.. 應該加個如何寫 sys call 的連結

3.2 加入自己的 system call
---------------------------

在本節中，我們將透過 3.1 所敘述的步驟自己在系統中新增一個 system call ，這個 system call 將會顯示開機後它總共被呼叫了幾次。

1. 撰寫 system call 的程式

   system call 的程式是放在 <linux>/arch/arm/kernel 中，檔名即為 system call 的名字。

   用編輯器打開 mysyscall.c 後，將以下內容複製進去：

   ::

     #include <linux/linkage.h>
     #include <linux/kernel.h>

     asmlinkage void sys_mysyscall(void){

        static int count = 0;

        printk("mysyscall has been called for %d time(s)\n", ++count);
     }

  
2. 註冊 system call 的名字

   <linux>/arch/arm/kernel/call.S 定義了系統中 system call 的名字，我們要將新的 system call 紀錄在這個檔案中。請用編輯器打開 call.S 之後，找到目前的最後一個 system call，

   ::

      CALL(sys_get_mempolicy)
      CALL(sys_set_mempolicy)

   然後在後面加上

   ::

      CALL(sys_mysyscall)

   再存檔即可。

3. 定義新 system call 的代碼

   <linux>/include/asm-arm/unistd.h 定義了系統中 system call 的代碼，我們也需要在這裡定義新的 system call 代碼。請用編輯器打開 unistd.h 後，找到目前的最後一個 system call（大約在350行），

   ::

     #define __NR_get_mempolicy              (__NR_SYSCALL_BASE+320)
     #define __NR_set_mempolicy              (__NR_SYSCALL_BASE+321)


   然後在後面加上

   ::

     #define __NR_mysyscall                  (__NR_SYSCALL_BASE+322)


4. 調整 Makefile ，使 systam call 被包含在 kernel 中

   <linux>/arch/arm/kernel/Makefile 是該目錄的 makefile ，我們要將 mysyscall.c 加入編譯的範圍內。

5. 增加 system call 的 header file ，讓 user program 能夠 include

   接著，我們要將 mysyscall 的 header 加入 linux 的 header 目錄中，它的位置是 <linux>/include/linux ，在該目錄裡新增 mysyscall.h 的檔案，並填入以下內容：

   ::

     #include <linux/unistd.h>

     #define __NR_mysyscall         (__NR_SYSCALL_BASE+322)
     #define mysyscall(void)        syscall(__NR_mysyscall); 

   再存檔即可。

6. 重新編譯 kernel

   最後，回到 <linux> 並鍵入

   ::

     make CROSS_COMPILE=arm-linux-uclibc- ARCH=arm 

   重新編譯 kernel 後，就會產生新的 kernel image 了。

3.3 用 QEMU 測試
-----------------

為了測試 system call 是否有成功加到 kernel 中，我們可以先用 QEMU 載入新的 kernel image ，並另外寫一個 user program 來呼叫 mysyscall 。

1. 撰寫 user program

   若要呼叫 mysyscall ，要在程式中 include linux/mysyscall.h 。以下為使用 mysyscall 的範例：

   ::

     #include "linux/mysyscall.h"

     int main(){

        mysyscall();

        return 0;
     }


2. 編譯程式

  在寫好程式之後，我們可以用之前做好的 cross-compiler 來編譯程式，不過要注意的一點是，因為程式的內容牽涉到 kernel 的資訊（ system call 是包含在 kernel 中的 ），因此我們也需要加入 kernel 的 include 檔。

  假設要編譯的程式檔名為 test.c ，而要生成的執行檔為 test.out ，則在終端機下鍵入：

  ::

    arm-linux-uclibc-gcc -I<linux>/include/ -static test.c -o test.out 

  即可。

3. 用 QEMU 執行

   我們只需要將 執行 QEMU 時的 -kernel 參數後面換成新編譯完成的 kernel ，就可以使用新的 system call 了。如果 system call 製作成功，你應該可以發現 mysyscall 會隨著呼叫的次數而改變顯示的訊息。


4. 延伸閱讀
===========

Wikipedia
---------
- interrupt http://en.wikipedia.org/wiki/Interrupt

The Linux Document Project
--------------------------
- interrupt http://tldp.org/LDP/tlk/dd/interrupts.html
- exceptiong http://tldp.org/LDP/khg/HyperNews/get/devices/exceptions.html
- How_System_Calls_Work_on_Linux/i86 http://tldp.org/LDP/khg/HyperNews/get/syscall/syscall86.html
- system call http://tldp.org/LDP/lkmpg/2.6/html/x978.html


5. 關於本文件
=============

本文件以 `reStructuredText`_ 格式編撰，並可使用 `docutils`_ 工具轉換成 `HTML`_ 或 LaTeX 各類格式。

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _docutils: http://docutils.sourceforge.net/
.. _HTML: http://www.hosting4u.cz/jbar/rest/rest.html


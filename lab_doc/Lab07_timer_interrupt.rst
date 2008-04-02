======================
Lab 7 timer interrupt
======================

Timer interrupt 是 interrupt 的一種，負責和系統時間相關的處理任務。本次實驗將介紹 timer interrupt 在 Linux kernel 中扮演的意義，以及如何用軟體的方式調整 timer interrupt ；另外，我們也將介紹在 Linux kernel 中處理 interrupt 的技巧-- top half 和 bottom half。

1. 什麼是 timer interrupt
==========================

1.1 timer 的運作機制
-------------------------------

系統計算時間的方式常常是基於內部的某些硬體設備（如振盪器的振動頻率），在由系統控制這些設備的行為所代表的意義。在 Linux 中，當開機時會先從設備讀取時間來初始化計時器(RTC real time clock)，接著 kernel 再依據原本設定的值來決定每秒要發生的中斷（interrupt）次數，當一次中斷發生時，kernel 會將一個全域變數 jiffies 加一，藉此紀錄時間的變化，在一般的 Linux 系統中，每秒會發生 100 次的中斷。

1.2 timer interrupt 的意義
----------------------------

根據 timer 而產生的中斷就叫做 timer interrupt ，在 Linux 系統中， timer interrupt 被拿來當作一些例行性任務的觸發機制，例如更新系統時間、每個 process 的執行時間以及被 context switch 前還能執行的時間，藉此讓 mutlti-tasking 成為可能。

由於每次 timer interrupt 產生時都要花一些時間處理對應的任務，當 timer interrupt 的頻率過低時，系統的反應會比較遲鈍，因為 context switch 的頻率相對變低了，但當 timer interrupt 過高時，系統則會因為不斷處理 timer interrupt 而變得沒有效率。

1.3 timer interrupt 的處理流程
-------------------------------

由於 timer interrupt 是有時間急迫性的 interrupt ，Linux 將這種 interrupt 分成兩部份來處理，也就是在一開使所提的 top half 以及 bottom half。在 top half 中，ISR 會先處理最重要的任務，並儘快將 CPU 使用權交還給 kernel ，之後如果有時間的話才繼續處理 bottom half 的任務，這樣的機制可以使系統比較能夠在高頻率的 interrupt 下還保有系統的平性度。

2. 調整 timer interrupt
========================

2.1 調整 kernel
----------------

1. 找到初始化 timer 的程式碼

   我們可以在 <linux> [#]_ /init/main.c 中找到 kernel 初始化的流程，其中就包含了 time_init() 。如果有興趣的話，可以自行搜尋 time_init() 的內容（在 <linux>/arm/kernel/time.c 中），在此我們先在 time_init() 後面加上 printk() 印出提示訊息，來驗證該函式是否有備執行。

   ::

     timekepping_init();
     time_init();
     printk("----------------\ntime_init()\n----------------\n");

2. 更改 timer interrupt 頻率

   在 <linux>/include/linux/jiffies.h 中定義了 timer interrupt 的頻率，我們可以在該檔案中發現一行程式碼

   ::

     #define ACTHZ (SH_DIV (CLOCK_TICK_RATE, LATCH, 8))

   我們可以將 CLOCK_TICK_RATE 改成 CLOCK_TICK_RATE/2 ，就可以將 timer interrupt 的頻率增加一倍，

   ::

     #define ACTHZ (SH_DIV (CLOCK_TICK_RATE/2, LATCH, 8))

3. 重新編譯 kernel

   接著，請先備份原本的 kernel image 以比較不同 timer interrupt 頻率間的差異，然後再回到 <linux> 重新編譯 kernel ：

   ::

     make CROSS_COMPILE=arm-linux-uclibc- ARCH=arm 

.. [#] 在本文件中， <linux> 皆為 linux kernel 的原始碼位置

2.2 撰寫 user program
-----------------------

我們可以藉由撰寫一個需要較多執行時間的程式來簡單測量系統的效能。
::

  #include<stdio.h>
  #include<time.h>

  int main(){

     clock_t t1;
     int i, j, k, m;

     t1 = clock();

     for(i=0;i<1000;i++)
        for(j=0;j<1000;j++)
           for(k=0;k<1000;k++)
               for(m=0;m<10;m++);

     printf("%lf\n",((double)(clock()-t1))/CLOCKS_PER_SEC);
     return 0;
  }

接著再用之前製作的 cross-compiler 編譯（假設程式叫做 test.c ，執行檔叫做 test.out）：

::

  arm-linux-uclibc-gcc -I <linux>/include test.c -o test.out


2.3 用 QEMU 測試
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


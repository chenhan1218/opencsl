===================================
Lab 5 debugger 和 software emulator
===================================

.. QEMU 的 debug 方式還沒研究

1. 實驗介紹
====================
本次實驗的目的是學會如何對程式進行除錯，無論程式是被編譯成在 target 還是 host 端執行。底下將分段介紹如何用 GDB 以及它的一套 GUI 程式來進行除錯。

1.1 GDB (GNU Debugger)
----------------------
GDB 是一套在 Unix-like 環境上執行的文字介面 debugger，能夠支援多種平台以及程式語言。和GDB相關的介紹請參考 wikipedia [#]_ 以及 GDB 官方網站 [#]_ 。

.. [#] http://en.wikipedia.org/wiki/Gdb 
.. [#] http://www.gnu.org/software/gdb/

1.2 Insight
-----------
Insight 是使用 GDB 的一套 GUI，關於 Insight 的介紹可以參考 Insight 官方網站 [#]_ 。

.. [#] http://sourceware.org/insight/

2. 使用 GDB
===========

.. 介紹基本功能，並給額外文件連結
.. 有空要介紹 multi-thread/multi-process debugging

2.1 安裝 GDB
------------
如果有依照之前的實驗進行，gdb應該已經安裝在電腦當中，我們可以用 whereis 指令來確認 gdb 是否存在。

::

  whereis gdb

若是gdb沒有安裝在電腦當中，可以使用 apt-get 來安裝gdb

::

  sudo apt-get install gdb

2.2 基本功能介紹
----------------
GDB將程式分成一個個的區塊（ frame ），每個 frame 都對應到程式的一個 subroutine ，在使用 GDB 執行程式時是依照 frame 來分塊的。目前執行的 subroutine 叫做 frame 0 ，呼叫該 routine 的叫做 frame 1 ，以此類推。當 frame 0 要呼叫下一個 subroutine 時， GDB 會將目前的資料存到 stack 中，然後才執行下一個 frame ，這樣的分法可以方便除錯時檢視各個 subroutine 之間的關係。

我們用一個簡單的程式來當作使用GDB除錯的範例。以下用C 寫的程式會將輸入的字串全部加一以達到加密的目的。

::

  #include<stdio.h>

  char* encode(char* str){
  	char* tempStr = str;
  	while( *tempStr != 0 ){
  		(*tempStr)++;
  		tempStr++;
  	}
  
  	return str;
  }
  
  int main(int argc, char* argv[]){

  	int i;

  	for(i = 0; i < argc; i++)
  		printf("%s\n", encode(argv[i+1]));
  }

2.2.1 用 GDB 執行程式（ set, show, run/r ）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
如果要用 GDB 來除錯，必須在編譯時加上 -g 參數，使 gcc 多加一些除錯資訊到程式中。

::
 
  gcc -g -o encode encode.c

在編譯完成後，就可以將程式用 GDB 來執行。

::

  gdb ./encode

當載入完成後，會出現 GDB 的命令列，此時可以用 set args 設定要丟給程式的參數，並用 show args 來檢查所下的參數。

::

  (gdb) set args abc osss
  (gdb) show args
  Argument list to give program being debugged when it is started is "abc osss".

接著就可以用 run 來執行程式。

::

  (gdb) run

在執行之後會看到 GDB 出現提示資訊，跟我們說程式因為 segmentation fault 而終止了，並且會提示導致 segmentation fault 的程式行號。

2.2.2 顯示程式碼 （ list/l ）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
如果想要在使用 GDB 時檢視程式碼，可以直接在 GDB 裡用 list 指令，或是縮寫 l ，後面可以指定要顯示某一段程式碼，指定的方式可以是行號、函式名稱或是程式的位址。
例如想要顯示 encode 這個函式到第15行的內容，可以打

::

  (gdb) list encode, 15

如果想要繼續往後閱讀程式碼，只要再打一次 list 即可。
另外，「list - 」則可以印出前十行的程式碼。

2.2.3 設定中斷點（ breakpoint/break/b, continue/cont/c, next/n, step/s）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

2.2.4 讀取變數的值（ print/p, display, info ）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

2.2.5 查看程式資訊（ backtrace/bt, info ）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

2.3 用 GDB 作為 software emulator
---------------------------------

3. 使用 Insight
===============

3.1 安裝 Insight
----------------

3.2 基本功能介紹
----------------

4. 關於本文件
=============

本文件以 `reStructuredText`_ 格式編撰，並可使用 `docutils`_ 工具轉換成 `HTML`_ 或 LaTeX 各類格式。

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _docutils: http://docutils.sourceforge.net/
.. _HTML: http://www.hosting4u.cz/jbar/rest/rest.html


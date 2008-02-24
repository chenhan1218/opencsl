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

我們用一個簡單的程式來當作使用GDB除錯的範例。以下用C 寫的程式會將輸入的字串全部加一已達到加密的目的。

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


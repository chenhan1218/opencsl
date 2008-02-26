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
  }
  
  int main(int argc, char* argv[]){

  	int i;

  	for(i = 0; i < argc; i++){
  		encode(argv[i+1]);
  		printf("%s\n", argv[i+1]);
  	}
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
如果想要在使用 GDB 時檢視程式碼，可以直接在 GDB 裡用 list 指令，或是簡寫 l ，後面可以指定要顯示某一段程式碼，指定的方式可以是行號、函式名稱、檔案名稱或是程式的位址。
例如想要顯示 encode 這個函式到第15行的內容，可以打

::

  (gdb) list encode, 15

如果只給list一個參數，則會顯示那個參數代表的程式碼附近十行的程式。

如果想要繼續往後閱讀程式碼，只要再打一次 list 即可。
另外，「list - 」則可以印出前十行的程式碼。

2.2.3 設定中斷點並繼續執行（ breakpoint/break/b, continue/cont/c, next/n, step/s）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
在程式碼中插入中斷點可以使 GDB 不會一次把程式執行完，而會停在中斷點處。當程式被中斷時，我們可以使用 GDB 來讀取程式內變數、 CPU register 以及程式的其他資訊，本段先介紹如何設置中斷點以及逐步執行程式。

插入中斷點的指令是 breakpoint 或是簡寫 break、b ，後面可以加上參數指定行號、函式或是程式中的位址。當 GDB 執行遇到中斷點時，它會暫停在中斷點之前，也就是說，被設為中斷點的那行程式或函式就是下一個要執行的程式碼。例如我們可以透過以下指令將執行 encode() 前、後都設下中斷點：

::

  (gdb) b encode
  (gdb) b 10

第十行剛好是 encode 的結尾。

當設定好中斷點之後便可以用 run 開始執行程式，接著會發現 GDB 停在 encode() 的第一行程式碼，並且顯示它的參數。

::

  (gdb) set args abc osss
  (gdb) run
  Breakpoint 1, encode (str=0xbfef383c "abc") at bug.c:5
  5               char* tempStr = str;

此時，我們有三種方式可以選擇下一步的動作：

1. continue ，或是簡寫 cont、c 

   continue 的意思是繼續執行到下一個中斷點或是程式結束為止。

2. next ，或是簡寫 n

   next 是一次執行一行程式碼，當程式碼是呼叫函式時， GDB 只會把它視為一行程式碼。

3. step ，或是簡寫 s

   step 和 next 類似，但當碰到函式呼叫時， GDB 會進入函式中逐行執行。

以下示範三種不同方式的結果：

::

  Breakpoint 1, encode (str=0xbfef383c "abc") at bug.c:5
  5               char* tempStr = str;

  # 執行下一行程式碼
  (gdb) n
  6               while( *tempStr != 0 ){

  # 直接執行到下一個中斷點
  (gdb) c
  Continuing.

  Breakpoint 2, encode (str=0xbfef383c "bcd") at bug.c:10
  10      }

  # encode 結束，所以往下一行會跳回 main 裡的 printf
  (gdb) n
  main (argc=3, argv=0xbfef35a4) at bug.c:18
  18                      printf("%s\n", argv[i+1]);

  (gdb) n
  bcd
  16              for(i = 0; i < argc; i++){

  (gdb) s
  17                      encode(argv[i+1]);

  # 將要執行 encode ，選擇進入 encode 中逐步執行
  (gdb) s
  Breakpoint 1, encode (str=0xbfef3840 "osss") at bug.c:5
  5               char* tempStr = str;

值得注意的一點是，如果被呼叫的函式中有設定中斷點，即使是用 next 逐步執行， GDB 還是會跳到函式中。

2.2.4 讀取變數的值（ print/p, display）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
當 GDB 停在中斷點，或是在逐步執行的過程中，我們可以透過 print 指令，或是簡寫 p 來讀取程式內變數的值。接續上面的例子，當程式停在第一個中斷點時，因為程式已經進到 encode() 的第一行，所以目前有效的變數只有 encode() 以及它的參數 str ，main()裡的參數因為不屬於此 frame ，所以無法讀取，而 tempStr 因為還未宣告，因此也是無效的，以下是程式停在 encode() 時使用 print 的情況：

::

  (gdb) p str
  $6 = 0xbf99683b "abc"

  (gdb) p encode
  $7 = {void (char *)} 0x8048374 <encode>

  # 尚未宣告的變數
  (gdb) p tempStr
  $8 = 0x1 <Address 0x1 out of bounds>

  # 不在此 frame 的變數
  (gdb) p argc
  No symbol "argc" in current context.

可以發現到 GDB 會幫每次 print 的變數都取一個暫存代號，我們可以直接選擇顯示這些代號的內容，或是用 $ 、 $$ 來分別表示前一個顯示的變數、前二個顯示的變數的值。

另外， print 也可以顯示陣列裡的部份內容，或是顯示不同的進位方式，如：

::

  # 從 str[0] 開始，顯示兩個元素
  (gdb) p str[0]@2
  $9 = "ab"

  # 用16進位方式顯示
  (gdb) p/x str[1]@2
  $10 = {0x62, 0x63}

如果不想要每次中斷時都重新用 print 來讀取自己想要看的值，可以用 display 設定在每次程式被中斷時想要顯示的資訊。 display 的設定方法和 print 相同，在這裡就不另外作示範。

2.2.5 查看程式資訊（ backtrace/bt, info ）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
當我們想要知道目前函式之間的呼叫狀態時，可以使用 backtrace 指令，或是簡稱 bt ，它能顯示目前 frame stack 的狀態，也可以在後面加上參數「 full 」來顯示每個 frame 裡的 local variavle 。

info 則是顯示各種 GDB 內設定、程式執行狀況的指令。目前設定的中斷點、 display ，或是 CPU registers 的內容都可以用這個指令辦到，如：

::

  # 顯示目前設定的中斷點
  (gdb) info b

  # 顯示目前設定的 display
  (gdb) info display

  # 顯示 eax 的值
  (gdb) info register eax

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


=================
Lab 2 編譯 kernel
=================

Kernel 是作業系統的核心，作業系統所提供的各項功能就是包含在 Kernel 中。本次實驗將介紹如何製作作業系統的核心部份，內容包括了：介紹 Linux Kernel、介紹製作符合自己需求的 kernel ，並將 Linux 放在不同的 platform 上執行。

1. 什麼是 Linux kernel
======================

1.1 Kernel 結構
---------------
kernel 是作業系統的核心元件，負責處理應用程式和硬體之間的溝通。關於 kernel 的詳細介紹可以參考 wikipedia [#]_ 。

.. [#] http://en.wikipedia.org/wiki/Kernel_%28computer_science%29

1.2 Linux kernel 簡介
---------------------
Linux kernel 是 Linux 作業系統的 kernel，目前的最新版本是 2.6.*。關於 Linux kernel 的詳細介紹可參考 wikipedia [#]_ 。

.. [#] http://en.wikipedia.org/wiki/Linux_kernel

1.3 Patch
---------
在 kernel 中，為符合不同計算機結構的需求，可能需要對 kernel source 作一些調整，如調整 memory mapped I/O 或增加專屬於該結構的特殊功能。patch 的目的就在將想要更改的程式原始碼自動更新在舊原始碼上。關於 patch 的詳細介紹可參考 wikipedia [#]_ 。

.. [#] patch http://en.wikipedia.org/wiki/Patch_%28computing%29
       
       patch in unix http://en.wikipedia.org/wiki/Patch_%28Unix%29

2. 編譯 kernel
==============

2.1 下載 kernel 原始檔
----------------------
Linux kernel 的檔案庫是在 http://www.kernel.org/ ，目前所有的 linux kernel 版本都可以在這裡下載。
本次實驗中使用的是 linux kernel 2.6.18.1，可在終端機上直接用 wget 下載。

::

  # 下載
  wget http://www.kernel.org/pub/linux/kernel/v2.6/linux-2.6.18.1.tar.bz2
  # 解壓縮
  tar jvxf linux-2.6.18.1.tar.bz2
  # 切換到 linux kernel 目錄
  cd linux-2.6.18.1

2.2 編譯步驟
------------

編譯 kernel 的步驟和編譯一般的應用程式差不多，都需要經過 make configure、make的過程。以下指令都要在 kernel source的根目錄執行。

1. make mrproper （清理原始檔）
  
   make mrproper 會將所有編譯出來的檔案（包含 configure ）都清除，這個動作可以確保這次編譯的kernel不會被之前的設定所影響。

2. make menuconfig ARCH=arm （設定linux kernel）

   configure 是將 linux kernel 調整成適合目標系統使用的手段，在本次實驗中，我們先下載已經設定好的 .config 檔，接著再用 menuconfig 的方式瀏覽 .config 的內容。

  ::

    # 下載 config 檔
    wget http://free-electrons.com/pub/qemu/demos/arm/arm-test/linux-2.6.18/linux-2.6.18.config

  在下載完成後，鍵入 make menuconfig，即可進入圖形化介面的設定模式。

  make menuconfig 是圖性化介面的 configure 模式，可以依照預先設定好的分類來尋找需要調整的項目。在鍵入 make menuconfig 後，就可以看到圖性化的選單。首先，將游標移到選單最下方的「Load an Alternate Configuration File」，把下載下來的 configure 檔複製到 kernel source 中；這份新的 config 檔將原本的 kernel 調整為一個適合用 ARM 來執行的小型 kernel、使用 ramdisk、取消 module 的使用，並且盡量減少記憶體的消耗。

  如果想要查看或是調整目前的設定，可以用方向鍵、Enter來進出各個項目；以下介紹在 menuconfig 的介面中，一些比較特殊的符號：

  I. [ ]、<>、[*]、<M>

     在每個選項的左方都可以看到上述的其中一個符號，這四個符號代表該選項目前的狀態。

     「 [ ] 」（excludes）表示該選項沒有被選取，編譯後的 kernel 將不會有此功能。

     「 < > 」（module capable）表示該選項沒有被選取，而且是可以被當做是 module，可以在開機之後另外載入的。

     「 [*] 」（built-in）表示該選項有被選取，編譯後的 kernel 包含此功能，而且該功能會被編入 kernel image 中，這意味著在 kernel 被載入時該功能就已經存在，有些功能是一定要在 kernel 被載入時就存在的，例如讀取 filesystem，因為 kernel 無法從它認不出的 filesystem 裡讀取檔案。雖然將各能選成內建可以將整個 kernel 的功能包成一個 kernel image 檔，但它也會造成執行時一些不必要的記憶體以及初始化時間的浪費。

     「 <M> 」（module）表示該選項有被選取，而且是被編譯成 module 的形式，它會存放在 filesystem中，並在 kernel 被載入後才動態地載入。編譯成 module 的優點是減少 kernel image 的空間、加快開機時間，以及方便開發 kernel 功能，因為 module 是在開機後才被載入，每次修改該功能時只需要重新編譯並載入 module ，而不需要重新編譯整個 kernel 並且重新開機。

  II. --->

    「--->」表示該選項是一個分類，他底下還有其他的項目可以選擇。

  在調整完 configure 檔之後，按下方向鍵的「->」，將選項切換到<Exit>，就可以選擇存檔並且離開。

3. make ARCH=arm CROSS_COMPILE=arm-linux-uclibc- （編譯）

  在編譯完成之後，可以在 arch/arm/boot/ 底下發現編譯完成的 kernel image -- zImage。若編譯失敗，或想重新編譯，可以打 make clean 來清除所有除了 config 以外的編譯出來的檔案。

3. 執行新的 kernel
==================
我們可以用 QEMU 來測試新編的 kernel image 是否能夠執行。

.. 如果在真實的系統中，則是可以將kernel image燒到系統的flash上，或是在開機時將 kernel image 載入。

3.1 下載 file system
--------------------
在這裡要找一個確定可以用而且符合此 kernel 相關設定的 file system，QEMU官方網站上的 arm-test disk image 可以符合這項需求。
如果在實驗一中已經有下載過 arm-test disk image，可以直接使用而不需另外下載
下載方法如下：
::

  # 下載 disk image
  wget http://fabrice.bellard.free.fr/qemu/arm-test-0.2.tar.gz
  # 解壓縮
  tar zxf arm-test-0.2.tar.gz


3.2 用QEMU執行
--------------
若在終端機鍵入下列指令後，能夠看到登入畫面，並用root登入，則代表 kernel 編譯成功
::

  <QEMU>/arm-softmmu/qemu-system-arm -kernel <KERNEL> \
        -initrd <ARM_TEST>/arm_root.img -nographic -append "console=ttyAMA0"

.. note::
  <QEMU> = qemu 的根目錄 （如 qemu-0.9.0/ ）
  <KERNEL> = kernel image 的位置 （如 linux-2.6.18.1/arch/arm/boot/zImage）
  <ARM_TEST> = arm-test 的位置


4. 關於本文件
=============

本文件以 `reStructuredText`_ 格式編撰，並可使用 `docutils`_ 工具轉換成 `HTML`_ 或 LaTeX 各類格式。

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _docutils: http://docutils.sourceforge.net/
.. _HTML: http://www.hosting4u.cz/jbar/rest/rest.html


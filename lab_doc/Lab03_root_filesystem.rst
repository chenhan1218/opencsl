==========================
Lab 3 製作 root filesystem
==========================

.. 將來可以介紹 ramdisk 是什麼，還有 linux 的開機流程

除了 kernel 之外，讓作業系統能順利運作還需要另外一項元素-- filesystem，它紀錄了一個作業系統在運作的過程中所需的程式、資料紀錄等，本次實驗將介紹如何從無到有建立一個最基本的 filesystem ，並學習透過網路使用 filesystem 。

1. 什麼是 root filesystem
=========================

Root filesystem 是構成 filesystem 的最小集合，它包含所有 Linux 開機時需要的檔案及資料夾，如 initrd 、init.d裡的各項服務，、/etc、/proc、/lib等，而且位置全都是從根目錄（ / ）開始，它可以算是整個 filesystem 的源頭。在嵌入式系統中， root filesystem 通常包含了能滿足各種基本使用的工具，如 ls 、 mount 等，之後如果需要額外的儲存空間或檔案則是再透過 mount 來把其他的儲存裝置掛載進來。

2. 製作 root filesystem
=======================

Root filesystem 大致上包含三部份-- 各種常用的工具、一些關於系統組態的設定檔、基本的資料夾結構。以下我們主要使用 busybox 來製作各項工具及生成基本的資料夾。

Busybox 是一套常被嵌入式系統使用的程式，它主要的功能是提供了各種常用的指令來操作系統，並且將所有指令包成一個執行檔，因為他的各項指令經過改寫，編譯出來的執行檔大小會較一般 Linux 上使用的指令來得小，很適合在嵌入式系統這種資源有限的情況下使用。

2.1 編譯 busybox
-----------------

2.1.1 下載原始碼
~~~~~~~~~~~~~~~~~

我們可以透過 subversion 的工具下載原始碼，請先切換到欲安裝 busybox 的目錄，然後在終端機下鍵入

::

  svn co svn://busybox.net/branches/busybox_1_9_stable ./busybox

即可下載 busybox 1.9 stable 的原始碼，以下編譯過程即以 busybox 1.9 stable 為對象，不同版本間可能會有些微的差異。

2.1.2 調整編譯選項
~~~~~~~~~~~~~~~~~~

在開始編譯之前，我們需要先調整一些 busybox 的選項。請先下載 busybox 的 config 檔，

::

  wget http://svn.openfoundry.org/opencsl/lab_doc/data/busybox-1.9.config

接著便如同編譯 kernel 時一樣，在 busybox 的根目錄 <busybox> 下鍵入 make menuconfig ，即可進入 configure 畫面。

首先，我們先將載入剛下載的 config 檔，將游標移到選單的最下面可以找到「Load an Alternative Configuration File」，並鍵入 busybox-1.9.config ，這個設定檔會調整 busybox 編譯出的工具以及一些 busybox 的基本設定。

接下來，再進入「Busybox Settings」的「Build Options」，在「Build BusyBox as a static binary(no shared libs)」前按 y 以選擇該項目，將 busybox 編成 static linked 的執行檔。

最後在存檔離開 configure 畫面即可。

2.1.3 編譯及產生 root filesystem
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

接下來便是編譯的過程，我們同樣使用 make 來編譯以及安裝 busybox。

::

  make CROSS_COMPILE=arm-linux-uclibc- ARCH=arm
  make install CROSS_COMPILE=arm-linux-uclibc- ARCH=arm

和編譯 kernel 時相同，我們可以使用 make mrproper 來清除包含 config 在內的所有編譯出來的檔案，或是用 make clean 來清除 config 以外的所有編譯出來的檔案，當更改過 config 檔而需重新編譯時，常常需要 make clean 來將所有的 object file 清除才能成功編譯。 

在 make install 後，我們可以在 <busybox> 下發現一個 _install 資料夾，裡面就放著最基本的檔案結構以及剛才選擇要產生的各項工具。

另外，不仿在 <busybox> 目錄下鍵入 ls -l _install/bin | less ，你會發現除了 busybox 之外的所有執行檔其實都是指向 busybox 的 symbolic link，這也印證了在 2.1 開頭時所提到的資訊。

2.2 製作所需檔案、目錄
-----------------------

在製作完 busybox 後，我們需要補足 linux 需要的一些檔案，包含資料夾、裝置檔以及開機的設定檔，以下分別介紹三類檔案的製作方法。

1. 必須的資料夾

   我們需要 etc、init.d 來放置一些和系統有關的設定、dev 來儲存裝置、root 當作家目錄以及 tmp 來放暫存資料，在 _install 目錄下鍵入：

   ::

     mkdir etc etc/init.d dev root tmp

2. 裝置檔

   為了使用 command line 以及開機，我們需要新增三項裝置 console 、 null 以及 ttyAMA0 ，在 _install/dev 下鍵入

   :: 

     sudo mknod console c 5 1
     sudo mknod null c 1 3
     sudo mknod ttyAMA0 c 204 64

3. 開機的設定檔

   開機所需的檔案包括了 /init 以及 /etc 底下的一些檔案。

   I. 製作 init：

      init 是 linux 在開機時就會去執行的程式，我們編出來的 busybox 已經包含此功能，只要在 _install 下鍵入：

      ::

         ln -s bin/busybox init

      即可把 init 連到 busybox 。

   II. 編輯開機要執行的 script：

      我們需要補上 /etc/inittab 以及 /etc/init.d/rcS 兩個檔案。請先至 svn 下載 inittab 以及 rcS 兩個檔案，再把它放到對應的位置即可。

   III. 登入帳號的相關檔案

      要登入 Linux shell 需要帳號的資料以及群組的資料，我們目前只需設定一個不需要密碼的 root 。請先至 svn 下載 passwd 以及 group 兩個檔案，在將它放到 /etc 底下即可。

.. 檔案應該要放在哪裡呢？

2.4 確定 root filesystem 位置
-----------------------------

由於 _install 目錄裡的就檔案在每次重新製作 busybox 時會被清空，我們必須要把 root filesystem 先移至其他的目錄，搬移的方法如下：

::

  # <rfs> 是 root filesystem 將要放置的位置
  cp -r <busybox>/_install <rfs>

3. 使用新的 root filesystem
===========================

我們選擇使用 NFS 來當作 target 的 root file system ，因為透過 NFS ，我們可以很容易調整並且保留整個 file system 。 為了使用 NFS ，我們需要先設定 host 和 target 的網路環境。

3.1 設定 host 端的 NFS 及網路環境
---------------------------------

3.1.1 設定網路
~~~~~~~~~~~~~~

QEMU 會在 host 的 /etc 中建立一個叫做 qemu-ifup 的檔案，當 QEMU 執行並指定要使用網路時， QEMU 會先執行這個 script ，我們可以用這個檔案來調整 QEMU 的網路設定。

由於目前只需要將 target 連至 host ，還不需要讓 target 能夠連到 host 的對外網路，因此我們只需要將 QEMU 的虛擬網卡設定好即可。

在 /etc/qemu-ifup 中加入一行指令：

::

  /sbin/ifconfig $1 192.168.0.1  promisc up

這樣在 QEMU 啟動時就可以把 QEMU 要使用的網卡設定好 IP 。

3.1.2 設定 NFS
~~~~~~~~~~~~~~

Ubuntu 7.10 已經內含 NFS 的相關工具了，我們只需要再調整一些設定即可。在此，我們要將原本的 root filesystem 加入 NFS 可連線的資料夾中，並且讓 host 端網路能夠接受從 QEMU 發起的連線。

在 /etc/exports 中加入

::

  <rfs> 192.168.0.2(rw,async,no_root_squash,no_subtree_check)
  <rfs> localhost(rw,async,no_root_squash,no_subtree_check)

設定可以掛載 <rfs> 的 IP 位址以及其權限，各選項的說明如下：

1. rw：設為可讀寫
2. async：更改的結果不會馬上寫回硬碟，而事先儲存在記憶體中
3. no_root_squash：掛載的帳號可以在此資料夾使用 root 權限
4. no_subtree_check：

.. no_subtree_check 有需要嗎？


接著，在 /etc/host.allow 加入

::

  nfsd:ALL
  portmap:ALL
  mountd:ALL

將 NFS 需要的網路連線打開。

最後，我們要將新的設定套用在 NFS 上，在終端機下鍵入

::

  sudo /etc/init.d/portmap restart
  sudo /etc/init.d/nfs-kernel-server restart

這樣就可以使用 NFS 了。你不仿可以先在 host 端試試看 NFS 是否有設定成功，只要鍵入

::

  sudo mount -t nfs localhost:<rfs> <想要/掛載/的/目錄>

再去掛載上去的目錄查看是否可以看到 <rfs> 底下的內容，或是進一步用 ls -i 比對兩邊的 inode 是否相同。如果要卸載目錄的話，請鍵入

::

  sudo umount <rfs>

即可。

3.2 用QEMU執行
--------------

在開使用 QEMU 執行之前，要先打開 QEMU 的網路需要的虛擬裝置 tun ，請鍵入

::

  sudo modprobe tun

接著，就可以用 QEMU 執行以 NFS 為 root filesystem 的 Linux 了。

由於指令有點長，建議可以先將指令寫成一個 script ，需要時再直接執行即可。完整的指令為：

::

  <QEMU>/arm-softmmu/qemu-system-arm \
        -kernel <KERNEL> \
        -net nic -net tap \
        -nographic \
        -append "console=ttyAMA0 root=/dev/nfs rw nfsroot=192.168.0.1:<RFS> ip=192.168.0.2::192.168.0.1:255.255.255.0"

.. note::
  <QEMU> = qemu 的根目錄 （如 qemu-0.9.0/ ）

  <KERNEL> = kernel image 的位置 （如 linux-2.6.18.1/arch/arm/boot/zImage）

  <RFS> = root filesyste 的位置

這樣 Linux 會直接使用 NFS 上的檔案來進行開機流程，你也可以試著在 QEMU 裡試著增加一些檔案，來看看是否從 host 端可以馬上看到這些改變。


4. 關於本文件
=============

本文件以 `reStructuredText`_ 格式編撰，並可使用 `docutils`_ 工具轉換成 `HTML`_ 或 LaTeX 各類格式。

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _docutils: http://docutils.sourceforge.net/
.. _HTML: http://www.hosting4u.cz/jbar/rest/rest.html


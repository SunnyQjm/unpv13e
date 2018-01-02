# unpv13e

> ## 下载课本源码（机房的源码已经下载好，可以跳过这一步）

### 方法一：直接到课本提供的官网下载源码

* 首先进入到你要存放代码的路径（这边存在用户根目录下）
  ```java

  //其中sunny换车本机的用户名
  cd /usr/home/sunny/

  ```
* 下载源码</br>
  wget http://www.unpbook.com/unpv13e.tar.gz

### 方法二：直接用本项目里面的压缩包unpv13e.tar.gz即可
  ```c
  
  //linux,unix下的解压命令如下
  tar -zxvf unpv13e.tar.gz
  
  ```
> ## 基本配置：

* 进入到源码的目录，并开始配置
  ```java
  cd unpv13e

  ./configure

  cd lib

  make

  cd ../libfree

  //执行这一步的时候可能会报错，将错误拷贝百度一下就有解决方案
  make
  ```
* 将头文件和支持库配置到系统库里面，这样就可以在任何地方使用unp.h这个头文件了
  ```java
  //执行上面的代码以后处于 unpv13e/libfree 目录下，执行下面的代码回到 unpv13e 根目录下
  cd ..

  cp libunp.a /usr/lib/

  cp libunp.a /usr/lib32/

  cd lib

  cp unp.h /usr/include/

  cp ../config.h /usr/include/

  cd /usr/include

  vim unp.h

  接着把 unp.h 文件中第七行代码中的 “../config.h” 改成 “config.h”。 然后保存并退出

  ```
  
## 至此，你就可以在计算机的任何地方使用unp.h头文件了
## 注意，编译带unp.h头的c文件的时候，需要在最后加上 ***-lunp*** 选项
```c
//类似下面这种用法（byterorder.c 是 unpv13e源码中一个此时计算机是大端还是小端的简单程序————位于：intro/byterorder.c
cc byteorder.c -o bo -lunp
```

* tags配置，直接在配置文件中配置，这样对于所有打开的文件跳转都是有效的
    > 如果用exctags命令无效，试试ctags
    > 如果没安装： </br>
    linux-> apt-get install ctags </br>
    freebsd-> pkg install ctags

  ```java

  cd /usr/lib

  exctags -R .

  cd /usr/lib32

  exctags -R .
  cd ~

  //如果在 ～ 目录下没有.vimrc 这个文件，用下面的命令也能创建一个
  vim .vimrc

  然后在配置文件尾部加上下面两行：
  set tags+=/usr/lib/tags
  set tags+=/usr/lib32/tags

  ```


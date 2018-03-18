# 常见错误
- 链接出错，找不到指定函数
```cmake
[ 50%] Building CXX object CMakeFiles/hello.dir/main.cc.o
[100%] Linking CXX executable hello
CMakeFiles/hello.dir/main.cc.o: In function `main':
main.cc:(.text+0x7d): undefined reference to `power(double, int)'
collect2: error: ld returned 1 exit status
```  
一般是因为代码中使用了某个外部函数，但没有-l引用对应的库，或者没有在LD_LIBARY_PATH中加入指定的路径。  
此外要注意的是，cmake不会预防这种错误。
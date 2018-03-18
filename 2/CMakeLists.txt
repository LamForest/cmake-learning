cmake_minimum_required(VERSION 3.5.1)

project(main)

#这么写略显繁琐，因为若有很多个c文件，都要手动加入。
#add_executable(hello a.cc b.cc c.cc ...一系列源文件)
#可以用aux_source_directory代替
#作用是查找指定文件夹下的所有C++源文件
aux_source_directory(. SRCS)
#生成目标
add_executable( hello ${SRCS} )
#添加链接库，这一行必须要在对应的add_executable后面
#否则，target_link_libraries不知道要hello是什么


# 加入一个配置头文件，用于处理 CMake 对源码的设置
# 这个头文件应该是所有子文件夹公用的，所以放到顶层文件夹中
# 而CMAKE_SOURCE_DIR一直指的是顶层文件夹
configure_file (
  "${CMAKE_SOURCE_DIR}/config.h.in"
  "${CMAKE_BINARY_DIR}/config.h"
)
#加入条件编译选项
#这是cmake的亮点之一
#cmake除了在CMakeLists.txt中使用USE_MYMATH
#还会动态生成config.h文件
#config.h中包含同名的USE_MYMATH变量
#可以通过#ifdef来判断，具体参见main.cc
#USE_MATH的值也可以在ccmake中改变
option (USE_MYMATH
       "Use self-defined math implementation" ON)

# 是否加入自己写的math库
if (USE_MYMATH)
  include_directories ("${CMAKE_SOURCE_DIR}/math")
  #增加子文件夹，对所有子文件夹，递归处理
  #递归处理即在子文件中查找CMakeLists.txt
  #然后按照文件内容进行编译
  #不管是根文件夹，还是子文件夹下的CMakeList中的变量名
  #都要是project中unique的
  add_subdirectory (math)  
  #cmake的赋值语句
  #类似bashrc中的PATH=${PATH}:...,拼接变量
  set (EXTRA_LIBS ${EXTRA_LIBS} math)
  #<target>即hello要在add_executable之后出现
  target_link_libraries(hello math)
else (USE_MYMATH)
  # add_compile_options(-lm)
endif (USE_MYMATH)







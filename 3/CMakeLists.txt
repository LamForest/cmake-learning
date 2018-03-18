#参考：http://www.hahack.com/codes/cmake/
cmake_minimum_required(VERSION 3.5.1)

set(OUTPUT_LIB mymath)
set(COMPILED_DIR mymath)
#这么写略显繁琐，因为若有很多个c文件，都要手动加入。
#add_executable(hello a.cc b.cc c.cc ...一系列源文件)
#可以用aux_source_directory代替
#作用是查找指定文件夹下的所有C++源文件
aux_source_directory(${COMPILED_DIR} SRCS)
#生成目标
add_library( ${OUTPUT_LIB} SHARED ${SRCS} )

#这个函数的作用是，检查Glog是否安装了，并存入对应的变量，以便cmake使用
#流程如下：（参考：https://cmake.org/cmake/help/v3.5/command/find_package.html )
#1. module模式：
#先在cmake自带的*.cmake文件中找，路径为：/usr/share/cmake-3.5/Modules
#注：不清楚如果安装在个人目录下，该路径是否会自动改变
#然后在./cmake（要通过CMAKE_MODULE_PATH设置）中找，如果都找不到就报错。
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
#然后执行找到的*.cmake。
#2. config模式：
#config模式不利用cmake或者本package所提供的*.cmake文件，
#而是利用要找的package安装的时候提供的
#比如/home/barneygao/software/folly/share/folly/folly-config.cmake
#cmake寻找的路径可以通过CMAKE_PREFIX_PATH设置
#具体参看链接
find_package(Glog REQUIRED)

get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

#install
#集中所有头文件
set(MY_HEADER_DIRS
  ${COMPILED_DIR}
)
#统一安装所有头文件
foreach(dir ${MY_HEADER_DIRS} )
  install(DIRECTORY ${dir} DESTINATION include
    FILES_MATCHING PATTERN "*.h"
  )
endforeach()
#安装库，库一般只有一个
install(TARGETS ${OUTPUT_LIB} DESTINATION lib)
#注include 和 lib的前缀都是CMAKE_INSTALL_PREFIX

#test
#test程序名字
set(TEST_EXE math_test)
enable_testing()

#首先编译test程序
#CMAKE_SOURCE_DIR为顶层CMakeLists.txt所在的目录
include_directories(${CMAKE_SOURCE_DIR})
add_executable(${TEST_EXE} test/test.cc)
target_link_libraries(${TEST_EXE} ${OUTPUT_LIB})

macro(do_test test_base test_exponent result)
  add_test(test_${test_base}_${test_exponent} ./${TEST_EXE} ${test_base} ${test_exponent})
  #如果不加下面这行，那么只是简单地测试。
  #只要程序返回的值是0，则test通过
  #所以只能检查一些简单的，比如有无段错误
  #如果加了这行
  #那么cmake就会检查程序的输出是否可以与给定的正则表达式匹配
  #若有匹配则成功
  #这应该就是JOS检查的方式吧
  set_tests_properties (test_${test_base}_${test_exponent}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(do_test)

do_test(2 4 "is 16") 
do_test(10 3 "is 1000")





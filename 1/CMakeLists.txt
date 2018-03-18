cmake_minimum_required(VERSION 3.5.1)

project(hello_world)

#这么写略显繁琐，因为若有很多个c文件，都要手动加入。
#add_executable(hello main.cc math.c)
#可以用aux_source_directory代替
aux_source_directory(. SRCS)
add_executable( hello ${SRCS} )
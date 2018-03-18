aux_source_directory(. MATH_SRCS)
#编译完之后，可以在build中找到一个
#libmath.a的文件
add_library(math ${MATH_SRCS})
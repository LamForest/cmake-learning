#include <stdio.h>
#include <stdlib.h>

/*
如果不在CMakeLists.txt中加入
includeinclude_directories(${CMAKE_SOURCE_DIR})
则要写作：
#include "../mymath/mymath.h"
这是因为make的时候，分别进入一个个子文件夹，然后编译，
而gcc默认只检索当前目录
*/
#include "mymath/mymath.h"

int main(int argc, char *argv[])
{
    if (argc < 3){
        printf("Usage: %s base exponent \n", argv[0]);
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
    double result = pow(base, exponent) ;
    printf("%g ^ %d is %g\n", base, exponent, result);
    return 0;
}
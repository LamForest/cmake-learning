#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#ifdef USE_MYMATH
    #include "math/myMath.h" 
#else
    #include "math.h"
#endif



int main(int argc, char *argv[])
{
    if (argc < 3){
        printf("Usage: %s base exponent \n", argv[0]);
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
    double result = pow(base, exponent);
    printf("%g ^ %d is %g\n", base, exponent, result);
    printf("hello world\n");
    return 0;
}
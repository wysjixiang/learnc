#include "libtest.h"

int add(int a, int b){
    debug("dynamic lib_test, add = %d\n", a+b);
    //return a+b;
    return a - b;
}

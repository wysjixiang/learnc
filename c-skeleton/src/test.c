
#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>
// static lib function test
// int main(int argc, char **argv){
//     int x = 10;
//     printf("sum of 10+2 = %d\n", add(x,2));
//     return 0;
// }



// dynamic lib function test
// when using danamic library, you need to know the version of the lib,
// since the lib is real-time updating 
int main(int argc, char **argv){
    void *handle = NULL;
    int (*add_test)(int a, int b) = NULL;

    // open the dynamic library file
    handle = dlopen("./build/lib.so", RTLD_LAZY);

    if(handle == NULL){
        fprintf(stderr, "%s", dlerror());
        return -1;
    }

    // get function pointer
    add_test = dlsym(handle, "add"); // "add" indicates the string name in the string table. so this string must be compatible with the function name in dynamic lib
    if(add_test == NULL){
        fprintf(stderr, "%s", dlerror());
        dlclose(handle);
        return -1;
    }   

    int x = 10;
    int y = 20;
    debug("dl-function test: %d + %d = %d\n",x,y,add_test(x,y));
    return 0;
}
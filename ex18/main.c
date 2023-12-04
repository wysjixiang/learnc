#include <stdio.h>




int compare_p(int a, int b){
    return (a<b);
}


// shows how to transmit a function pointer to a function as an augment.
int test(int a, int b, int (*cmp_p)(int c, int d)){
    if(cmp_p(a,b) >0)
        return 0;
    return 1;
}

int main(int argc, char **argv){

    printf("result = %d\n",test(1,0,compare_p));

    return 0;
}




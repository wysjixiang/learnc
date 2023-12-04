#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int stack_pos = 0;
static int stack_max = 0;
static void **stack_ptr = NULL;

typedef struct{
	char str[20];
} sentence;

// string stack.
void* stack_gen(int num){
	void **p = (void **)malloc(num * sizeof(void *));
	stack_max = num;
	return p;
}


void stack_push(char *s){
	if(stack_pos >= stack_max){
		printf("No more stack room!stack push failed!\n");
		return ;
	}
	stack_ptr[stack_pos] = (sentence *)malloc(sizeof(sentence));
		memcpy(((sentence *)stack_ptr[stack_pos])->str,s,20);
		stack_pos++;
}

void stack_pop(){
	if(stack_pos == 0){
		printf("Stack is empty!\n");
		return ;
	}

	free(stack_ptr[stack_pos-1]);
	stack_ptr[stack_pos-1] = NULL;
	stack_pos--;
}


int main(){
	int num = 1000;
	stack_ptr = stack_gen(num);
	char *s1 = "stack-1";
	char *s2 = "stack-2";
	char *s3 = "stack-3";
	char *s4 = "stack-4";
	
	stack_push(s1);
	stack_push(s3);
	stack_push(s4);
	//
	for(int i=0;i<stack_pos;i++){
		printf("stack[%d] = %s\n",i,((sentence *)stack_ptr[i])->str);
	}
	//
	stack_pop();
	stack_pop();
	stack_push(s2);
	//
	for(int i=0;i<stack_pos;i++){
		printf("stack[%d] = %s\n",i,((sentence *)stack_ptr[i])->str);
	}
	//

	return 0;
}


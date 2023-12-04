#include <time.h>
#include "node.h"



int main(){
	srand(time(NULL));
	int round = 5000;
	while(round--){
		Node *node = RandNodeCreate(1000);
		bubble_sort(node);
		Node *merge_node = merge_sort(node);
	//	while(merge_node != NULL){
	//		printf("num = %d\n",merge_node->num);
	//		merge_node = merge_node->next;
	//	}
		if(0 != CheckSort(merge_node)){
			printf("Sorted failed!\n");
			return 0;
		}
		destructor(node);
	}
	printf("Sorted Success!\n");

	return 0;
}

#include "node.h"


Node *RandNodeCreate(int N){
	if(N < 2){
		printf("N should bigger than 2");
		return NULL;
	}
	Node *p = (Node *)malloc(N * sizeof(Node));
	p->num = rand()%1000;
	p->next = (p +1);
	for(int i=1;i<N-1;i++){
		(p+i)->num = rand()%1000;
		(p+i)->next = (p+i+1);
	}
	(p+N-1)->num = rand()%1000;
	(p+N-1)->next = NULL;

	return p;
}


void bubble_sort( Node *p){
	Node *start = p;
	Node *end = NULL;
	int temp = 0;

	while(end != start){
		if(start->next == end){
			if(start->num > start->next->num){
				temp = start->num;
				start->num = start->next->num;
				start->next->num = temp;
			}
			return ;
		}

		while(start->next != end){
			if(start->num > start->next->num){
				temp = start->num;
				start->num = start->next->num;
				start->next->num = temp;
			}
				start = start->next;
		}

		end = start;
		start = p;
	}

	return;
}

Node* merge_sort(Node *p){
	int num =0;
	Node *p_s = p;
	while(p_s != NULL){
		num++;
		p_s = p_s->next;
	}
	Node **array = (Node **)malloc(num * sizeof(Node *));
	p_s = p;
	for(int i=0;p_s !=NULL;i++){
		array[i] = p_s;
		p_s= p_s->next;
	}
	int split =1;
	int n;
	int begin;
	int end;
	int s0,s1;
	int index = 0;
	while(split < num){
		n = split;
		begin = 0;
		while(begin < num - split){
			n = begin + split;
			end = (n+split <= num ) ? n + split - 1: num-1;
			s0 = begin;
			s1 = n;
			Node **buf = (Node **)malloc((end-begin+1) * sizeof(Node *));
			// pay attention to memcpy function! the size_t represents bytes!!!
			memcpy(buf,array+begin,(end-begin+1)* sizeof(Node *));
			index = 0;
			while( s0 < n || s1 <= end){
				if(s0 < n && s1 <= end){
					if(array[s0]->num < array[s1]->num){
						buf[index++] = array[s0];
						s0++;
					}	else{
						buf[index++] = array[s1];
						s1++;
					}
				}	else if(s0 < n){
						buf[index++] = array[s0];
						s0++;
				}	else{
						buf[index++] = array[s1];
						s1++;
				}
			}
			memcpy(array+begin,buf,(end-begin+1)* sizeof(Node *));
			free(buf);
			begin = begin + 2*split;
		}
		split = 2 * split;
	}

	Node *head = array[0];
	Node *node = head;
	for(int i=1; i<num ;i++){
		node->next = array[i];
		node = node->next;
	}
	node->next = NULL;

	return head;
}

void destructor(Node *p){
	if(p == NULL){
		return ;
	}	else{
		free(p);
		p = NULL;
		//Node *buf = p;
		//Node *pos = p;
		//while(buf != NULL){
		//	pos = buf->next;
		//	free(buf);
		//	buf = pos;
		//}
	}
	return ;
}

int CheckSort(Node *p){
	while(p->next != NULL){
		if(p->num > p->next->num){
			return -1;
		}
		p = p->next;
	}
	return 0;
}


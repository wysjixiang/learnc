#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Node Node;

struct Node {
	int num;
	Node *next;
} ;


Node *RandNodeCreate(int N);
void bubble_sort(Node *p);

void destructor(Node *p);
int CheckSort(Node *p);
Node* merge_sort(Node *p);

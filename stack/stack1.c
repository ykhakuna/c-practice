#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

//
// This push routine is broken!!
//
int push(int data, struct node **stack) {

	struct node *add = (struct node *)malloc(sizeof(struct node));
	add->data = data;
	add->next = *stack;
	*stack = add;
	return 0;
}

void print_stack(struct node *stack) {
	struct node *cur = stack;
	while (cur) {
		printf("%d ",cur->data);
		cur = cur->next;
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
//	struct node *stack;
	int i;
	struct node *stack=(struct node *)malloc(sizeof(struct node));
//	stack->next=NULL;
//	stack=NULL;
	for (i=0; i<10; i++){
//	stack=push(i,stack);
//		if (push(i,stack)) {
//			fprintf(stderr,"Push Failed!!!!\n");
//			return -1;
//		}a
//struct node *stack=NULL;
push(i,stack);
	}

	printf("Stack:\t");
	print_stack(stack);

	return 0;
}

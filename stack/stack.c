#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

//
// This push routine is broken!!
//
struct node* push(int data, struct node *stack) {

	struct node *add = (struct node *)malloc(sizeof(struct node));
	add->data = data;
	add->next = stack;
	stack = add;
	return stack;
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
	struct node *stack = NULL;
	int i;
	for (i=0; i<10; i++){
		stack=push(i,stack);
		if (!stack) {
			fprintf(stderr,"Push Failed!!!!\n");
			return -1;
		}
	}

	printf("Stack:\t");
	print_stack(stack);

	return 0;
}

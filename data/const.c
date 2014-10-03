#include <stdlib.h>
#include <stdio.h>

int main(){
	const int a=1;
	int const b=2;
	const int *c;
	int *const d;
	int e=8;
	c=&e;
//	d=&e;
	printf("pointer c is:%x, value is:%d\n",&c,c);
	
	c=(int *)malloc(sizeof(int));
	printf("new pointer c is:%x, value is:%d\n",&c,c);
}

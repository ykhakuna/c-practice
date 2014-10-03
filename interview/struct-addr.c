#include <stdio.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({                    \
		const typeof( ((type *)0)->member ) *__mptr = (ptr);  \
		(type *)( (char *)__mptr - offsetof(type,member) );})

struct number{
	int a;
	int b;
	int c;
} n1;

int main(){
//	struct number n1;
	int *p_b;
	p_b=&n1.b;
	struct number *n1_ptr;
	n1_ptr=container_of(p_b,struct number, b);
	printf("n1 address is %p\n",&n1);
	printf("n1_ptr address is %p\n",n1_ptr);
	return 0;
}

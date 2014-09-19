#include <stdio.h>

int main(){
	char ch[]={"abc\0def"}, *p=ch;
	struct {short a; char b; float c;}cs;
	printf("%c\n",*p+4);
	printf("the size of cs is: %u\n",sizeof(cs));
	return 0;}

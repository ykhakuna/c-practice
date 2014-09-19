#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef MEMWATCH
#include "/home/antoine/work/c-practice/memory/examples/memwatch/memwatch.h"
#endif

#define FREE_MEM 4

int *get_mem()
{
	int *mem;
	mem=(int *)calloc(sizeof(int),1024);
	return mem;
}

int main()
{
	int *arr[FREE_MEM];
	int i;
	i=0;

	while(i<FREE_MEM)
	{
		arr[i]=get_mem();
		i++;
	}
	/*	for (i=0; i<10000;i++)
		{
		arr[i]=get_mem();
		}*/
	for(i=0;i<FREE_MEM;i++)
	{	
		free(arr[i]);
	//	arr[i]=NULL;
	}
}

#include <stdio.h>
#include <stdlib.h>

int b_search(int *table, int sz, int key);

int main(int argc,char *argv[]){
	int arr1[]={1,3,5,7,8,9};
	int i=0, index;
	if(argc<2)
	{
		printf("Wrong usage, should be: ./bsearch search_value\n");
		exit(0);
	}
	printf("The array is:\n");
	while(i<(sizeof(arr1)/sizeof(arr1[0])))
	{
		printf("%d ",arr1[i]);
		i++;
	}
	printf("\nThe search value is %d\n",atoi(argv[1]));
	index=b_search(arr1, 7, atoi(argv[1]));
	if(index==-1) 
		printf("Cannot find the value.\n");
	else
		printf("The value index is %d.\n",index);
	return 0;
}

int b_search( int *a, int n, int key )
{
	int mid, front=0, back=n-1;
	while (front<=back)
	{
		mid = (front+back)/2;
		if (a[mid]==key)
			return mid;
		if (a[mid]<key)
			front = mid+1;
		else back = mid-1;
	}
	return -1;
}



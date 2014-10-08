#include <stdio.h>

typedef struct _list_item {
    int value;
    struct _list_item *next;
} list_item;
 
void del_item(list_item *root, int val)
{	
	list_item *cur=root;
	if(root==NULL)
	{
		printf("Empty list!\n");
		return ;
	}
	if(cur->value == val) 
	{
		cur=cur->next;
		return ;
	}
	
	do
	{
		if(cur->next->value==val)
		{	
			cur->next=cur->next->next;
			break;
		}
		cur=cur->next;
	}while(cur != NULL);
}

void print_list(list_item *root)
{
	list_item *lp=root;
	while(lp) {
		printf("%d\n", lp->value);
		lp=lp->next;
	}
}

int main()
{
	list_item list[6];

	list[0].value=1; list[0].next=list+1;
	list[1].value=2; list[1].next=list+2;
	list[2].value=3; list[2].next=list+3;
	list[3].value=4; list[3].next=list+4;
	list[4].value=5; list[4].next=list+5;
	list[5].value=6; list[5].next=0;

	printf("test to delete list item whose value is 3\n");
	del_item(&list, 2);
	print_list(list);

}

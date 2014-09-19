#include <stdio.h>

int fun(void){
    static int count = 10;
    return count--;
}

int count = 1;

int main(void)
{    
     printf("global\t\tlocal static\n");
     for(; count <= 10; ++count)
         printf("%d\t\t%d\n", count, fun());    
    return 0;
}

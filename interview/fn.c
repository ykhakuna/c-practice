int fn(int v)
{
if(v==1 || v==0)
return 1;
if(v%2==0)
return fn(v/2)+2;
else
return fn(v-1)+3;
}

int main(){

printf("fn(7) is:%d\n", fn(7));
}

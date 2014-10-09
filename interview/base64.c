#include <stdio.h>
#include <string.h>

size_t b64_length(size_t len); 
void b64_encode(const void * src, size_t len, void * dst);

const char base64_map[] ="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

int main(){
	char src[]="49d4";
	char dst[128];
	b64_encode(src,strlen(src),dst); 
	printf("Source string is:%s\n",src);
	printf("Base64 dst is:%s\n",dst);
}

size_t b64_length(size_t len){
	int length=0, size=0;
	if(len%3 == 1) length=len+2;
	if(len%3 == 2) length=len+1;
	size=length/3*4;
	return size+1;	//one for terminal char '\0'
}

void b64_encode(const void *src,size_t len, void *dst){
	int dst_size=0;
	int count=len;
	int encode;
	char *in=(char *)src;
	char *out=(char *)dst;
	dst_size=b64_length(len);
	printf("original length is:%d\n",len);
	while(count>=3){
		encode=0;
		encode=*in<<16|*(in+1)<<8|*(in+2);
		*out=base64_map[encode>>18 & 0x3f];
		*(++out)=base64_map[encode>>12 & 0x3f];
		*(++out)=base64_map[encode>>6 & 0x3f];
		*(++out)=base64_map[encode & 0x3f];
		count -=3;
		in +=3;
	}
	if(count>0)
	{
		encode = 0;
		if(count==1)
		{
			encode=*in<<16;
			*out=base64_map[encode>>18 & 0x3f];
			*(++out)=base64_map[encode>>12 & 0x3f];
			*(++out)='='; 
			*(++out)='=';

		}
		if(count==2)
		{
			encode=*in<<16|*(in+1)<<8;
			*out=base64_map[encode>>18 & 0x3f];
			*(++out)=base64_map[encode>>12 & 0x3f];
			*(++out)=base64_map[encode>>6 & 0x3f];
			*(++out)='=';

		}
	}	
	*(++out)='\0';

}

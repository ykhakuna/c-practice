#include <stdio.h>

unsigned char average(const char *filename){
	unsigned int BLOCK_SIZE=512;
	unsigned int nlen=0, nround=0;
	unsigned char avg = 0;
	FILE *fp;
	unsigned char tmp[512];

	if ( (fp = fopen(filename,"r")) == NULL){
		printf("\nThe file did not open\n.");
		return 255;
	}

	while(!feof(fp)){
		if(fread(tmp, 1, BLOCK_SIZE, fp)){
			nlen+=BLOCK_SIZE;
			nround++;
		}else{
			BLOCK_SIZE=BLOCK_SIZE/2;
		}
	}

	avg=(unsigned char)(nlen/nround);
	return avg;
}

int main(){
	char *file="a.txt";
	printf("average of the file is:%d\n",average(file));
}

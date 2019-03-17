#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* ptr;
int num;
float frac;
char leter;

int main(){
	ptr=fopen("db.txt", "w");
	for(num=0;num<4;++num)
		for(frac=0.0;frac<0.5;frac+=0.1)
			for(leter='a';strcmp(&leter,"e")<0;leter=(char)((int)leter+1))
				fprintf(ptr,"%d %f %c\n", num, frac, leter);

}

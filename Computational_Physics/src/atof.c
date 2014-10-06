#include "stdio.h"
#include "stdlib.h"

//不停调用atof转换格式
int main(){
	double v;
	char astring[11];
	for(int i=0; i<10000000; i++){
		scanf("%s",astring);
		v=atof(astring);
		fwrite(&v,sizeof(v),1,stdout);
	}
	return 0;
}

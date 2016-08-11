#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void ss(const char *s)
{
	printf("%s",s);
}
int main()
{
	int s;
	char *f,*w="ssdw";
	f=(char*)malloc(100*sizeof(char));
	strcpy(f,w);
	/*FILE *fpin,*fpout;
	fpin=fopen("C:\\Users\\lenovo\\Desktop\\part3.pdf","rb");
	fpout=fopen("ug.pdf","wb+");
	while((s=fgetc(fpin)) != EOF) fputc(s,fpout);
	fclose(fpin);
	fclose(fpout);*/
	ss(f);
	getchar();
}
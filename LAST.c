#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main()
{
	int i,t;
	FILE *fout,*fp;
	char *name="F:/data/test/",*line;
	line=(char*)malloc(1000*sizeof(char));
	name=(char*)malloc(200*sizeof(char));
	fout=fopen("141270004.txt","w+");
	srand((unsigned)time(NULL));
	for(i=1;i<=14926;i++)
	{
		sprintf(name,"F:/data/test/%d.txt",i);
		fp=fopen(name,"r");
		fgets(line,1000,fp);
		if(strrchr(line,"enron") != NULL) t=-1;
		else t=1;
		fprintf(fout, "%d.txt %d\n", i,t);
		fclose(fp);
	}
	fclose(fout);
	return 0;
}
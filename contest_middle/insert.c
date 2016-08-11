#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
	int i,t[81];
	FILE *fp;
	fp=fopen("4.txt","r+");
	for(i=0;i<81;i++)
		fscanf(fp,"%d",&t[i]);
	for(i=0;i<81;i++)
		fprintf(fp,"%d,",t[i]);
	fclose(fp);
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void merge_file(char *fn_src1,char *fn_src2,char *fn_des)
{
	char t=' ';
	FILE *fn1,*fn2,*fn3;
	fn1=fopen(fn_src1,"r+");
	fn2=fopen(fn_src2,"r+");
	fn3=fopen(fn_des,"w+");
	if(fn1 && fn2 && fn3)
	{
		while(1)
		{
			fscanf(fn1,"%c",&t);
			if(feof(fn1)) break;
			fprintf(fn3,"%c",t);
		}
		fprintf(fn3,"%c",'\n');
		while(1)
		{
			fscanf(fn2,"%c",&t);
			if(feof(fn2)) break;
			fprintf(fn3,"%c",t);
		}
	}
	else printf("erroe");
	fclose(fn1);
	fclose(fn2);
	fclose(fn3);
}
void upper_file(char *fn_src,char *fn_des)
{
	char t=' ';
	FILE *fc,*fd;
	fc=fopen(fn_src,"r+");
	fd=fopen(fn_des,"w+");
	if(fc && fd)
	{
		while(1)
		{
			fscanf(fc,"%c",&t);
			if(feof(fc)) break;
			if(t >= 'a' && t <= 'z') t='A'+(t-'a');
			fprintf(fd,"%c",t);
		}
	}
	fclose(fc);
	fclose(fd);
}
void lower_file(char *fn_src,char *fn_des)
{
	char t=' ';
	FILE *fc,*fd;
	fc=fopen(fn_src,"r+");
	fd=fopen(fn_des,"w+");
	if(fc && fd)
	{
		while(1)
		{
			fscanf(fc,"%c",&t);
			if(feof(fc)) break;
			if(t >= 'A' && t <= 'Z') t='a'+(t-'A');
			fprintf(fd,"%c",t);
		}
	}
	fclose(fc);
	fclose(fd);
}
int f(char *a,char *b)//·µ»Ø1Îªa>b£¬0Îªb>a
{
	return strcmp(a,b);
}
int g(char *a,char *b)
{
	return -strcmp(a,b);
}
void sort_file(char *fn_src,char *fn_des,int (*func)(char *a,char *b))
{
	int i=0,j,k,init=1024,n=10;
	char **c,*tmp;
	FILE *fpin,*fpout;
	fpin=fopen(fn_src,"r+");
	fpout=fopen(fn_des,"w+");
	c=(char**)malloc(n*sizeof(char*));
	tmp=(char*)malloc(init*sizeof(char));
	for(i=0;i<n;i++)
		c[i]=(char*)malloc(init*sizeof(char));
	i=0;
	while(!feof(fpin))
	{
		fscanf(fpin,"%s",c[i]);
		i++;
		if(i >= n)
		{
			n=n*2;
			c=(char**)realloc(c,n*sizeof(char*));
			for(j=i;j<n;j++)
				c[j]=(char*)malloc(init*sizeof(char));
		}
	}
	for(j=0;j<i;j++)
		for(k=0;k<i-j-1;k++)
			if(func(c[k],c[k+1]) > 0)
			{
				strcpy(tmp,c[k]);
				strcpy(c[k],c[k+1]);
				strcpy(c[k+1],tmp);
			}
	for(j=0;j<i;j++)
		fprintf(fpout,"%s\n",c[j]);
}
int main()
{
	merge_file("A.txt", "B.txt", "C.txt");
	upper_file("C.txt", "Cupper.txt");
	lower_file("C.txt", "Clower.txt");
	sort_file("C.txt", "D.txt", f);
	sort_file("C.txt", "E.txt", g);

}
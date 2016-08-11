#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void printFile(FILE *fp)
{
	double gpa;
	int id,age,init=1024,t;
	char *loc,*name;
	loc=(char*)malloc(init*sizeof(char));
	name=(char*)malloc(init*sizeof(char));
	while(1)
	{
		fread(&id,sizeof(int),1,fp);
		fread(name,sizeof(unsigned char),init,fp);
		fread(&age,sizeof(int),1,fp);
		fread(loc,sizeof(unsigned char),init,fp);
		fread(&gpa,sizeof(double),1,fp);
		if(feof(fp)) break;
		printf("%d\t%s\t%d\t%s\t\t%.1lf\n",id,name,age,loc,gpa);
	}
	printf("\n\n");
	fclose(fp);
}
void fwriteb(FILE *fpout,char *fname,int n,int *age,int *id,char **name,char **loc,double *gpa)
{
	int i=0,init=1024;
	while(i<n)
	{
		fwrite(&id[i],sizeof(int),1,fpout);
		fwrite(name[i],sizeof(unsigned char),init,fpout);
		fwrite(&age[i],sizeof(int),1,fpout);
		fwrite(loc[i],sizeof(unsigned char),init,fpout);
		fwrite(&gpa[i],sizeof(double),1,fpout);
		i++;
	}
	fclose(fpout);
}
void txttodat()
{
	FILE *fpin,*fpout;
	double *gpa,t;
	int *age,*id,init=1024,i,n=10,j,rc;
	char **name,**loc,*tmp;
	fpin=fopen("student.txt","r");
	tmp=(char*)malloc(init*sizeof(char));
	name=(char**)malloc(n*sizeof(char*));
	loc=(char**)malloc(n*sizeof(char*));
	age=(int*)malloc(n*sizeof(int));
	id=(int*)malloc(n*sizeof(int));
	gpa=(double*)malloc(n*sizeof(double));
	for(i=0;i<n;i++)
	{
		name[i]=(char*)malloc(init*sizeof(char));
		loc[i]=(char*)malloc(init*sizeof(char));
	}
	i=0;
	while(1)
	{
		fscanf(fpin,"%d %s %d %s %lf",&id[i],name[i],&age[i],loc[i],&gpa[i]);
		i++;
		if(feof(fpin)) break;
		if(i>=n)
		{
			n=n*2;
			id=(int*)realloc(id,n*sizeof(int));
			age=(int*)realloc(age,n*sizeof(int));
			gpa=(double*)realloc(gpa,n*sizeof(double));
			name=(char**)realloc(name,n*sizeof(char*));
			loc=(char**)realloc(loc,n*sizeof(char*));
			for(j=i;j<n;j++)
			{
				name[j]=(char*)malloc(init*sizeof(char));
				loc[j]=(char*)malloc(init*sizeof(char));
			}
		}
	}
	n=i;
	fclose(fpin);
	fpout=fopen("student.dat","wb+");
	fwriteb(fpout,"student.dat",n,age,id,name,loc,gpa);
	fpout=fopen("student.dat","rb");
	printFile(fpout);
	for(i=0;i<n;i++)
		if(strcmp(loc[i],"Nanjing") == 0) id[i]=id[i]+10000000;
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++)
			if(gpa[j]<gpa[j+1])
			{
				rc=id[j];
				id[j]=id[j+1];
				id[j+1]=rc;
				rc=age[j];
				age[j]=age[j+1];
				age[j+1]=rc;
				t=gpa[j];
				gpa[j]=gpa[j+1];
				gpa[j+1]=t;
				strcpy(tmp,name[j]);
				strcpy(name[j],name[j+1]);
				strcpy(name[j+1],tmp);
				strcpy(tmp,loc[j]);
				strcpy(loc[j],loc[j+1]);
				strcpy(loc[j+1],tmp);
			}
	fpout=fopen("studentNew.dat","wb+");
	fwriteb(fpout,"studentNew.dat",n,age,id,name,loc,gpa);
	fpout=fopen("studentNew.dat","rb");
	printFile(fpout);
}
int main()
{
	txttodat();
	system("pause");
}
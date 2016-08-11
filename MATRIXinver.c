#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct {
	char *name;
	int row,col;
	double **value;
}varType;
double determinant(int n,double **m,double re)
{
	int i,j,k=1;
	double **mtmp;
	mtmp=(double**)malloc((n-1)*sizeof(double*));
	if(n == 2)
		return m[0][0]*m[1][1]-m[0][1]*m[1][0];
	else if(n == 1) return m[0][0];
	for(i=1;i<n;i++)
	{
		mtmp[i-1]=(double*)malloc((n-1)*sizeof(double));
		for(j=1;j<n;j++)
			mtmp[i-1][j-1]=m[i][j];
	}
	for(i=0;i<n;i++)
	{
		if(i != 0)
		{
			for(j=1;j<n;j++)
				mtmp[j-1][i-1]=m[j][i-1];
		}
		if(m[0][i] != 0) re=re+m[0][i]*determinant(n-1,mtmp,0)*k;
		k=(-1)*k;
	}
	return re;
}
varType* inverse(varType tmp)
{
	varType* result;
	int n,i,j,k,l,f=1;
	double sub,**subd;
	n=tmp.row;
	sub=determinant(n,tmp.value,0);
	if(sub == 0) return NULL;
	subd=(double**)malloc((n-1)*sizeof(double*));
	result=(varType*)malloc(sizeof(varType));
	result->value=(double**)malloc(n*sizeof(double*));
	for(i=0;i<n;i++)
	{
		result->value[i]=(double*)malloc(n*sizeof(double));
		if(i != n-1) subd[i]=(double*)malloc((n-1)*sizeof(double));
		for(j=0;j<n;j++)
			result->value[i][j]=0;
		result->value[i][i]=1;
	}
	result->row=n;
	result->col=n;
	for(i=0;i<n;i++)
	{
		for(j=0,l=0;j<n && l<n-1;j++,l++)
		{
			if(j == i) j++;
			for(k=1;k<n;k++)
				subd[l][k-1]=tmp.value[j][k];
		}
		result->value[0][i]=determinant(n-1,subd,0)/sub;
		f=(-1)*f;
		for(j=1;j<n;j++)
		{
			for(k=0,l=0;k<n && l<n-1;k++,l++)
			{
				if(k == i) k++;
				subd[l][j-1]=tmp.value[k][j-1];
			}
			result->value[j][i]=determinant(n-1,subd,0)/sub;
			f=(-1)*f;
		}
	}
	return result;
}
int main()
{
	FILE *fp;
	int i,j;
	varType *a,b;
	fp=fopen("inve.txt","r");
	b.row=9;
	b.col=9;
	b.value=(double**)malloc(b.row*sizeof(double*));
	for(i=0;i<b.row;i++)
	{
		b.value[i]=(double*)malloc(b.col*sizeof(double));
		for(j=0;j<b.col;j++)
			fscanf(fp,"%lf",&b.value[i][j]);
	}
	fclose(fp);
	a=inverse(b);
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct {
	char *name;
	int row,col;
	double **value;
}varType;
varType* plusMinus(varType a,varType b,int porm,int error)//porm=1 plus,p=-1 minus
{
	varType *result;
	int i,j,row,col;
	result=(varType*)malloc(sizeof(varType));
	result->name="tmp";
	if(error == 1)
	{
		result->row=a.row<b.row ? a.row:b.row;
		result->col=a.col<b.col ? a.col:b.col;
	}
	else
	{
		result->row=a.row;
		result->col=a.col;
	}
	row=result->row;
	col=result->col;
	result->value=(double**)malloc(row*sizeof(double*));
	for(i=0;i<row;i++)
		result->value[i]=(double*)malloc(col*sizeof(double));
		for(j=0;j<col;j++)	
	if(b.row == 1 && b.col == 1)
	{
		for(i=0;i<row;i++)
			for(j=0;j<col;j++)
				result->value[i][j]=a.value[i][j]+b.value[0][0]*porm;
	}
	else
	{
		for(i=0;i<row;i++)
			for(j=0;j<col;j++)
				result->value[i][j]=a.value[i][j]+b.value[i][j]*porm;
	}
	return result;
}
varType* multiply(varType a,varType b,int reverse)
{
	varType *result;
	int i,ik,jk,n;
	result=(varType*)malloc(sizeof(varType));
	result->name="tmp";
	if(reverse == 0)
	{
		result->row=a.row;
		result->col=b.col;
		n=a.col;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(ik=0;ik<result->row;ik++)
		{
			result->value[ik]=(double*)malloc(result->col*sizeof(double));
			for(jk=0;jk<result->col;jk++)
			{
				result->value[ik][jk]=0;
				for(i=0;i<n;i++)
					result->value[ik][jk]+=a.value[ik][i]*b.value[i][jk];
			}
		}
	}
	else if(reverse == 1)
	{
		result->row=a.col;
		result->col=b.col;
		n=a.row;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(ik=0;ik<result->row;ik++)
		{
			result->value[ik]=(double*)malloc(result->col*sizeof(double));
			for(jk=0;jk<result->col;jk++)
			{
				result->value[ik][jk]=0;
				for(i=0;i<n;i++)
					result->value[ik][jk]+=a.value[i][ik]*b.value[i][jk];
			}
		}	
	}
	else if(reverse == 2)
	{
		result->row=a.row;
		result->col=b.row;
		n=a.col;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(ik=0;ik<result->row;ik++)
		{
			result->value[ik]=(double*)malloc(result->col*sizeof(double));
			for(jk=0;jk<result->col;jk++)
			{
				result->value[ik][jk]=0;
				for(i=0;i<n;i++)
					result->value[ik][jk]+=a.value[ik][i]*b.value[jk][i];
			}
		}
			
	}
	else if(reverse == 3)
	{
		result->row=a.col;
		result->col=b.row;
		n=a.row;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(ik=0;ik<result->row;ik++)
		{
			result->value[ik]=(double*)malloc(result->col*sizeof(double));
			for(jk=0;jk<result->col;jk++)
			{
				result->value[ik][jk]=0;
				for(i=0;i<n;i++)
					result->value[ik][jk]+=a.value[i][ik]*b.value[jk][i];
			}
		}
	}
	return result;
}
int main()
{
	int ra=4,ca=8,rb=4,cb=10,i,j;
	FILE *fp1,*fp2;
	varType a,b,*result;
	fp1=fopen("mat1.txt","r");
	fp2=fopen("mat2.txt","r");
	a.value=(double**)malloc(ra*sizeof(double*));
	a.row=ra;
	a.col=ca;
	for(i=0;i<ra;i++)
	{
		a.value[i]=(double*)malloc(ca*sizeof(double));
		for(j=0;j<ca;j++)
			fscanf(fp1,"%lf",&a.value[i][j]);
	}
	b.value=(double**)malloc(rb*sizeof(double*));
	b.row=rb;
	b.col=cb;
	for(i=0;i<rb;i++)
	{
		b.value[i]=(double*)malloc(cb*sizeof(double));
		for(j=0;j<cb;j++)
			fscanf(fp2,"%lf",&b.value[i][j]);
	}
	//result=plusMinus(a,b,1,1);
	result=multiply(a,b,1);
	fclose(fp1);
	fclose(fp2);
	return 0;
}
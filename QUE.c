#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
typedef struct s
{
	int n,*position;
	int start,end;
}hull;
int tangent(hull *q,int a,int b,int *X,int *Y)
{
	
}
void clockwise(int a,int *X,int *Y,int anti)
{

}
void combine(int start,int end,int *X,int *Y,hull *A,hull *B)
{
	int i,a,b;
	a=A->position[A->n-1];
	b=B->position[0];
	while(!tangent(A,a,b,X,Y) || !tangent(B,a,b,X,Y))
	{
		while(!tangent(A,a,b,X,Y)) clockwise(a,X,Y,0);
		while(!tangent(B,a,b,X,Y)) clockwise(b,X,Y,1);//anti=1 -> anti-clockwise
	}
}
hull* CH(int start,int end,int *X,int *Y)
{
	hull *A,*B,*tmp;
	int i,j,t,mid;
	mid=(end-start)/2;
	if(mid > 3)
	{
		A=CH(start,mid,X,Y);
		B=CH(mid+1,end,X,Y);
		combine(start,mid,end,X,Y,A,B);
	}
	else
	{
		tmp=(hull*)malloc(sizeof(hull));
		tmp->n=0;
		tmp->start=start;
		tmp->end=end;
		tmp->position=(int*)malloc(n*sizeof(int));
		for(i=start;i<=end;i++)
		{
			tmp->position[tmp->n]=i;
			tmp->n++;
		}
		return tmp;
	}
}
int main()
{
	int i,n,*X,*Y;
	fscanf(fp,"%d",&n);
	X=(int*)malloc(n*sizeof(int));
	Y=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf(fp,"%d %d",&X[i],&Y[i]);
	cacu(0,n-1,X,Y);
}
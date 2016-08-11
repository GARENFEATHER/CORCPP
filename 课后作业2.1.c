#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void exchange(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void rank(int n,int *t,int *b)
{
	int i=0,j=0,temp1,temp2,temp;
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++)
		{
			temp1=t[j]*b[j+1];
			temp2=t[j+1]*b[j];
			if(temp1 > temp2)
			{ 
				exchange(&t[j],&t[j+1]);
				exchange(&b[j],&b[j+1]);
			}
		}
	printf("排序后:\n");
	for(i=0;i<n;i++)
		printf("%d/%d ",t[i],b[i]);
	printf("\n");
}
int gcd(int m,int n)
{
	int r;
	if(n!=0)
	{
		if(m>=n)
		{
			r=m%n; m=n; n=r;
		}
		else
		{
			r=n%m; n=r;
		}
		gcd(m,n);
	}
	else return m;
}
void sum(int n,int *t,int *b)
{
	int *sum,sumb,i,j,g,sumt;
	sum=(int* )malloc(n*sizeof(int));
	for(i=0,sumb=1;i<n;i++)
	{
		sumb=sumb*b[i];
		sum[i]=t[i];
		for(j=0;j<n;j++)
			if(i!=j) sum[i]=sum[i]*b[j];
	}
	for(i=0,sumt=0;i<n;i++)
		sumt=sumt+sum[i];
	g=gcd(sumt,sumb);
	sumt=sumt/g;
	sumb=sumb/g;
	printf("所有分数的和为:\n");
	printf("%d/%d\n",sumt,sumb);
}
int main()
{
	int n,*b,*t,i;
	printf("请输入分数的个数:\n");
	scanf("%d",&n);
	b=(int* )malloc(n*sizeof(int));
	t=(int* )malloc(n*sizeof(int));
	printf("请输入分数:\n");
	for(i=0;i<n;i++)
		scanf("%d/%d",&t[i],&b[i]);
	printf("排序前:\n");
	for(i=0;i<n;i++)
		printf("%d/%d ",t[i],b[i]);
	printf("\n");
	rank(n,t,b);
	sum(n,t,b);
	system("pause");
}
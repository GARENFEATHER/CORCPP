#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<sys/timeb.h>
struct timeb s,e;
void quicksort(int *num,int *L,int *K,int *G,int low,int high)
{
	int tmp1,tmp2,ht=0;
	if(num[low] > num[high])
	{ tmp1=num[low]; num[low]=num[high]; num[high]=tmp1; }
	tmp1=num[low];
	tmp2=num[high];
	*L=low+1;
	*K=low+1;
	*G=high-1;
	while(*K<*G)
	{
		while(num[*K] < tmp1)
		{
			(*L)++;
			(*K)++;
		}
		while(num[*K] > tmp2)
		{
			ht++;
			(*K)++;
		}
		while(num[*K] >= tmp1 && num[*K] <=tmp2) (*K)++;
	}
	num[low]=num[*L-1];
	num[*L-1]=tmp1;
	num[high]=num[*G+1];
	num[*G+1]=tmp2;
}
void dualQsort(int *num,int low,int high)
{
	int K,G,L;
	if(low <high)
	{
		quicksort(num,&L,&K,&G,low,high);
		dualQsort(num,low,L-1);
		dualQsort(num,L+1,G-1);
		dualQsort(num,G+1,high);
	}
}
int main()
{
	FILE *fp;
	int n,*num,i;
	long t;
	ftime(&s);
	fp=fopen("input1 - less.txt","r");
	fscanf(fp,"%d",&n);
	num=(int* )malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		fscanf(fp,"%d",&num[i]);
	dualQsort(num,0,n-1);
	for(i=0;i<n;i++)
		printf("%d ",num[i]);
	ftime(&e);
	t=(long)(e.time*1000+e.millitm)-(long)(s.time*1000-s.millitm);
}
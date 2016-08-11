#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int quicksort(int low,int high,double *ci,int *di)
{
	int tmpd;
	double tmpc;
	tmpd=di[low];
	tmpc=ci[low];
	while(low < high)
	{
		while(low < high && tmpc <= ci[high]) high--;
		ci[low]=ci[high];
		di[low]=di[high];
		while(low < high && tmpc >= ci[low]) low++;
		ci[high]=ci[low];
		di[high]=di[low];
	}
	di[low]=tmpd;
	ci[low]=tmpc;
	return low;
}
void Qsort(int low,int high,double *ci,int *di)
{
	int mid;
	if(low < high)
	{
		mid=quicksort(low,high,ci,di);
		Qsort(low,mid-1,ci,di);
		Qsort(mid+1,high,ci,di);
	}
}
void price(int n,int l,int u)
{
	int di[n],i,count,value;
	double ci[n],weight;
	count=0;
	weight=0;
	for(i=0;i<n;i++)
		scanf("%d %lf",&di[i],&ci[i]);
	Qsort(0,n-1,ci,di);
	for(i=0;i<n;i++)
	{
		if(count < l && count+di[i] < l) value=di[i];
		else if(di[i] > 0)
		{
			if(count < l) value=l-count;
			else value=0;
		}
		else
		{
			if(count+di[i] >=l && count+di[i] <= u) value=di[i];
			else if(count+di[i] > u) value=u-count;
		}
		weight=weight+value*ci[i];
		if(weight > 0)
		{
			printf("0.00");
			return;
		}
		else if(value == l-count || value == u-count || value == 0)
		{
			printf("%.2lf", weight);
			return;
		}
		count=count+value;
	}
}
int main()
{
	int n,l,u;
	scanf("%d %d %d",&n,&l,&u);
	price(n,l,u);
	return 0;
}
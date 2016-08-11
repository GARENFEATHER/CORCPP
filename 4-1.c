#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<sys/timeb.h>
void sort(int *num,int n)
{
	int i,j,tmp;
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++)
			if(num[j] < num[j+1])
			{
				tmp=num[j];
				num[j]=num[j+1];
				num[j+1]=tmp;
			}
}
int combine(int *num,int low,int high)
{
	int middle,i,j,count=0;
	middle=(low+high)/2;
	sort(num+low,middle-low+1);
	sort(num+middle+1,high-middle);
	for(i=low;i<=middle;i++)
		for(j=middle+1;j<=high;j++)
			if(num[i] > num[j])
			{
				count=count+high-j+1;
				break;
			}
	sort(num+low,high-low+1);
	return count;
}
int inversion(int count,int *num,int low,int high)
{
	int i,j,middle;
	middle=(low+high)/2;
	if(high-low <= 4)
	{
		for(i=low;i<high;i++)
			for(j=i+1;j<=high;j++)
				if(num[i] >= num[j]) count++;
	}
	else
	{
		count=inversion(count,num,low,middle);
		count=inversion(count,num,middle+1,high);
		count=count+combine(num,low,high);
	}
	return count;
}
int main()
{
	FILE *fp;
	int n,*num,i,count,t;
	scanf("%d",&n);
	num=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",&num[i]);
	count=inversion(0,num,0,n-1);
	printf("%d",count);
}
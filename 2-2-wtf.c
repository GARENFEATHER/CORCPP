#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main()
{
	int n,*num,i,j,tmp;
	scanf("%d",&n);
	num=(int* )malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",&num[i]);
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++)
			if(num[j]<num[j+1])
			{
				tmp=num[j];
				num[j]=num[j+1];
				num[j+1]=tmp;
			}
	for(i=0;i<n;i++)
		printf("%d ",num[i]);
}
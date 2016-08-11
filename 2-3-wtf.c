#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main()
{
	int n,*num,k,i,j,tmp;
	scanf("%d%d",&n,&k);
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
	printf("%d ",num[k-1]);
}
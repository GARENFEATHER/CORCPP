#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int quick(int* num,int low,int high)
{
	int tmp;
	tmp=num[low];
	while(low<high)
	{
		while(low<high && num[high]<=tmp) high--;
		num[low]=num[high];
		while(low<high && num[low]>=tmp) low++;
		num[high]=num[low];
	}
	num[low]=tmp;
	return low;
}
void Quick(int* num,int low,int high,int k)
{
	int middle;
	if(low<=high)
	{
		middle=quick(num,low,high);
		/*printf("%d %d %d\n",low,middle,high);*/
		if(middle == k-1)
		{
			printf("%d",num[middle]);
			return;
		}
		else if(middle>k-1) Quick(num,low,middle-1,k);
		else Quick(num,middle+1,high,k);
	}
}
int main()
{
	/*FILE *fp;*/
	int n,k,*num,i;
	/*fp=fopen("3-input7.txt","r");*/
	scanf("%d%d",&n,&k);
	num=(int* )malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",&num[i]);
	Quick(num,0,n-1,k);
	/*system("pause");*/
}
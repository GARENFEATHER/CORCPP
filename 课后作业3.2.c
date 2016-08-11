#include<stdio.h>
#include<stdlib.h>
int caculate(int *num)
{
	int i,sum=0;
	for(i=0;i<5;i++)
		sum=sum+num[i];
	return sum;
}
void find(int *num,int n)
{
	int i,tmp,max=INT_MIN,position=0;
	for(i=0;i<n-5;i++)
	{
		tmp=caculate(num+i);
		if(tmp > max)
		{
			max=tmp;
			position=i;
		}
	}
	printf("相邻的和最大的5个数：\n");
	for(i=position;i<position+5;i++)
		printf("%d ",num[i]);
	printf("\n");
	printf("起始位置：\n%d\n",position);
}
int main()
{
	FILE *fp;
	int n=20,i,*num;
	fp=fopen("课后作业3.2.txt","r");
	num=(int*)malloc(n*sizeof(int));
	printf("请输入%d个数：\n",n);
	for(i=0;i<n;i++)
		fscanf(fp,"%d",&num[i]);
	find(num,n);
	system("pause");
}
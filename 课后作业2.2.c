#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void rank(int n,int *num)
{
	int i,j,temp;
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++)
			if(num[j]>num[j+1])
			{
				temp=num[j];
				num[j]=num[j+1];
				num[j+1]=temp;
			}
	printf("��С��������:\n");
	for(i=0;i<n;i++)
		printf("%d ",num[i]);
	printf("\n");
}
int search(int m,int n,int *num)
{
	int mid,low,high,find=0;
	low=0;
	high=n-1;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(m > num[mid]) low=mid+1;
		else if(m < num[mid]) high=mid-1;
		else
		{
			find=1;
			break;
		}
	}
	if(find == 1) return mid;
	else return -1;
}
int main()
{
	int n,*num,i,m,result;
	printf("�����������ĸ�����\n");
	scanf("%d",&n);
	num=(int* )malloc(n*sizeof(int));
	printf("������������\n");
	for(i=0;i<n;i++)
		scanf("%d",&num[i]);
	rank(n,num);
	printf("��������������:\n");
	scanf("%d",&m);
	result=search(m,n,num);
	if(result != -1) printf("%d�Ǵ�С�������еĵ�%d������\n",m,result+1);
	else printf("��û�������");
	system("pause");
}
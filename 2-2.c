#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<sys/timeb.h>
struct timeb s,e;
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
void Quick(int* num,int low,int high)
{
	int middle;
	if(low<high)
	{
		middle=quick(num,low,high);
		Quick(num,low,middle-1);
		Quick(num,middle+1,high);
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
	Quick(num,0,n-1);
	for(i=0;i<n;i++)
		printf("%d ",num[i]);
	ftime(&e);
	t=(long)(e.time*1000+e.millitm)-(long)(s.time*1000+s.millitm);
	printf("\n\n%ld ms",t);
	fclose(fp);
	system("pause");
}
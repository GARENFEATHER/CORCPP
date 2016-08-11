#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
void combine(int *arr,int low,int mid,int high)
{
	int i,j,k=0,*temp;
	temp=(int*)malloc((high-low+1)*sizeof(int));
	i=low;
	j=mid+1;
	while(i <= mid && j <= high)
	{
		while(i <= mid && arr[i] < arr[j]) temp[k++]=arr[i++];
		while(j <= high && arr[j] < arr[i]) temp[k++]=arr[j++];
	}
	while(j <= high) temp[k++]=arr[j++];
	while(i <= mid) temp[k++]=arr[i++];
	for(i=0,j=low;i<k;i++,j++)
		arr[j]=temp[i];
}
void mergesort(int *arr,int low,int high)
{
	int mid;
	if(low < high)
	{
		mid=(low+high)/2;
		mergesort(arr,low,mid);
		mergesort(arr,low+1,high);
		combine(arr,low,mid,high);
	}
}
int main()
{
	FILE *fp;
	int *arr;
	int i=0,n;
	fp=fopen("merge.txt","r");
	fscanf(fp,"%d",&n);
	arr=(int*)malloc(n*sizeof(int));
	while(i<n)
	{
		fscanf(fp,"%d",&arr[i]);
		i++;
	}
	fclose(fp);
	mergesort(arr,0,n-1);
	for(i=0;i<n;i++)
		printf("%d\n",arr[i]);
	return 0;
}
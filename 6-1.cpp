#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;
typedef struct s
{
	double weight,compare;
	int item;
}data;
int quick(data *t,int low,int high)
{
	data tmp;
	tmp=t[low];
	while(low<high)
	{
		while(low<high && t[high].compare <= tmp.compare) high--;
		t[low]=t[high];
		while(low<high && t[low].compare >= tmp.compare) low++;
		t[high]=t[low];
	}
	t[low]=tmp;
	return low;
}
void quicksort(data *t,int low,int high)
{
	int mid;
	if(low<high)
	{
		mid=quick(t,low,high);
		quicksort(t,low,mid-1);
		quicksort(t,mid+1,high);
	}
}
double max(data *t,int n,int all)
{
	int i;
	double Weight=0.0;
	quicksort(t,0,n-1);
	for(i=0;i<n;i++)
		if(t[i].item <= all)
		{
			all=all-t[i].item;
			Weight=Weight+t[i].weight;
		}
		else
		{
			Weight=Weight+all*t[i].weight/t[i].item;
			break;
		}
	return Weight;
}
int main()
{
	double result;
	data *arr;
	int n,all,i;
	cin>>all;
	cin>>n;
	arr=(data*)malloc(n*sizeof(data));
	for(i=0;i<n;i++)
	{
		cin>>arr[i].weight;
		cin>>arr[i].item;
		arr[i].compare=arr[i].weight/arr[i].item;
	}
	result=max(arr,n,all);
	printf("%.2f",result);
	getchar();
}
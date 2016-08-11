#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
typedef struct s
{
	int x,y;
}point;
void sortbyy(point *l,int n)
{
	point tmp;
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++)
			if(l[j].y > l[j+1].y)
			{
				tmp=l[j];
				l[j]=l[j+1];
				l[j+1]=tmp;
			}
}
double distance(point a,point b)
{
	double d=0.0;
	d=(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
	return sqrt(d);
}
void combine(point *L,int low,int high,double *min)
{
	int i,j,mid;
	mid=(low+high)/2;
	sortbyy(L+low,mid-low+1);
	sortbyy(L+mid+1,high-mid);
	for(i=low;i<=mid;i++)
		for(j=mid+1;j<=high;j++)
			if(distance(L[i],L[j]) < *min) *min=distance(L[i],L[j]);
	sortbyy(L+low,high-low+1);
}
void findmin(point *L,int low,int high,double *min)
{
	int i,j,mid;
	mid=(low+high)/2;
	if(high-low < 3)
	{
		for(i=low;i<high;i++)
			for(j=i+1;j<=high;j++)
				if(distance(L[i],L[j]) < *min) *min=distance(L[i],L[j]);
	}
	else
	{
		findmin(L,low,mid,min);
		findmin(L,mid+1,high,min);
		combine(L,low,high,min);
	}
}
int main()
{
	FILE *fp;
	point *L;
	int n,i;
	double min=DBL_MAX;
	fp=fopen("input6.txt","r");
	fscanf(fp,"%d",&n);
	L=(point*)malloc(n*sizeof(point));
	for(i=0;i<n;i++)
		fscanf(fp,"%d %d",&L[i].x,&L[i].y);
	findmin(L,0,n-1,&min);
	system("pause");
}
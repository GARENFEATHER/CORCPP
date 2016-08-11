#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct s
{
	int number;
	double value;
}point;
int quicksort(int low,int high,point *prn)
{
	point tmp;
	tmp=prn[low];
	while(low < high)
	{
		while(low < high && prn[high].value >= tmp.value) high--;
		prn[low]=prn[high];
		while(low < high && prn[low].value <= tmp.value) low++;
		prn[high]=prn[low];
	}
	prn[low]=tmp;
	return low;
}
void Qsort(int low,int high,point *prn)
{
	int mid;
	if(low<high)
	{
		mid=quicksort(low,high,prn);
		Qsort(low,mid-1,prn);
		Qsort(mid+1,high,prn);
	}
}
void price(int p,int a,int b,int c,int d,int n)
{
	double r=0;
	point *prn,l,t;
	int i,j;
	prn=(point*)malloc(n*sizeof(point));
	for(i=0;i<n;i++)
	{
		prn[i].number=i;
		prn[i].value=p*(sin(a*i+b)+cos(c*i+d));
	}
	Qsort(0,n-1,prn);
	for(i=0;i<n-1;i++)
		for(j=n-1;j>i;j--)
			if(prn[j].number < prn[i].number)
			{
				r=prn[j].value-prn[i].value;
				printf("%lf",r);
				return;
			}
	printf("%lf",r);
}
int main()
{
	int p,a,b,c,d,n;
	scanf("%d %d %d %d %d %d",&p,&a,&b,&c,&d,&n);
	price(p,a,b,c,d,n);
	getchar();
	getchar();
}
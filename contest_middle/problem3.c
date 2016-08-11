#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int sum=0;
int check(int level,int *x)
{
	int i;
	for(i=0;i<level-1;i++)
		if(!(x[i] != x[level] && abs(x[i]-x[level]) != level-i)) return 0;
	return 1;
}
void sumqueen(int level,int n,int *x,int last,int left,int right)
{
	int i;
	if(level < n)
	{
		for(i=0;i<n;i++)
		{
			if(i == last || i == left || i == right) continue;
			x[level]=i;
			if(check(level,x) == 1) sumqueen(level+1,n,x,i,i-1,i+1);
		}
	}
	else sum++;
}
void recall(int n)
{
	int x[n];
	sumqueen(0,n,x,-1,-1,-1);
}
int main()
{
	int n;
	scanf("%d",&n);
	recall(n);
	printf("%d", sum);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int find=0;
int check(int level,int *x)
{
	int i;
	for(i=0;i<level;i++)
		if(!(x[i] != x[level] && abs(x[i]-x[level]) != level-i)) return 0;
	return 1;
}
void backtree(int level,int n,int *x,int last,int left,int right)
{
	int i;
	if(level < n)
	{
		if(find == 1) return;
			for(i=0;i<n;i++)
			{
				if(find == 1) return;
				if(i == last || i == left || i == right) continue;
				x[level]=i;
				if(check(level,x) == 1) backtree(level+1,n,x,i,i-1,i+1);
			}
	}
	else if(find != 1)
	{
		for(i=0;i<n;i++)
			printf("%d ", x[i]+1);
		find=1;
	}
}
void recall(int n)
{
	int x[n];
	backtree(0,n,x,-1,-1,-1);
}
int main()
{
	int n;
	scanf("%d",&n);
	recall(n);
	return 0;
}
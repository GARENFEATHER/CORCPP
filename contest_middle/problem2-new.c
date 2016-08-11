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
void backtree(int n)
{
	int x[n],i,j;
	i=j=0;
	while(i<n)
	{
		while(j<n)
		{
			x[i]=j;
			if(check(i,x) == 1)
			{
				j=0;
				break;
			}
			else j++;
		}
		if(j == 0) i++;
		else i--;
	}
	for(i=0;i<n;i++)
		printf("%d ", x[i]+1);
}
int main()
{
	int n;
	scanf("%d",&n);
	backtree(n);
	return 0;
}
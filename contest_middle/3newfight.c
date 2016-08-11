#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int check(int row,int col,int n,int *x)
{
	int i;
	for(i=0;i<n;i++)
		if(x[i] == col || abs(row-i) == abs(col-x[i])) return 0;
	return 1;
}
void caculate(int n)
{
	long result=0;
	int i,j,x[n];
	for(i=0;i<n;i++)
		x[i]=-n-1;
	i=0;
	j=0;
	while(i < n)
	{
		while(j<n)
		{
			if(check(i,j,n,x))
			{
				x[i]=j;
				j=0;
				break;
			}
			else j++;
		}
		if(j == n)
		{
			if(i == 0) break;
			else
			{
				i--;
				j=x[i]+1;
				x[i]=-n-1;
				continue;
			}
		}
		if(i == n-1)
		{
			result++;
			j=x[i]+1;
			x[i]=-n-1;
			continue;
		}
		i++;
	}
	printf("%ld", result);
}
int main()
{
	int n;
	scanf("%d",&n);
	caculate(n);
	return 0;
}
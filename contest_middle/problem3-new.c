#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct s
{
	int value;
	struct s *next;
}get;
int sum=0;
int check(int level,int *x)
{
	int i;
	for(i=0;i<level;i++)
		if(!(x[i] != x[level] && abs(x[i]-x[level]) != level-i)) return 0;
	return 1;
}
int* possibleget(int position,get *now)
{

}
void sumqueen(int level,int n,int *x)
{
	int i;
	if(level < n)
	{
		for(i=0;i<n;i++)
		{
			
			x[level]=i;
			if(check(level,x) == 1) sumqueen(level+1,n,x);
		}
	}
	else sum++;
}
void recall(int n)
{
	int x[n];
	sumqueen(0,n,x);
}
int main()
{
	int n;
	scanf("%d",&n);
	recall(n);
	printf("%d", sum);
	return 0;
}
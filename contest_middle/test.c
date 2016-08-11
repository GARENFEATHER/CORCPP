#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int* ss(int n)
{
	int a[n],i;
	for(i=0;i<n;i++)
		a[i]=i;
	return a;
}
int main()
{
	int n=9,*p;
	p=ss(n);
	printf("%d\n", p[n-1]);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long simplegcd(long long a,long long b)
{
	long long r;
	if(b != 0)
	{
		if(a >b)
		{
			r=a%b;
			a=b;
			b=r;
		}
		else
		{
			r=b%a;
			b=r;
		}
		simplegcd(a,b);
	}
	else return a;
}
int figure(long long x)
{
	int i;
	for(i=0;x!=0;i++)
		x=x/10;
	return i;
}
int* multiply(long long a,long long b,int ma,int mb)
{
	int M[ma][mb];
}
void caculate(long long a,long long b,long long m,long long n)
{
	int k;
	long tmp;
	tmp=simplegcd(a,b);
	a=a/tmp;
	b=b/tmp;
	k=simplegcd(m,n);
	
}
int main()
{
	unsigned long long a,b,m,n;
	scanf("%llu",&a);
	printf("%llu\n", a);
	return 0;
}
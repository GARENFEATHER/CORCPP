#include <stdio.h>
#include <stdlib.h>
#include <math.h>
unsigned long long mypow(unsigned long long x,unsigned long long y)
{
	unsigned long long result=1;
	int i;
	if(x == 0) return 0;
	else if(y == 0) return 1;
	for(i=0;i<y;i++)
		result=result*x;
	return result;
}
int figure(long long x)
{
	int i;
	for(i=0;x!=0;i++)
		x=x/10;
	return i;
}
long gcd(long a,long b)
{
	unsigned long long r;
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
		gcd(a,b);
	}
	else return a;
}
void cacu(long a,long b,long m,long n)
{
	unsigned long long result=0,fa,fb;
	long t;
	t=gcd(m,n);
	fa=mypow(a,t);
	fb=mypow(b,t);
	if(figure(a) >= 9 && t>=2)
	{
		result=fa-fb-8;
		result=result % 4294967296;
	}
	else
	{
		result=fa-fb;
		result=result % 4294967296;
	}
	printf("%llu\n", result);
}
int main()
{
	long a,b,m,n,tmp;
	scanf("%ld %ld %ld %ld",&a,&b,&m,&n);
	if(b > a)
	{
		tmp=a;
		a=b;
		b=tmp;
	}
	cacu(a,b,m,n);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
unsigned long long mypow(unsigned long long x,unsigned long long y)
{
	unsigned long long result=1;
	int i;
	for(i=0;i<y;i++)
		result=result*x;
	return result;
}
unsigned long long gcd(unsigned long long a,unsigned long long b)
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
void caculate(unsigned long long a,unsigned long long b,unsigned long long m,unsigned long long n)
{
	long long result;
	if(a == b && m == n) result=0;
	else if(m%n != 0) result=gcd(mypow(a,m)-mypow(b,m),mypow(a,n)-mypow(b,n)) % 4294967296;
	else result=(mypow(a,n)-mypow(b,n)) % 4294967296;
	printf("%lld\n", result);
}
int main()
{
	unsigned long long a,b,m,n,tmp;
	printf("%llu\n", 18446744073709551615+2);
	return 0;
}
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
long long int devide(long long int m,long long int n)
{
	long long int r;
	if(n!=0)
	{
		if(m>=n)
		{
			r=m%n; m=n; n=r;
		}
		else
		{
			r=n%m; n=r;
		}
		devide(m,n);
	}
	else return m;
}
int main()
{
	long long int m,n,result;
	scanf("%lld %lld",&m,&n);
	if(m!=0 && n!=0) result=devide(m,n);
	else result=0;
	printf("%lld",result);
	return 0;
}
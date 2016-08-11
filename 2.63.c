#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int sra(int x,int k)
{
	unsigned re;
	int xsrl = (unsigned) x >> k;
	int n=0,t,i;
	if(x < 0)
	{
		t=-x;
		while(t != 0)
		{
			t=t/2;
			n++;
		}
		xsrl=-(xsrl-1);
		xsrl=xsrl+pow(2,30)-1;
		xsrl=-xsrl;
	}
	return xsrl;
}
unsigned srl(unsigned x,int k)
{
	unsigned xsra = (int) x >> k;
	return xsra;
}
int main()
{
	unsigned y=178;
	int x=-161,k=2;
	//unsigned y;
	printf("%u %u\n",y >> k,srl(y,k));
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int signed_high_prod(int x,int y)
{
	int i=0,j,nx=0,ny=0,t,**s,*xe,*ye,ti,tj,k,sum,result=0;
	t=x;
	while(t != 0)
	{
		t=t/10;
		nx++;
	}
	xe=(int*)malloc(nx*sizeof(int));
	s=(int**)malloc(nx*sizeof(int*));
	t=x;
	while(i<nx)
	{
		xe[i]=t%10;
		t=t/10;
		i++;
	}
	i=0;
	t=y;
	while(t != 0)
	{
		t=t/10;
		ny++;
	}
	ye=(int*)malloc(ny*sizeof(int));
	t=y;
	while(i<ny)
	{
		ye[i]=t%10;
		t=t/10;
		i++
	}
	i=0;
	for(i=0;i<nx;i++)
	{
		s[i]=(int*)malloc(ny*sizeof(int));
		for(j=0;j<ny;j++)
			s[i][j]=xe[nx-1-i]*ye[ny-1-j];
	}
	xe=(int*)malloc((ny+nx-1)*sizeof(int));
	for(k=0,i=0,ti=0,tj=0,j=ny-1;k<ny+nx-1;k++)
	{
		sum=0;
		while(i+ti<nx && j+tj<ny)
		{
			sum=sum+s[i+ti][j+tj];
			ti++;
			tj++;
		}
		xe[k]=sum;
		if(i>0) j--;
		else i++;
	}
	sum=-1;
	for(i=ny+nx-2;i>=0;i--)
	{
		if(i-1 >= 0) xe[i-1]=xe[i-1]+xe[i]/10;
		else if(xe[i]/10 != 0) sum=xe[i]/10;
		xe[i]=xe[i]%10;
	}
	if(sum=-1) i=0;
	else
	{
		result=sum;
		i=1;
	}
	for(;i<w;i++)
		result=result*10+xe[i];
	return result;
}
unsigned unsigned_high_prod(unsigned x,unsigned y)
{
	int w = sizeof(unsigned) << 3;
	int 
	unsigned x_lmb = x >> (w - 1);
	unsigned y_lmb = y >> (w - 1);

	int temp = signed_high_prod((int)x , (int)y);

	return (unsigned)(temp + x_lmb * y + y_lmb * x);

}
int main()
{
	unsigned x=2147483647,y=214748367;
	unsigned_high_prod(x,y);
	return 0;
}
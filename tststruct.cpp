#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<time.h>
struct u
{
	int a,b,c;
	char i,*p,**lo;
	u *next;
};
int main()
{
	char **tmp;
	int i,j;
	u *d,s,*q;
	d=(u*)malloc(7*sizeof(u));
	q=(u*)malloc(7*sizeof(u));
	for(i=0;i<4;i++)
	{
	d[i].a=1;
	d[i].b=2;
	d[i].c=3;
	d[i].i='e';
	d[i].lo=(char**)malloc(2*sizeof(char*));
	for(j=0;j<2;j++)
		d[i].lo[j]=(char*)malloc(2*sizeof(char));
	d[i].p="heja";
	d[i].next=q;
	}
	d[2].a=55;

	s=d[0];
	d[0]=d[2];
	d[2]=s;
	getchar();

}
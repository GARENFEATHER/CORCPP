#include<stdio.h>
#include<stdlib.h>
int getchar(char *s)
{
	int sum=0,i;
	for(i=0;s[i]!='\0';i++)
		sum=sum*10+(s[i]-'0');
	return sum;
}
int main(int argc,char* argv[])
{
	int i=1,sum=0,temp;
	for(i=1;i<argc;i++)
	{
		temp=getchar(argv[i]);
		sum=sum+temp;
	}
	printf("%d",sum);
	return 0;
}
#include<iostream>
#include<stdlib.h>
#include<glut.h>
using namespace std;
bool ODD(char *s,int count)
{
	if(*s != '\0')
	{
		if(*s == '1') ODD(s+1,count+1);
		else ODD(s+1,count);
	}
	else
	{
		if(count%2 == 0) return false;//Å¼Êý
		else return true;
	}
}
int main()
{
	bool c=false;
	char *t="0000010100111111110";
	c=ODD(t,0);
	system("pasue");
}
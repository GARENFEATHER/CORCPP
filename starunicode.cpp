#include<iostream>
#include<stdlib.h>
using namespace std;
int main()
{
	int i,j,t;
	for(i=0;i<8;i++)
	{
		if(i>=4) t=7-i;
		else t=i;
		for(j=0;j<14;j++)
			if((j >= t && j <= t*2) || (j <= 13-t && j >= 13-t*2)) cout<<"#";
			else cout<<" ";
		cout<<endl;
	}
	system("pause");
}
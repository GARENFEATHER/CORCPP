#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;
int main()
{
	char tmp;
	string buffer[32];
	int n,i=0;
	ifstream fp;
	fp.open("1for1.txt",ios::in);
	if(!fp)
	{
		cout<<"no"<<endl;
		system("pause");
	}
	while(!fp.eof())
	{
		getline(fp,buffer[i],'\n');
		i++;
	}
	fp.close();
	cout<<n<<endl;
	system("pause");
}
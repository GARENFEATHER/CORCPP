#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<ctime>
#include<sys/timeb.h>
using namespace std;
struct timeb ls,le;
class basef
{
protected:int mm1;
public:void setm(int x,int y)
	   {
		   mm1=x;
		   cout<<"mm1:"<<mm1<<"\ny:"<<y<<endl;
	   }
	   virtual void quu()
	   {
		   cout<<"bsf here"<<endl;
	   }
};
class bases
{
protected:int mm2;
public:void setmm(int y)
	   {
		   mm2=y;
		   cout<<"mm2:"<<mm2<<endl;
	   }
};

class mul:public basef,public bases
{
public:
	void getans()
	{
		int re;
		re=mm1+mm2;
		cout<<"answer:"<<re<<endl;
	}
	void quu()
	{
		cout<<"derive here"<<endl;
	}
};
class Myclass
{
public:int plus(int,int);
	   double plus(double,double);
};
int Myclass::plus(int x,int y)
{ return x+y; }
double Myclass::plus(double x,double y)
{ return x-y; }
void main()
{
	fstream f1("3.1.txt",ios::in);
	fstream f2("A.txt",ios::in);
	fstream f3;
	long long tt;
	int i;
	double j;
	char c;
	ftime(&ls);
	while(!f1.eof())
	{
		f1>>i;
		cout<<i<<endl;
	}
	f1.close();
	while((c=f2.get()) != EOF) cout<<c;
	f2.close();
	f3.open("ahh.txt",ios::out);
	f3<<128<<' '<<122.3<<" ahhhhh\n"<<c<<endl;
	f3.close();
	f3.open("ahh.txt",ios::in);
	f3>>i>>j;
	cout<<"\n"<<i<<" "<<c<<" "<<j<<endl;
	f3.close();
	/*Myclass Data;
	basef *p,bsf;
	mul dd;
	p=&dd;
	cout<<"answer:"<<Data.plus(1,3)<<endl;
	cout<<"answer:"<<Data.plus(4.4,1.0)<<endl;
	dd.setmm(100);
	dd.setm(19,20);
	p->quu();
	p=&bsf;
	dd.quu();
	dd.getans();*/
	ftime(&le);
	tt=(long long)(le.time*1000+le.millitm)-(long long)(ls.time*1000+ls.millitm);
	cout<<tt<<"Ê±³¤"<<endl;
	system("pause");
}

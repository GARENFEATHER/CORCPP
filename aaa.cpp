#include<iostream>
#include<math.h>
#include<stdlib.h>
using namespace std;
class Myclass
{
int x;
public:Myclass();
	   void display();
	   int plus(int,int);
	   double plus(double,double);
	   Myclass operator++();
	   Myclass operator++(int);
};
Myclass::Myclass()
{ x=22; }
void Myclass::display()
{ cout<<"answer:"<<x<<endl; }
int Myclass::plus(int x,int y)
{ return x+y; }
double Myclass::plus(double x,double y)
{ return x-y; }
Myclass Myclass::operator++()//Ç°ÖÃ
{
	Myclass a;
	x++;
	a.x=x;
	return a;
}
Myclass Myclass::operator++(int)//ºóÖÃ
{
	Myclass a;
	x=x-9;
	a.x=x;
	return a;
}
int main()
{
	Myclass Data,Y;
	Data++;
	cout<<"answer:"<<Data.plus(1,3)<<endl;
	cout<<"answer:"<<Data.plus(4.4,1.0)<<endl;
	Data.display();
	return 0;
}

#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<time.h>
#include<array>
using namespace std;
struct Tree
{
	int data;
	Tree *left,*right;
};
void randomtree()
{
	int n=300,i;
	ofstream out("tst.txt",ios::out);
	srand((unsigned)time(NULL));
	out<<n<<endl;
	for(i=0;i<n;i++)
		out<<rand()<<" ";
}
Tree* searchtree(Tree *T,int target)
{
	Tree *p,*f;
	if(T)
	{
		p=f=T;
		while(p != NULL)
		{
			if(p->data > target)
			{
				f=p;
				p=p->left;
			}
			else if(p->data < target)
			{
				f=p;
				p=p->right;
			}
			else return NULL;
		}
		return f;
	}
	else return NULL;
}
Tree* createtree()
{
	Tree *T,*f,*p;
	int data;
	ifstream in("tst.txt",ios::in);
	in>>data;
	T=(Tree*)malloc(sizeof(Tree));
	T->data=data;
	T->left=NULL;
	T->right=NULL;
	while(!in.eof())
	{
		in>>data;
		f=searchtree(T,data);
		if(f != NULL)
		{
			p=(Tree*)malloc(sizeof(Tree));
			p->data=data;
			p->left=NULL;
			p->right=NULL;
			if(data > f->data) f->right=p;
			else f->left=p;
		}
	}
	return T;
}
int successor(Tree *T,int x)
{
	Tree *f,*p;
	f=searchtree(T,x);
	p=f;
	if(f != NULL)
		if(f->left->data == x) f=f->left;
		else f=f->right;
	if(f->right != NULL)
	{
		p=f->right;
		while(p->left != NULL) p=p->left;
		return p->data;
	}
	else
	{

	}

}
int predecessor(int x)
{
	
}
inline int squere(int x)
{
	return x*x;
}
int main()
{
	int c=3,r;
	Tree *T;
	//randomtree();
	//T=createtree();
	r=squere(c++);
	getchar();
}
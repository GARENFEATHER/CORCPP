#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
typedef struct s
{
	int value;
	struct s *next;
}Node;
int Create(Node **L)
{
	Node *p,*head,*t;
	int n,i,tmp;
	srand((unsigned)time(NULL));
	n=rand()%20+8;
	head=(Node*)malloc(sizeof(Node));
	t=p=head;
	head->value=rand();
	for(i=0;i<n;i++)
	{
		tmp=rand();
		p=(Node*)malloc(sizeof(Node));
		p->value=tmp;
		t->next=p;
		t=p;
	}
	t->next=NULL;
	*L=head;
	return n;
}
void display(Node *L)
{
	Node *p;
	p=L;
	while(p != NULL)
	{
		cout<<p->value<<" ";
		p=p->next;
	}
	cout<<"\n"<<endl;
}
void reverse(int n,Node **L)
{
	int i;
	Node *p,*t,*q;
	t=*L;
	if(n >= 3)
	{
		p=t;
		q=p->next;
		for(i=0;i<n;i++)
		{
			t=p;
			p=q;
			q=q->next;
			p->next=t;
			if(i == 0) t->next=NULL;
		}
		*L=p;
	}
	else
	{
		if (n == 1 || *L == NULL) return;
		else
		{
			p=t->next;
			p->next=t;
			t->next=NULL;
		}
	}
}
int main()
{
	int n;
	Node *L;
	n=Create(&L);
	display(L);
	reverse(n,&L);
	display(L);
	system("pause");
}
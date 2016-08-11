#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#pragma warning (disable:4100)
#pragma warning (disable:4996)

typedef struct s {
	char c;
	struct s *next;
}Node;

//输出array数组
void display(Node *array[], int arsz) 
{
	cout << "array[0]: ";
	for (Node *p = array[0]; p != NULL; p = p->next)
//	for (Node *p = array[0]->next; p != NULL; p = p->next) 
	{
		cout << p->c << "->";
	}
	cout << "NULL" << endl;
	cout << "array[1]: ";
	for (Node *p = array[1]; p != NULL; p = p->next)
//	for (Node *p = array[1]->next; p != NULL; p = p->next)
	{
		cout << p->c << "->";
	}
	cout << "NULL" << endl;
	cout<< endl;
}

Node* create(char str[])
{
	int i=0,n=0;
	Node *p,*head,*t;
	while(str[n] != '\0') n++;
	p=(Node*)malloc(sizeof(Node));
	head=p;
	if(n != 0)
	{
		i=0;
		while(i<n)
		{
			p->c=str[i];
			p->next=(Node*)malloc(sizeof(Node));
			t=p;
			p=p->next;
			i++;
		}
		t->next=NULL;
		return head;
	}
	else return NULL;
}
void sort(char str[])
{
	int n=0,i,j;
	char tmp;
	while(str[n]  !='\0') n++;
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++)
			if(str[j]>str[j+1])
			{
				tmp=str[j];
				str[j]=str[j+1];
				str[j+1]=tmp;
			}
}
Node* insert1(Node *head,char str[])
{
	Node *p,*pn,*t;
	int i=0,n=0;
	while(str[n]  !='\0') n++;
	if(head != NULL) pn=p=head;
	else
	{
		pn=p=(Node*)malloc(sizeof(Node));
		p->c=str[i];
		i++;
	}
	while(p != NULL && i<n)
	{
		pn=(Node*)malloc(sizeof(Node));
		pn->c=str[i];
		pn->next=p->next;
		p->next=pn;
		p=pn->next;
		i++;
	}
	if(i<n)
	{
		pn->next=(Node*)malloc(sizeof(Node));
		pn=pn->next;
		pn->c=str[i++];
	}
	while(i<n)
	{
		pn->next=(Node*)malloc(sizeof(Node));
		pn=pn->next;
		pn->c=str[i];
		i++;
	}
	pn=pn->next;
	pn->next=NULL;
	return head;
}
Node* insert2(Node *head,char *str)
{
	Node *p,*pn,*t;
	int n=0,i=0;
	while(str[n]  !='\0') n++;
	sort(str);
	if(head != NULL ) t=p=head;
	else
	{
		t=p=(Node*)malloc(sizeof(Node));
		p->c=str[i];
		i++;
	}
	while(p != NULL && i<n)
	{
		if(str[i] <= p->c)
		{
			if(t!=p)
			{
				pn=(Node*)malloc(sizeof(Node));
				pn->c=str[i];
				t->next=pn;
				pn->next=p;
				t=t->next;
			}
			else
			{
				t=(Node*)malloc(sizeof(Node));
				t->c=str[i];
				t->next=p;
				head=t;
			}
		i++;
		}
		else
		{
			t=p;
			p=p->next;
		}
	}
	if(p == NULL && i<n)
	{
		while(i<n)
		{
			p=(Node*)malloc(sizeof(Node));
			p->c=str[i];
			t->next=p;
			t=p;
			i++;
}
	}
	
	return head;
}
void deleteSame(Node *array[])
{
	Node *p1,*p2,*tmp;
	p1=array[0];
	p2=array[1];
	while(p1 != NULL && p2 != NULL)
	{
		if(p1->c == p2->c)
		{
			p1->next=p1->next->next;
			p2->next=p2->next->next;
		}
		p1=p1->next;
		p2=p2->next;
	}
}
#define STRSIZE 30
#define ARRSIZE 2
int main() 
{
	char str1[STRSIZE]="china", str2[STRSIZE]="usa";


	/*cout << "请输入两个字符串：" << endl;

	gets(str1);
	gets(str2);*/



	Node *array[ARRSIZE];

	array[0]=NULL;
	array[1]=NULL;

	cout << endl;

	cout << "将第1个字符串以原始顺序建立链表，用array[0]指向该链表：" << endl;
	array[0]=create(str1);
	display(array, ARRSIZE);

	
	cout << "将第1个字符串以字典顺序建立链表，用array[1]指向该链表：" << endl;
	sort(str1);

	array[1]=create(str1);
	display(array, ARRSIZE);

	
	cout << "将第2个字符串以一个间一个的方式插入array[0]后面的链表：" << endl;
	array[0] = insert1(array[0], str2);
	display(array, ARRSIZE);
	
	cout << "将第2个字符串以字典序插入array[1]后面的链表：" << endl;
	array[1] = insert2(array[1], str2);
	display(array, ARRSIZE);
	
	cout << "删除array[0]和array[1]后面的链表中对应位置字符相同的结点：" << endl;
	deleteSame(array);
	display(array, ARRSIZE);
	
	system("pause");
	return 0;
}
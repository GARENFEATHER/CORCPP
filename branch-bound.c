#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
typedef struct s
{
	int currentValue,currentWeight,nodeCount;
	int *nodeChoses;
	double upboundValue;
	struct s *left,*right;
}Node;
typedef struct o
{
	int weight,value;
	double valuePerWeight;
}item;
typedef struct l
{
	Node **base,*head,*tail;
	int space;
}queue;
int currentMaxValue=0;
Node currentMaxNode;
Node* newnode(Node *parent,int n)
{
	Node *p;
	p=(Node*)malloc(sizeof(Node));
	p->nodeChoses=(int*)malloc(n*sizeof(int));
	if(parent == NULL)
	{
		p->currentValue=0;
		p->currentWeight=0;
		p->nodeCount=0;
		for(i=0;i<n;i++)
			p->nodeChoses[i]=0;
	}
	else
	{
		p->currentValue=parent->currentValue;
		p->currentWeight=parent->currentWeight;
		p->nodeCount=parent->nodeCount+1;
		for(i=0;i<n;i++)
			p->nodeChoses[i]=parent->nodeChoses[i];
	}
	return p;
}
void upBound(Node *p,int n,int w,item *c)
{
	int i;
	for(i=0;i<n;i++)
		if(p->nodeChoses[i] == 0) break;
	if(i != n)
		p->upboundValue=p->currentValue+w*c[i].valuePerWeight;
	else p->upboundValue=p->currentValue;
}
void branchAndBound(FILE *fp,int w,int n)
{
	Node *p,*T;
	queue L;
	item c[n];
	int i;
	for(i=0;i<n;i++)
	{
		fscanf(fp,"%d %d",&c[i].weight,&c[i].value[i]);
		c[i].valuePerWeight=1.0*c[i].value[i]/c[i].weight;
	}
	sort(c);
	L.space=100;
	L.base=(Node**)malloc(L.space*sizeof(Node*));
	L.base[0]=(Node*)malloc(sizeof(Node));
	L.base[0]->currentValue=0;
	L.base[0]->currentWeight=0;
	L.base[0]->nodeCount=0;
	upBound(L.base[0],n,w,c);
	L.head=L.tail=L.base[0];
	L.tail++;
	while(L.head != L.tail)
	{

	}
}
int main()
{
	FILE *fp,*out;
	int i,w,n;
	fp=fopen("bagdata/beibao0.in","r");
	fscanf(fp,"%d %d",&w,&n);
	branchAndBound(fp,w,n);
}
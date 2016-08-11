#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/timeb.h>
typedef struct s
{
	int data;
	struct s *next;
}Node;
struct _timeb s,e;
Node* create(int *tmp,int n)
{
	Node *L,*p,*t;
	int i;
	for(i=0;i<n;i++)
	{
		if(i == 0)
		{
			L=(Node*)malloc(n*sizeof(Node));
			L->data=tmp[i];
			t=p=L;
		}
		else
		{
			p=(Node*)malloc(n*sizeof(Node));
			p->data=tmp[i];
			t->next=p;
			t=p;
		}
	}
	t->next=NULL;
	return L;
}
void display(Node *L)
{
	Node *p=L;
	if(L == NULL)
	{
		printf("NULL\n");
		return;
	}
	while(p != NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
}
void sort(int *num,int n)
{
	int i,j,tmp;
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++)
			if(num[j] > num[j+1])
			{
				tmp=num[j];
				num[j]=num[j+1];
				num[j+1]=tmp;
			}
}
void del(Node **L1,Node **L2,int na,int nb)
{
	int j,k=0,*data,i;
	Node *p,*b;
	data=(int*)malloc((na+nb)*sizeof(int));
	p=*L1;
	while(p != NULL)
	{
		data[k++]=p->data;
		p=p->next;
	}
	p=*L2;
	while(p != NULL)
	{
		data[k++]=p->data;
		p=p->next;
	}
	sort(data,na+nb);
	for(i=0;i<k-1;i++)
	{
		if(data[i] == data[i+1])
		{
			for(j=0;j<2;j++)
			{
				if(j == 0) b=p=*L1;
				else b=p=*L2;
				while(p != NULL)
				{
					if(p->data == data[i])
					{
						if(b == p)
						{
							if(j == 0)
							{
								*L1=(*L1)->next;
								b=p=*L1;
							}
							else
							{
								*L2=(*L2)->next;
								b=p=*L1;
							}
						}
						else
						{
							b->next=p->next;
							p=p->next;
						}
					}
					else
					{
						b=p;
						p=p->next;
					}
				}
			}
		}
	}
}
int main()
{
	long long t;
	FILE *fp;
	Node *la,*lb;
	int na,nb,i,*tmp;
	double d;
	fp=fopen("3.1.txt","r");
	printf("请输入链表A的长度:");
	fscanf(fp,"%d",&na);
	printf("请输入链表A中节点的data:\n");

	tmp=(int* )malloc(na*sizeof(int));
	for(i=0;i<na;i++)
		fscanf(fp,"%d",&tmp[i]);
	if(na != 0) la=create(tmp,na);

	printf("请输入链表B的长度:");
	fscanf(fp,"%d",&nb);
	printf("请输入链表B中节点的data:\n");

	free(tmp);
	tmp=(int* )malloc(nb*sizeof(int));
	for(i=0;i<nb;i++)
		fscanf(fp,"%d",&tmp[i]);
	if(nb != 0) lb=create(tmp,nb);

	printf("原始链表A:\n");
	display(la);
	printf("原始链表B:\n");
	display(lb);

	del(&la,&lb,na,nb);//备注：如果这里使用(la,lb,na,nb)的话，在函数内操作指针并不会改变指针指向的对象
	printf("删除相同值后的链表A:\n");
	display(la);
	printf("删除相同值后的链表B:\n");
	display(lb);
	printf("\n%lf s\n",d);
	system("pause");
}
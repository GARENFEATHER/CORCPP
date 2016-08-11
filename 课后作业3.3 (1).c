#include<stdio.h>
#include<stdlib.h>
typedef struct s{
	int a[10];
	struct s *next;
}Node;
void display(Node *L,int mark)
{
	int i,n;
	Node *p;
	p=L;
	printf("������ṹΪ:\n");
	while(p != NULL)
	{
		if(p->next == NULL) n=mark;
		else n=10;
		printf("[");
		for(i=0;i<n;i++)
			if(i == n-1) printf("%d",p->a[i]);
			else printf("%d,",p->a[i]);
		printf("] -> ");
		p=p->next;
	}
	printf("NULL\n\n");
}
void insert(int *num,int n,Node **L,int *mark)
{
	int k=0,i;
	Node *p;
	if(*L != NULL)
	{
		p=*L;
		while(p->next != NULL) p=p->next;
	}
	else
	{
		*L=(Node*)malloc(sizeof(Node));
		(*L)->next=NULL;
		*mark=0;
		p=*L;
	}
	while(k<n)
	{
		if(*mark == 10)
		{
			p->next=(Node*)malloc(sizeof(Node));
			*mark=0;
			p=p->next;
			p->next=NULL;
		}
		for(;(*mark)<10 && k<n;(*mark)++)
			p->a[*mark]=num[k++];
	}
	printf("�������");
	display(*L,*mark);
}
int Remove(Node **L,int *mark)
{
	int x;
	Node *p,*t;
	if(*L == NULL)
	{
		printf("����Ϊ�գ�����ɾ��\n\n");
		return;
	}
	t=p=*L;
	while(p->next != NULL)
	{
		t=p;
		p=p->next;
	}
	(*mark)--;
	x=p->a[*mark];
	if((*mark) == 0)
	{
		if(p == t) *L=NULL;
		else *mark=10;
		free(p);
		t->next=NULL;
	}
	printf("ɾ����%d��",x);
	display(*L,*mark);
	return x;
}
int main()
{
	int n,*num,i,mark;
	char c;
	Node *L;
	L=NULL;
	while(1)//��������Ī����ʾ����
	{
		printf("������Ҫ���еĲ�����i��ʾ����һ����������r��ʾɾ�����һ������q��ʾ�˳�����\n");
		scanf("%c",&c);
		if(c == 'q') return;
		else if(c == 'i')
		{
			printf("������Ҫ����������ĸ�����\n");
			scanf("%d",&n);
			num=(int*)malloc(n*sizeof(int));
			printf("������Ҫ�����������\n");
			for(i=0;i<n;i++)
				scanf("%d",&num[i]);
			insert(num,n,&L,&mark);
		}
		else if(c == 'r') Remove(&L,&mark);
		else printf("�������\n\n");
		getchar();//����������ε���֮bug
	}
}
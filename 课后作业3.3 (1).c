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
	printf("，链表结构为:\n");
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
	printf("插入完成");
	display(*L,*mark);
}
int Remove(Node **L,int *mark)
{
	int x;
	Node *p,*t;
	if(*L == NULL)
	{
		printf("链表为空，不能删除\n\n");
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
	printf("删除了%d后",x);
	display(*L,*mark);
	return x;
}
int main()
{
	int n,*num,i,mark;
	char c;
	Node *L;
	L=NULL;
	while(1)//输入错误会莫名显示两次
	{
		printf("请输入要进行的操作（i表示插入一个或多个数，r表示删除最后一个数，q表示退出）：\n");
		scanf("%c",&c);
		if(c == 'q') return;
		else if(c == 'i')
		{
			printf("请输入要插入的整数的个数：\n");
			scanf("%d",&n);
			num=(int*)malloc(n*sizeof(int));
			printf("请输入要插入的整数：\n");
			for(i=0;i<n;i++)
				scanf("%d",&num[i]);
			insert(num,n,&L,&mark);
		}
		else if(c == 'r') Remove(&L,&mark);
		else printf("输入错误\n\n");
		getchar();//解决输入两次的迷之bug
	}
}
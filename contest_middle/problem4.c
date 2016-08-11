#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//流氓算法
typedef struct o
{
	int value;
	struct o *next;
}loop;
loop* listget()
{
	int i;
	loop *head,*p,*t;
	head=NULL;
	for(i=1;i<=9;i++)
	{
		p=(loop*)malloc(sizeof(loop));
		p->value=i;
		p->next=NULL;
		if(head == NULL) head=t=p;
		else
		{
			t->next=p;
			t=t->next;
		}
	}
	p->next=head;
	return head;
}
void Create(int origin[9][9],int start,int init)
{
	int i,r,change[9],j,c;
	srand((unsigned)time(NULL));
	loop *head,*t,*p;
	head=listget();
	p=head;
	for(i=0;i<9;i++)
	{
		r=rand()%9+1;
		for(c=0;c<r;c++)
		{
			if(c == r-1) t=p;
			p=p->next;
		}
		change[i]=p->value;
		t->next=p->next;
		p=t;
	}
	for(i=0;i<9;i++)
		if(change[i] == start) break;
	r=change[i];
	change[i]=change[init-1];
	change[init-1]=r;
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			origin[i][j]=change[origin[i][j]-1];
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(j != 8) printf("%d ",origin[i][j]);
			else printf("%d",origin[i][j]);
		}
		printf("\n");
	}

}
int main()
{
	int start,init,origin[9][9]={{6,1,3,2,7,4,5,8,9},{8,9,5,6,3,1,7,2,4},{2,4,7,5,8,9,3,1,6},{9,5,8,3,4,2,1,6,7},{1,3,6,8,9,7,2,4,5},{4,7,2,1,5,6,9,3,8},{3,8,4,7,1,5,6,9,2},{5,2,1,9,6,8,4,7,3},{7,6,9,4,2,3,8,5,1}};
	scanf("%d",&start);
	init=origin[0][0];
	Create(origin,start,init);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
typedef struct s
{
	struct s *next;
	int target,value;
}arc;
void bellmanford(arc *XY,int n,arc **end,int *pv)
{
	int i,j,*final,*prepoint,*D;
	arc *p,*t,**prearc;
	final=(int*)malloc((2*n+2)*sizeof(int));
	D=(int*)malloc((2*n+2)*sizeof(int));
	prepoint=(int*)malloc((2*n+2)*sizeof(int));
	prearc=(arc**)malloc((2*n+2)*sizeof(arc*));
	prepoint[0]=0;
	prearc[0]=NULL;
	D[0]=0;
	final[0]=1;
	for(i=1;i<2*n+2;i++)
	{
		D[i]=INT_MAX;
		final[i]=0;
		prepoint[i]=-1;
	}
	p=XY[0].next;
	t=XY+0;
	while(p != NULL)
	{
		D[p->target]=p->value;
		prepoint[p->target]=0;
		prearc[p->target]=t;
		t=p;
		p=p->next;
	}
	for(i=1;i<=2*n+2;i++)
	{
		for(j=0;j<2*n+2;j++)
		{
			t=XY+j;
			p=t->next;
			while(p != NULL)
			{
				if(D[j] != INT_MAX && D[j]+p->value < D[p->target])//INT_MAXµÄÎÊÌâ
				{
					prearc[p->target]=t;
					prepoint[p->target]=j;
					D[p->target]=D[j]+p->value;
				}
				t=p;
				p=p->next;
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		p=XY[i].next;
		while(p != NULL)
		{
			p->value=D[i]+p->value-D[p->target];
			p=p->next;
		}
	}
	i=2*n+1;
	while(i != 0)
	{
		p=prearc[i]->next;
		prearc[i]->next=p->next;
		p->next=NULL;
		p->target=prepoint[i];
		if(XY[i].next != NULL)
		{
			end[i]->next=p;
			end[i]=p;
		}
		else
		{
			XY[i].next=p;
			end[i]=p;
		}
		i=prepoint[i];
		if(i == 0) break;
	}
	for(i=1;i<2*n+1;i++)
		pv[i]=pv[i]+D[i];
}
void assignment(int n,arc *XY,arc **end)
{
	int i,*pv,cost=0;
	pv=(int*)malloc((2*n+2)*sizeof(int));
	for(i=0;i<2*n+2;i++)
		pv[i]=0;
	while(XY[0].next != NULL)
		bellmanford(XY,n,end,pv);
	for(i=1;i<=n;i++)
		cost=cost+pv[i+n]-pv[i];
	printf("%d\n",cost);
}
int main()
{
	arc *XY,*p1,*p2,**end;
	int m,n,i,a,b,v;
	// FILE *fp;
	// fp=fopen("assignment.txt","r");
	scanf("%d %d",&n,&m);
	end=(arc**)malloc((2*n+2)*sizeof(arc*));
	XY=(arc*)malloc((2*n+2)*sizeof(arc));
	XY[2*n+1].next=NULL;
	end[2*n+1]=NULL;
	for(i=1;i<=n;i++)
	{
		XY[i].next=NULL;
		end[i]=NULL;
		p1=(arc*)malloc(sizeof(arc));
		p1->next=NULL;
		p1->target=i;
		p1->value=0;
		p2=(arc*)malloc(sizeof(arc));
		p2->next=NULL;
		p2->target=2*n+1;
		p2->value=0;
		if(i == 1)
		{
			XY[0].next=p1;
			end[0]=p1;
		}
		else
		{
			end[0]->next=p1;
			end[0]=p1;
		}
		XY[i+n].next=p2;
		end[i+n]=p2;
	}
	for(i=0;i<m;i++)
	{
		scanf("%d %d %d",&a,&b,&v);
		p1=(arc*)malloc(sizeof(arc));
		p1->next=NULL;
		p1->target=b+n;
		p1->value=v;
		if(XY[a].next == NULL)
		{
			XY[a].next=p1;
			end[a]=p1;
		}
		else
		{
			end[a]->next=p1;
			end[a]=p1;
		}
	}
	//fclose(fp);
	assignment(n,XY,end);
	return 0;
}
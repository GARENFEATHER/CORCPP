#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
typedef struct s
{
	int target;
	double value;
	struct s *next;
}edge;
void Djkstra(int n,edge *arc)
{
	int start=0,i,u=0,j;
	edge *p;
	double *D,min;
	int *final;
	final=(int*)malloc(n*sizeof(int));
	D=(double*)malloc(n*sizeof(double));
	for(i=0;i<n;i++)
	{
		if(i == start)
		{
			final[i]=1;
			D[i]=0.0;
		}
		else
		{
			final[i]=0;
			D[i]=DBL_MAX;
		}
	}
	p=arc[start].next;
	while(p != NULL)
	{
		D[p->target]=p->value;
		p=p->next;
	}
	for(i=1;i<n;i++)
	{
		for(j=1,min=DBL_MAX;j<n;j++)
		{
			if(!final[j] && D[j] < min)
			{
				u=j;
				min=D[j];
			}
		}
		p=arc[u].next;
		final[u]=1;
		while(p != NULL)
		{
			if(!final[p->target] && p->value+min < D[p->target])
				D[p->target]=p->value+min;
			p=p->next;
		}
	}
	printf("%.2lf",D[n-1]);
}
int main()
{
	int n,m,i,origin,target;
	double v;
	edge *arc,*p,*pn;
	scanf("%d %d",&n,&m);
	arc=(edge*)malloc(n*sizeof(edge));
	for(i=0;i<n;i++)
	{
		arc[i].next=NULL;
		arc[i].target=i;
	}
	for(i=0;i<m;i++)
	{
		scanf("%d %d %lf",&origin,&target,&v);
		p=arc+origin;
		while(p->next != NULL) p=p->next;
		pn=(edge*)malloc(sizeof(edge));
		pn->target=target;
		pn->next=NULL;
		pn->value=v;
		p->next=pn;
		p=arc+target;
		while(p->next != NULL) p=p->next;
		pn=(edge*)malloc(sizeof(edge));
		pn->target=origin;
		pn->next=NULL;
		pn->value=v;
		p->next=pn;
	}
	Djkstra(n,arc);
	getchar();
}
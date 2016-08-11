#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct s
{
	int x,y;
}point;
typedef struct a
{
	double a,b;
	char m;
}line;
typedef struct u
{
	int n,vx,vy;
	struct s *pn;
	struct a *ln;
}Gra;
void Line(point p1,point p2,line *l1)
{
	(*l1).a=1.0*(p2.y-p1.y)/(p2.x-p1.x);
	(*l1).b=1.0*(p2.x*p1.y-p1.x*p2.y)/(p2.x-p1.x);
}
double trian(point a,point b,point c)
{
	double l1,l2,l3,p,s;
	l1=sqrt(1.0*(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	l2=sqrt(1.0*(b.x-c.x)*(b.x-c.x)+(b.y-c.y)*(b.y-c.y));
	l3=sqrt(1.0*(c.x-a.x)*(c.x-a.x)+(c.y-a.y)*(c.y-a.y));
	p=(l1+l2+l3)/2;
	s=sqrt((p*(p-l1)*(p-l2)*(p-l3)));
	return s;
}
double area(int n,point *p)
{
	int i;
	double s=0.0;
	for(i=1;i<n-2;i++)
		s=s+trian(p[0],p[i],p[i+1]);
	return s;
}
int intersection(Gra g,point p)//判断点是否在图内
{
	int i,a,b,y;
	char pm;
	for(i=0;i<g.n;i++)
	{
		a=g.ln[i].a;
		b=g.ln[i].b;
		y=a*p.x+b;
		if(y > p.y) pm='s';
		else pm='b';
		if(pm != g.ln[i].m) return 0;
	}
	return 1;
}
void linecre(Gra *ga,Gra *gb)
{
	int i,midpx,midpy;
	midpx=((*ga).pn[0].x + (*ga).pn[1].x + (*ga).pn[2].x) / 3;
	midpy=((*ga).pn[0].y + (*ga).pn[1].y + (*ga).pn[2].y) / 3;
	for(i=0;i<(*ga).n;i++)
	{
		int ty;
		double a,b;
		if(i != (*ga).n-1) Line((*ga).pn[i],(*ga).pn[i+1],(*ga).ln+i);
		else Line((*ga).pn[(*ga).n-1],(*ga).pn[0],(*ga).ln+(*ga).n-1);
		a=(*ga).ln[i].a;
		b=(*ga).ln[i].b;
		ty=a*midpx+b;
		if(ty > midpy) (*ga).ln[i].m = 's';
		else (*ga).ln[i].m = 'b';
	}
	midpx=((*gb).pn[0].x + (*gb).pn[1].x + (*gb).pn[2].x) / 3;
	midpy=((*gb).pn[0].y + (*gb).pn[1].y + (*gb).pn[2].y) / 3;
	for(i=0;i<(*gb).n;i++)
	{
		int ty;
		double a,b;
		if(i != (*gb).n-1) Line((*gb).pn[i],(*gb).pn[i+1],(*gb).ln+i);
		else Line((*gb).pn[(*gb).n-1],(*gb).pn[0],(*gb).ln+(*gb).n-1);
		a=(*gb).ln[i].a;
		b=(*gb).ln[i].b;
		ty=a*midpx+b;
		if(ty > midpy) (*gb).ln[i].m = 's';
		else (*gb).ln[i].m = 'b';
	}
}
double caculate(Gra *ga,Gra *gb)
{
	int i,x1,x2,y1,y2,j;
	for(i=1;/*不知道什么条件停止*/;i++)
	{
		for(j=0;j<(*ga).n;j++)
		{
			(*ga).pn[j].x=(*ga).pn[j].x+(*ga).vx;
			(*ga).pn[j].y=(*ga).pn[j].y+(*ga).vy;
			if(j != 0)
			{
				x1=(*ga).pn[j-1].x;
				x2=(*ga).pn[j].x;
				y1=(*ga).pn[j-1].y;
				y2=(*ga).pn[j].x;
				(*ga).ln[j-1].b=1.0*(x2*y1-x1*y2)/(x2-x1);
			}
		}
		x1=(*ga).pn[j-1].x;
		x2=(*ga).pn[0].x;
		y1=(*ga).pn[j-1].y;
		y2=(*ga).pn[0].x;
		(*ga).ln[j-1].b=1.0*(x2*y1-x1*y2)/(x2-x1);
		for(j=0;j<(*gb).n;j++)
		{
			(*gb).pn[j].x=(*gb).pn[j].x+(*gb).vx;
			(*gb).pn[j].y=(*gb).pn[j].y+(*gb).vy;
			if (j != 0)
			{
				x1=(*gb).pn[j-1].x;
				x2=(*gb).pn[j].x;
				y1=(*gb).pn[j-1].y;
				y2=(*gb).pn[j].x;
				(*gb).ln[j-1].b=1.0*(x2*y1-x1*y2)/(x2-x1);
			}
		}
		x1=(*gb).pn[j-1].x;
		x2=(*gb).pn[0].x;
		y1=(*gb).pn[j-1].y;
		y2=(*gb).pn[0].x;
		(*gb).ln[j-1].b=1.0*(x2*y1-x1*y2)/(x2-x1);
	}
}
int main()
{
	int i;
	FILE *fp;
	Gra ga,gb;
	fp=fopen("in1.txt","r");
	fscanf(fp,"%d",&ga.n);
	ga.pn=(point*)malloc(ga.n*sizeof(point));
	ga.ln=(line*)malloc(ga.n*sizeof(line));
	for(i=0;i<ga.n;i++)
		fscanf(fp,"%d %d",&ga.pn[i].x,&ga.pn[i].y);
	fscanf(fp,"%d %d",&ga.vx,&ga.vy);
	fscanf(fp,"%d",&gb.n);
	gb.pn=(point*)malloc(gb.n*sizeof(point));
	gb.ln=(line*)malloc(gb.n*sizeof(line));
	for(i=0;i<gb.n;i++)
		fscanf(fp,"%d %d",&gb.pn[i].x,&gb.pn[i].y);
	fscanf(fp,"%d %d",&gb.vx,&gb.vy);
	caculate(&ga,&gb);
	return 0;
}
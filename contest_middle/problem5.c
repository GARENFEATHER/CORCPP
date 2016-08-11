#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct s
{
	int n;
	int x[9],y[9];
}empty;
typedef struct p
{
	empty row[9],col[9],square[9];
	int matrix[9][9];
}Iterator;
typedef struct o
{
	int value;
	struct o *next;
}possible;
int find=0;
Iterator Copy(empty row[9],empty col[9],empty square[9],int s[9][9],int x,int y,int value)
{
	int i,j;
	Iterator c;
	for(i=0;i<9;i++)
	{
		c.row[i]=row[i];
		c.col[i]=col[i];
		c.square[i]=square[i];
		if(i == x)
		{
			for(j=0;j<row[i].n;j++)
				if(y == row[i].y[j])
				{
					c.row[i].y[j]=row[i].y[row[i].n-1];
					break;
				}
		}
		if(y == i)
		{
			for(j=0;j<col[i].n;j++)
				if(x == col[i].x[j])
				{
					c.col[i].x[j]=col[i].x[col[i].n-1];
					break;
				}
		}
		if(i == x/3*3+y/3)
		{
			for(j=0;j<square[i].n;j++)
				if(x == square[i].x[j] && y == square[i].y[j])
				{
					c.square[i].x[j]=square[i].x[square[i].n-1];
					c.square[i].y[j]=square[i].y[square[i].n-1];
					break;
				}
		}
		for(j=0;j<9;j++)
			c.matrix[i][j]=s[i][j];
	}
	c.matrix[x][y]=value;
	c.row[x].n--;
	c.col[y].n--;
	c.square[x/3*3+y/3].n--;
	return c;
}
possible* valueget(int s[9][9],int x,int y)
{
	int result[9],startx,starty,i,j;
	possible *p,*head,*t;
	head=NULL;
	startx=x/3*3;
	starty=y/3*3;
	for(i=0;i<9;i++)
		result[i]=1;
	for(i=0;i<9;i++)
	{
		if(s[x][i] != 0) result[s[x][i]-1]=0;
		if(s[i][y] != 0) result[s[i][y]-1]=0;
	}
	for(i=startx;i<startx+3;i++)
		for(j=starty;j<starty+3;j++)
			if(s[i][j] != 0) result[s[i][j]-1]=0;
	for(i=0;i<9;i++)
		if(result[i] != 0)
		{
			p=(possible*)malloc(sizeof(possible));
			p->value=i+1;
			p->next=NULL;
			if(head == NULL)
			{
				head=p;
				t=p;
			}
			else
			{
				t->next=p;
				t=p;
			}
		}
	return head;
}
void fill(empty row[9],empty col[9],empty square[9],int s[9][9],int emp)
{
	int i,x,y,j,n;
	possible *p,*t;
	Iterator tmp;
	if(emp != 0)
	{
		if(find == 1) return;
		n=10;
		for(i=0;i<9;i++)
		{
			if(row[i].n != 0 && row[i].n < n)
			{
				n=row[i].n;
				x=row[i].x[n-1];
				y=row[i].y[n-1];
			}
			if(col[i].n != 0 && col[i].n < n)
			{
				n=col[i].n;
				x=col[i].x[n-1];
				y=col[i].y[n-1];
			}
			if(square[i].n != 0 && square[i].n < n)
			{
				n=square[i].n;
				x=square[i].x[n-1];
				y=square[i].y[n-1];
			}
		}
		t=valueget(s,x,y);
		if(t == NULL) return;
		else p=t;
		while(p != NULL)
		{
			tmp=Copy(row,col,square,s,x,y,p->value);
			fill(tmp.row,tmp.col,tmp.square,tmp.matrix,emp-1);
			if(find == 1) return;
			p=p->next;
		}
	}
	else
	{
		find=1;
		for(i=0;i<9;i++)
		{
			for(j=0;j<9;j++)
				printf("%d ",s[i][j]);
			printf("\n");
		}
	}
}
int main()
{
	empty row[9],col[9],square[9];
	int s[9][9],i,j,emp=0;
	for(i=0;i<9;i++)
	{
		row[i].n=0;
		col[i].n=0;
		square[i].n=0;
		for(j=0;j<9;j++)
		{
			row[i].x[j]=i;
			col[i].y[j]=i;
		}
	}
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
		{
			scanf("%d",&s[i][j]);
			if(s[i][j] == 0)
			{
				emp++;
				row[i].y[row[i].n]=j;
				col[j].x[col[j].n]=i;
				square[i/3*3+j/3].x[square[i/3*3+j/3].n]=i;
				square[i/3*3+j/3].y[square[i/3*3+j/3].n]=j;
				col[j].n++;
				row[i].n++;
				square[i/3*3+j/3].n++;
			}
		}
	fill(row,col,square,s,emp);
	getchar();
	return 0;
}
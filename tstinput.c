#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
int main()
{
	int row,col,low=6,high=26,i,j,x,y,fx,fy,**num;
	FILE *fp;
	fp=fopen("input-8.txt","w+");
	if(fp)
	{
		srand((unsigned)time(NULL));
		row=rand() % (high-low)+low;
		col=rand() % (high-low)+low;
		num=(int**)malloc(row*sizeof(int*));
		for(i=0;i<row;i++)
			num[i]=(int*)malloc(col*sizeof(int));
		fprintf(fp,"%d%c%d%c",row,' ',col,'\n');
		for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
			{
				num[i][j]=rand() % 10;
				if(num[i][j] >= 3) num[i][j]=1;
				else num[i][j]=0;
				if(j != col-1) fprintf(fp,"%d%c",num[i][j],' ');
				else fprintf(fp,"%d",num[i][j]);
			}
			fprintf(fp,"%c",'\n');
		}
		x=rand() % (row/3);
		fx=rand() % (row/2)+(row/2);
		while(num[x][0] != 1)
			x=rand() % (row/3);
		while(num[fx][col-1] != 1)
			fx=rand() % (row/2)+(row/2);
		fprintf(fp,"%d%c%d%c",x,' ',0,'\n');
		fprintf(fp,"%d%c%d",fx,' ',col-1);
	}
}
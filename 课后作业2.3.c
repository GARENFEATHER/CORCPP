#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct c
{
	int value,row,col;
}AN;
void findan(int m,int n,int **matrix)
{
	int i,j,num,k;
	AN *point;
	num=m;
	point=(AN*)malloc(num*sizeof(AN));
	for(i=0,k=0;i<m;i++)
	{
		point[k].value=matrix[i][0];
		point[k].row=i;
		point[k].col=0;
		for(j=0;j<n;j++)
			if(matrix[i][j] > point[i].value)
			{
				point[k].value=matrix[i][j];
				point[k].row=i;
				point[k].col=j;
			}
		for(j=0;j<n;j++)//确保相同的最大值计入
			if(matrix[i][j] == point[i].value && (point[i].row != i || point[i].col != j))
			{
				num++;
				point=(AN*)realloc(point,num*sizeof(AN));
				k++;
				point[k].value=matrix[i][j];
				point[k].row=i;
				point[k].col=j;
			}
		k++;
	}
	for(j=0;j<k;j++)
	{
		int cols=point[j].col;
		for(i=0;i<m;i++)
			if(matrix[i][cols] < point[j].value)
			{
				point[j].value=INT_MIN;
				break;
			}
	}
	printf("鞍点及其位置:\n");
	for(i=0;i<k;i++)
		if(point[i].value != INT_MIN)
			printf("%d\n第%d行第%d列\n",point[i].value,point[i].row+1,point[i].col+1);
}
int main()
{
	int m,n,**matrix,i,j;
	printf("请依次输入矩阵的行数和列数:\n");
	scanf("%d%d",&m,&n);
	matrix=(int** )malloc(m*sizeof(int*));
	for(i=0;i<m;i++)
		matrix[i]=(int*)malloc(n*sizeof(int));
	printf("请输入矩阵:\n");
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			scanf("%d",&matrix[i][j]);
	findan(m,n,matrix);
	system("pause");
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct s
{
	int weight,profit;
}pack;
void knapsack(int m,int n,pack *s)
{
	int **mt,i,j;
	mt=(int**)malloc((n+1)*sizeof(int*));
	for(i=0;i<=n;i++)
		mt[i]=(int*)malloc((m+1)*sizeof(int));
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=m;j++)
		{
			if(i == 0) mt[i][j]=0;
			else if(s[i-1].weight > j) mt[i][j]=mt[i-1][j];
			else mt[i][j]=(mt[i-1][j] > s[i-1].profit+mt[i-1][j-s[i-1].weight]) ? (mt[i-1][j]) : (s[i-1].profit+mt[i-1][j-s[i-1].weight]);
		}
	}
	printf("%d",mt[n][m]);
}
int main()
{
	FILE *fp;
	pack *s;
	int W,n,i;
	fp=fopen("input14.txt","r");
	fscanf(fp,"%d%d",&W,&n);
	s=(pack*)malloc(n*sizeof(pack));
	for(i=0;i<n;i++)
		fscanf(fp,"%d%d",&s[i].weight,&s[i].profit);
	knapsack(W,n,s);
	getchar();
	return 0;
}
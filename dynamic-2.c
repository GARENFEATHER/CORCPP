#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct s
{
	int weight,volume,profit,number;
}pack;
void knap2(pack *s,int w,int v,int n)
{
	int result[w+1][v+1],i,j,k,u;
	for(i=0;i<=w;i++)
		for(j=0;j<=v;j++)
			result[i][j]=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=s[i-1].number;j++)
			for(u=w;u>=s[i-1].weight*j;u--)
				for(k=v;k>=s[i-1].volume*j;k--)
					result[u][k]=(result[u][k]>result[u-s[i-1].weight][k-s[i-1].volume]+s[i-1].profit) ? result[u][k] : result[u-s[i-1].weight][k-s[i-1].volume]+s[i-1].profit;
	printf("%d\n",result[w][v]);
}
int main()
{
	int w,v,i,n;
	FILE *fp;
	pack *s;
	scanf("%d %d\n%d",&w,&v,&n);
	s=(pack*)malloc(n*sizeof(pack));
	for(i=0;i<n;i++)
		scanf("%d %d %d %d",&s[i].weight,&s[i].volume,&s[i].profit,&s[i].number);
	knap2(s,w,v,n);
	return 0;
}
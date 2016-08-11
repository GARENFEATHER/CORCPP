#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
void Djkstra(int n,double **ma)
{
	int i,j,u,*final,start=0;
	double *D,min;
	final=(int*)malloc(n*sizeof(int));
	D=(double*)malloc(n*sizeof(double));
	for(i=0;i<n;i++)
	{
		D[i]=ma[start][i];
		final[i]=0;
	}
	D[start]=0.0;
	final[start]=1;
	for(i=0;i<n;i++)
	{
		if(i == start) continue;
		for(j=0,min=DBL_MAX;j<n;j++)
		{
			if(j == start) continue;
			if(!final[j] && D[j]<min)
			{
				u=j;
				min=D[j];
			}
		}
		final[u]=1;
		for(j=0;j<n;j++)
		{
			if(j == start || j == u || final[j]) continue;
			if(ma[u][j] + min < D[j])
				D[j]=ma[u][j]+min;
		}
	}
	printf("%.2lf",D[n-1]);
}
int main()
{
	FILE *fp;
	int m,n,i,j,origin,target;
	double **ma,value;
	scanf("%d %d",&n,&m);
	ma=(double**)malloc(n*sizeof(double*));
	for(i=0;i<n;i++)
	{
		ma[i]=(double*)malloc(n*sizeof(double));
		for(j=0;j<n;j++)
			ma[i][j]=DBL_MAX;
		ma[i][i]=0.0;
	}
	for(i=0;i<m;i++)
	{
		scanf("%d %d %lf",&origin,&target,&value);
		ma[origin][target]=value;
		ma[target][origin]=value;
	}
	Djkstra(n,ma);
}
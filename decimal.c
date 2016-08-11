#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int ppow(int x,int y)
{
	int i,k=1;
	if(y == 0) return 1;
	else
	{
		for(i=0;i<y;i++)
			k=k*x;
		return k;
	}
}
int main()
{
	FILE *fp;
	int n,i,j,k,**num;
	char tmp='0';
	fp=fopen("1for1.txt","r");
	fscanf(fp,"%d",&n);
	fscanf(fp,"%c",&tmp);
	num=(int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	{
		num[i]=(int*)malloc(4*sizeof(int));
		for(j=0;j<4;j++)
			num[i][j]=0;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<4;j++)
			for(k=0;k<8;k++)
			{
				fscanf(fp,"%c",&tmp);
				/*printf("%c",tmp);*/
				if(tmp == '1') num[i][j]=num[i][j]+ppow(2,7-k);
			}
		fscanf(fp,"%c",&tmp);
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<4;j++)
			if(j == 3) printf("%d",num[i][j]);
			else printf("%d.",num[i][j]);
		printf("\n");
	}
	system("pause");
	//亜込込込込込込
}

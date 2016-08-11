#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
void Lcs(int l1,int l2,char *s1,char *s2)
{
	int lcs[l1+1][l2+1],i,j,count;
	char *same;
	for(i=0;i<l1;i++)
		lcs[i][0]=0;
	for(i=0;i<l2;i++)
		lcs[0][i]=0;
	for(i=1;i<=l1;i++)
		for(j=1;j<l2;j++)
		{
			if(s1[i-1] == s2[j-1]) lcs[i][j]=lcs[i-1][j-1]+1;
			else if(lcs[i-1][j] > lcs[i][j-1]) lcs[i][j]=lcs[i-1][j];
			else lcs[i][j]=lcs[i][j-1];
		}
	same=(char*)malloc((lcs[l1][l2]+1)*sizeof(char));
	i=l1-1;
	j=l2-1;
	count=0;
	while(i >= 0 && j >= 0)
	{
		if(s1[i] == s2[j])
		{
			same[count]=s1[i];
			count++;
			i--;
			j--;
		}
		else if(lcs[i-1][j] > lcs[i][j-1]) i--;
		else j--;
	}
	for(i=0;i<count;i++)
		printf("%c", same[i]);
}

int main()
{
	char s1[]="1010101",s2[]="010110110";
	int l1,l2;
	l1=strlen(s1);
	l2=strlen(s2);
	Lcs(l1,l2,s1,s2);
	return 0;
}
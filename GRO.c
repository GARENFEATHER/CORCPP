#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int line=400;
int main()
{
	int i=0;
	FILE *fp;
	char *tmp,*f1="G:\\RANDOM\\Assignment2\\dataset\\GroceryStore\\Groceries.csv",*f2="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER0\\sanitized_all.981115184025";
	tmp=(char*)malloc(line*sizeof(char));
	fp=fopen(f1,"r");
	while(fgets(tmp,line,fp))
	{
		printf("%d %s",i,tmp);
		i++;
		if (i > 20) break;
	}
	return 0;
	getchar();
}
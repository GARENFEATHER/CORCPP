#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int i,ma,mb,n;
	char *p="112,234,23,456,235,123,4,5,6,4233",*s;
	s=p;
	while(1)
	{
		i=sscanf(s,"%d,%d,%n",&ma,&mb,&n);
		s=s+n;
		if(i == EOF) break;
		else printf("%d %d %d\n",ma,mb,n);
	}
	return 0;
}
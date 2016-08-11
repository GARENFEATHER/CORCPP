#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int main()
{
	int a;
	char *s="sssdf";
	a=strchr(s,',');
	printf("%d\n", a);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
void change1(int *a)
{
	*a=3;
}
void change2(int b)
{
	printf("%d\n", b);
	change1(&b);
	printf("%d\n", b);
}
int main()
{
	int a=122;
	change2(a);
	printf("%d\n", a);
	return 0;
}
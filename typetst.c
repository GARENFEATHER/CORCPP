#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct {
	char *name;
	int row,col;
	double **value;
}varType;
typedef struct {
	varType *out;
	int n,top;
}stack;
stack use()
{
	varType *s;
	s=(varType*)malloc(sizeof(varType));
	s->row=1907;
	s->value=(double**)malloc(sizeof(double*));
	s->value[0]=(double*)malloc(sizeof(double));
	s->value[0][0]=122.353;
	stack a;
	a.n=122;
	a.out=(varType*)malloc(2*sizeof(varType));
	a.out[0]=*s;
	a.top=2;
	return a;
}
int main()
{
	stack ug;
	ug=use();
	printf("%d\n%d\n%lf", ug.n,ug.out[0].row,ug.out[0].value[0][0]);
	return 0;
}
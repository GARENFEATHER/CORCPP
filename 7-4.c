#include <stdio.h>
#include <stdlib.h>
short do_loop(short x, short y, short k) {
	do {
		x*=(y%k) ;
		k--;
	} while ((k>0) && (y>k));
		return x;
}
int main(int argc, char const *argv[])
{
	short int x,y,k;
	scanf("insert x y k:%d %d %d",&x,,&y,&k);
	//printf("%d %d %d\n",x,y,k);
	do_loop(x,y,k);
	return 0;
	//do_loop(x,y,k);
}

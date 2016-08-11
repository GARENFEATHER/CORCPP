#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long sum=0, mark=1; 
void test(long row, long ld, long rd)  
{  
    if (row != mark)  
    {
    	long pos = mark & ~(row | ld | rd);   
        while (pos)
        {
        	long p = pos & -pos;
            pos -= p;
            test(row + p, (ld + p) << 1, (rd + p) >> 1);                                
        }
    }
    else sum++;
}
int main()  
{  
    int n;
    scanf("%d",&n);
    mark = (mark << n) - 1;
    test(0, 0, 0);  
    printf("%ld\n",sum);
    return 0;  
}
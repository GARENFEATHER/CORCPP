int decode2(int x,int y,int z)
{
	int tmp,result;
	tmp=z-y;
	result=tmp;
	tmp=tmp^x;
	result=result*tmp;
	return result;
}


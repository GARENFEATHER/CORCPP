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
stack save;
varType *var;
int varnum=0,init=400,nl=20,space,pm=0,mul=0,list=0;
char *s[4][7]={"1","2","3","[","]","(",")","4","5","6","*","/",",",";","7","8","9","+","-","Enter","Var",".","0","|","%","=","Func","CLR"};
char sign[11]={'+','-','*','/','|','=','(',')','%'};
int search(char *name)
{
	int i;
	for(i=0;i<varnum;i++)
		if(strcmp(var[i].name,name) == 0) return i;
	return -1;
}
varType* plusMinus(varType a,varType b,int porm,int error)//porm=1 plus,p=-1 minus
{
	varType *result;
	int i,j,row,col;
	result=(varType*)malloc(sizeof(varType));
	result->name="tmp";
	if(a.row == 1 && a.col == 1)
	{
		result->row=b.row;
		result->col=b.col;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(i=0;i<result->row;i++)
		{
			result->value[i]=(double*)malloc(result->col*sizeof(double));
			for(j=0;j<result->col;j++)
				result->value[i][j]=a.value[0][0]+b.value[i][j]*porm;
		}
	}
	else if(b.row == 1 && b.col == 1)
	{
		result->row=a.row;
		result->col=a.col;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(i=0;i<result->row;i++)
		{
			result->value[i]=(double*)malloc(result->col*sizeof(double));
			for(j=0;j<result->col;j++)
				result->value[i][j]=a.value[i][j]+b.value[0][0]*porm;
		}
	}
	else if(error == 1)
	{
		result->row=a.row<b.row ? a.row:b.row;
		result->col=a.col<b.col ? a.col:b.col;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(i=0;i<result->row;i++)
		{
			result->value[i]=(double*)malloc(result->col*sizeof(double));
			for(j=0;j<result->col;j++)
				result->value[i][j]=a.value[i][j]+b.value[i][j]*porm;
		}
	}
	return result;
}
varType* multiply(varType a,varType b,int reverse)
{
	varType *result;
	int i,ik,jk,n;
	result=(varType*)malloc(sizeof(varType));
	result->name="tmp";
	if(a.row == 1 && a.col == 1)
	{
		result->row=b.row;
		result->col=b.col;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(ik=0;ik<result->row;ik++)
		{
			result->value[ik]=(double*)malloc(result->col*sizeof(double));
			for(jk=0;jk<result->col;jk++)
				result->value[ik][jk]=b.value[ik][jk]*a.value[0][0];
		}
	}
	else if(b.row == 1 && b.col == 1)
	{
		result->row=a.row;
		result->col=a.col;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(ik=0;ik<result->row;ik++)
		{
			result->value[ik]=(double*)malloc(result->col*sizeof(double));
			for(jk=0;jk<result->col;jk++)
				result->value[ik][jk]=a.value[ik][jk]*b.value[0][0];
		}
	}
	else if(reverse == 0)
	{
		result->row=a.row;
		result->col=b.col;
		n=a.col;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(ik=0;ik<result->row;ik++)
		{
			result->value[ik]=(double*)malloc(result->col*sizeof(double));
			for(jk=0;jk<result->col;jk++)
			{
				result->value[ik][jk]=0;
				for(i=0;i<n;i++)
					result->value[ik][jk]+=a.value[ik][i]*b.value[i][jk];
			}
		}
	}
	else if(reverse == 1)
	{
		result->row=a.col;
		result->col=b.col;
		n=a.row;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(ik=0;ik<result->row;ik++)
		{
			result->value[ik]=(double*)malloc(result->col*sizeof(double));
			for(jk=0;jk<result->col;jk++)
			{
				result->value[ik][jk]=0;
				for(i=0;i<n;i++)
					result->value[ik][jk]+=a.value[i][ik]*b.value[i][jk];
			}
		}	
	}
	else if(reverse == 2)
	{
		result->row=a.row;
		result->col=b.row;
		n=a.col;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(ik=0;ik<result->row;ik++)
		{
			result->value[ik]=(double*)malloc(result->col*sizeof(double));
			for(jk=0;jk<result->col;jk++)
			{
				result->value[ik][jk]=0;
				for(i=0;i<n;i++)
					result->value[ik][jk]+=a.value[ik][i]*b.value[jk][i];
			}
		}
			
	}
	else if(reverse == 3)
	{
		result->row=a.col;
		result->col=b.row;
		n=a.row;
		result->value=(double**)malloc(result->row*sizeof(double*));
		for(ik=0;ik<result->row;ik++)
		{
			result->value[ik]=(double*)malloc(result->col*sizeof(double));
			for(jk=0;jk<result->col;jk++)
			{
				result->value[ik][jk]=0;
				for(i=0;i<n;i++)
					result->value[ik][jk]+=a.value[i][ik]*b.value[jk][i];
			}
		}
	}
	return result;
}
double determinant(int n,double **m,double re)
{
	int i,j,k=1;
	double **mtmp;
	mtmp=(double**)malloc((n-1)*sizeof(double*));
	if(n == 2)
		return m[0][0]*m[1][1]-m[0][1]*m[1][0];
	else if(n == 1) return m[0][0];
	for(i=1;i<n;i++)
	{
		mtmp[i-1]=(double*)malloc((n-1)*sizeof(double));
		for(j=1;j<n;j++)
			mtmp[i-1][j-1]=m[i][j];
	}
	for(i=0;i<n;i++)
	{
		if(i != 0)
		{
			for(j=1;j<n;j++)
				mtmp[j-1][i-1]=m[j][i-1];
		}
		if(m[0][i] != 0) re=re+m[0][i]*determinant(n-1,mtmp,0)*k;
		k=(-1)*k;
	}
	return re;
}
varType* inverse(varType tmp)
{
	varType* result;
	int n,i,j,k,l,f=1;
	double sub,**subd;
	n=tmp.row;
	sub=determinant(n,tmp.value,0);
	if(sub == 0) return NULL;
	subd=(double**)malloc((n-1)*sizeof(double*));
	result=(varType*)malloc(sizeof(varType));
	result->name="tmp";
	result->value=(double**)malloc(n*sizeof(double*));
	result->row=n;
	result->col=n;
	if(n == 1)
	{
		result->value[0]=(double*)malloc(n*sizeof(double));
		result->value[0][0]=1/tmp.value[0][0];
		return result;
	}
	for(i=0;i<n;i++)
	{
		result->value[i]=(double*)malloc(n*sizeof(double));
		if(i != n-1) subd[i]=(double*)malloc((n-1)*sizeof(double));
		for(j=0;j<n;j++)
			result->value[i][j]=0;
		result->value[i][i]=1;
	}
	for(i=0;i<n;i++)
	{
		for(j=0,l=0;j<n && l<n-1;j++,l++)
		{
			if(j == i) j++;
			for(k=1;k<n;k++)
				subd[l][k-1]=tmp.value[j][k];
		}
		result->value[0][i]=determinant(n-1,subd,0)/sub;
		f=(-1)*f;
		for(j=1;j<n;j++)
		{
			for(k=0,l=0;k<n && l<n-1;k++,l++)
			{
				if(k == i) k++;
				subd[l][j-1]=tmp.value[k][j-1];
			}
			result->value[j][i]=determinant(n-1,subd,0)/sub;
			f=(-1)*f;
		}
	}
	return result;
}
varType* variable(char *v)
{
	varType *result;
	double value;
	int n,i,j,c;
	char *p;
	p=v;
	result=(varType*)malloc(sizeof(varType));
	sscanf(p,"%lf%n",&value,&n);
	result->name="tmp";
	if(n == strlen(v))//数值
	{
		result->row=1;
		result->col=1;
		result->value=(double**)malloc(result->row*sizeof(double*));
		result->value[0]=(double*)malloc(result->col*sizeof(double));
		result->value[0][0]=value;
		return result;
	}
	else if(v[0] == '[' && v[strlen(v)-1] == ']')//矩阵
	{
		v[strlen(v)-1]='\0';
		strcpy(v,v+1);
		if(strlen(v) != 2)
		{
			p=v;
			n=0;
			while(strchr(p,';') != NULL)
			{
				i=strchr(p,';')-p;
				p=p+i+1;
				n++;
			}
			result->value=(double**)malloc((n+1)*sizeof(double*));
			result->row=n+1;
			p=(char*)malloc((strlen(v)+1)*sizeof(char));
			strcpy(p,v);
			if(n != 0) p[strchr(v,';')-v]='\0';
			i=0;
			while(strchr(p,',') != NULL)
			{
				n=strchr(p,',')-p;
				p=p+n+1;
				i++;
			}
			result->col=i+1;
			strcat(v,";");
			p=v;
			for(i=0;i<result->row;i++)
			{
				result->value[i]=(double*)malloc(result->col*sizeof(double));
				for(j=0;j<result->col;j++)
				{
					c=sscanf(p,"%lf%n",&result->value[i][j],&n);
					p=p+n;
					if(*p == ',') p=p+1;
					else if(*p == ';') break;
					else
					{
						result->row=-1;
						result->col=-2;
						return result;
					}
				}
				if(j != result->col-1)
				{
					result->row=-1;
					result->col=-2;
					return result;
				}
				else p=p+1;
			}
			return result;
		}
		else
		{
			result->row=-1;
			result->col=-3;
			result->value=NULL;
			return result;
		}
	}
	else//变量
	{
		i=search(v);
		if(i != -1) result=var+i;
		else
		{
			result->row=-1;
			result->col=-1;
		}
		return result;
	}
}
stack anaylisis(char *input)//pm:plus minus automation;mul:multiply automation
{
	stack result,suffix;
	varType *tmp,a,b;
	char *v;
	int *mark,i,j,k=0,*bl,*br,*sl,*sr,blc=0,brc=0,slc=0,src=0,st=0;
	while(strchr(input,' ') != NULL)
	{
		i=strchr(input,' ')-input;
		input[i]='\0';
		strcat(input,input+i+1);
	}
	result.n=strlen(input);
	suffix.n=strlen(input);
	sl=(int*)malloc(result.n*sizeof(int));
	sr=(int*)malloc(result.n*sizeof(int));
	bl=(int*)malloc(result.n*sizeof(int));
	br=(int*)malloc(result.n*sizeof(int));
	result.out=(varType*)malloc(result.n*sizeof(varType));
	suffix.out=(varType*)malloc(suffix.n*sizeof(varType));
	result.top=0;
	suffix.top=0;
	v=(char*)malloc(result.n*sizeof(char));
	mark=(int*)malloc(result.n*sizeof(int));
	mark[0]=strlen(input);
	for(i=0;i<result.n;i++)
	{
		if(input[i] == '[')
		{
			bl[blc]=i;
			blc++;
			continue;
		}
		else if(input[i] == ']')
		{
			br[blc]=i;
			brc++;
			continue;
		}
		for(j=0;j<11;j++)
			if(input[i] == sign[j])
			{
				mark[k]=i;
				k++;
				break;
			}
		if(j == 6)
		{
			sl[slc]=i;
			slc++;
		}
		else if(j == 7)
		{
			sr[src]=i;
			src++;
		}
	}
	if(slc != src || blc != brc)//()或[]括号数量不匹配
	{
		result.n=-1;
		return result;
	}
	for(i=0;i<k-1;i++)
		if(mark[i] == mark[i+1]-1)
		{
			if(input[mark[i]] == input[mark[i+1]])
			{
				if(!(input[mark[i]] == '(' || input[mark[i+1]] == ')'))
				{
					result.n=-2;//符号非法相连
					return result;
				}
			}
		}
	if(mark[0] != 0)
	{
		st=0;
		strcpy(v,input);
		v[mark[0]]='\0';
		tmp=variable(v);
		result.out[0]=*tmp;
		result.top++;
		if(!(tmp->row>0 && tmp->col>0))
		{
			result.n=-4;//具体信息见本子
			return result;
		}
	}
	else
	{
		st=1;
		if(input[mark[0]] == '-' || input[mark[0]] == '(')
		{
			if(input[mark[0]] == '-')
			{
				result.out[0].col=-2;
				result.out[0].name="-";
			}
			else
			{
				result.out[0].col=-5;
				result.out[0].name="(";
			}
			result.out[0].row=-3;
			result.top++;
		}
		else
		{
			result.n=-3;//第一个字符为符号非法
			return result;
		}
	}
	if(mark[k-1] == strlen(input)-1)
	{
		if(!(input[mark[k-1]] == ')' || input[mark[k-1]] == '|'))
		{
			result.n=-3;
			return result;
		}
	}
	for(i=st;i<k;i++)
	{
		if(i != 0 && mark[i]-mark[i-1] != 1)
		{
			strcpy(v,input+mark[i-1]+1);
			v[mark[i]-mark[i-1]-1]='\0';
			tmp=variable(v);
			suffix.out[suffix.top]=*tmp;
			suffix.top++;
			if(!(tmp->row>0 && tmp->col>0))
			{
				result.n=-4;//具体信息见本子
				return result;
			}
		}
		if(input[mark[i]] == '(')
		{
			result.out[result.top].name="(";
			result.out[result.top].col=-5;
			result.top++;
		}
		else if(input[mark[i]] == ')')
		{
			while(result.top>0 && result.out[result.top-1].name[0] != '(')
			{
				suffix.out[suffix.top]=result.out[result.top-1];
				suffix.top++;
				result.top--;
			}
			result.top--;
		}
		else
		{
			tmp=(varType*)malloc(sizeof(varType));
			tmp->name=(char*)malloc(4*sizeof(char));
			if(input[mark[i]] == '|' || (input[mark[i]] == '-' && input[mark[i]-1] == '(')) tmp->col=-2;
			else if(input[mark[i]] == '*' || input[mark[i]] == '/' || input[mark[i]] == '%') tmp->col=-3;
			else if(input[mark[i]] == '+' || input[mark[i]] == '-') tmp->col=-4;
			tmp->name[0]=input[mark[i]];
			tmp->name[1]='\0';
			if(result.top != 0 && tmp->col <= result.out[result.top-1].col)
			{
				suffix.out[suffix.top]=result.out[result.top-1];
				suffix.top++;
				result.top--;
			}
			result.out[result.top]=*tmp;
			result.top++;
		}
	}
	if(mark[k-1] != strlen(input)-1)
	{
		strcpy(v,input+mark[k-1]+1);
		tmp=variable(v);
		suffix.out[suffix.top]=*tmp;
		suffix.top++;
		if(!(tmp->row>0 && tmp->col>0))
		{
			result.n=-4;//具体信息见本子
			return result;
		}
	}
	while(result.top != 0)
	{
		suffix.out[suffix.top]=result.out[result.top-1];
		suffix.top++;
		result.top--;
	}
	i=0;
	k=0;
	save.top=0;
	save.n=suffix.top;
	save.out=(varType*)malloc(save.n*sizeof(varType));
	while(i < suffix.top)
	{
		if(suffix.out[i].row > 0 && suffix.out[i].col > 0)
		{
			result.out[k]=suffix.out[i];
			k++;
		}
		else if(suffix.out[i].col < 0)
		{
			if(suffix.out[i].col == -3 || suffix.out[i].col == -4)
			{
				if(k < 2)
				{
					//gtk_entry_set_text(GTK_ENTRY(entry),"Stack Error");
					result.n=-5;//堆栈出错
					return result;
				}
				b=result.out[k-1];
				k--;
				a=result.out[k-1];
				k--;
				if(suffix.out[i].name[0] == '+' || suffix.out[i].name[0] == '-')
				{
					int porm;
					if(suffix.out[i].name[0] == '+') porm=1;
					else porm=-1;
					if(pm == 1) tmp=plusMinus(a,b,porm,pm);
					else if((a.row == b.row && a.col == b.col) || (a.row == 1 && a.col == 1) || (b.row == 1 && b.col == 1)) tmp=plusMinus(a,b,porm,pm);
					else
					{
						result.n=-6;//矩阵加减法错误
						return result;
					}
				}
				else if(suffix.out[i].name[0] == '*' || suffix.out[i].name[0] == '/')
				{
					if(suffix.out[i].name[0] == '/')
					{
						if(b.row == b.col) tmp=inverse(b);
						else
						{
							result.n=-12;//非方阵不可求逆
							return result;
						}
						if(tmp == NULL)
						{
							result.n=-8;//矩阵不存在逆矩阵
							return result;
						}
						else b=*tmp;
					}
					if(a.col == b.row || (a.row == 1 && a.col == 1) || (b.row == 1 && b.col == 1)) tmp=multiply(a,b,0);
					else if(mul == 0)
					{
						result.n=-7;//非自动处理型矩阵乘法错误
						return result;
					}
					else
					{
						if(a.row == b.row) tmp=multiply(a,b,1);
						else if(a.col == b.col) tmp=multiply(a,b,2);
						else if(a.row == b.col) tmp=multiply(a,b,3);
						else
						{
							result.n=-9;//自动处理型矩阵乘法错误
							return result;
						}
					}
				}
				else if(suffix.out[i].name[0] == '%')
				{
					if(a.row != 1 || a.col != 1 || b.row != 1 || b.col != 1)
					{
						result.n=-10;//矩阵不可求余
						return result;
					}
					else
					{
						tmp->row=1;
						tmp->col=1;
						tmp->value=(double**)malloc(sizeof(double*));
						tmp->value[0]=(double*)malloc(sizeof(double));
						tmp->value[0][0]=(int)a.value[0][0] % (int)b.value[0];
					}
				}
			}
			else if(suffix.out[i].col == -2)
			{
				a=result.out[k-1];
				k--;
				if(suffix.out[i].name[0] == '-')
				{
					for(i=0;i<a.row;i++)
						for(j=0;j<a.col;j++)
							a.value[i][j]=-a.value[i][j];
					*tmp=a;
				}
				else if(suffix.out[i].name[0] == '|')
				{
					if(a.row == a.col) tmp=inverse(a);
					else
					{
						result.n=-12;//非方阵不可求逆
						return result;
					}
					if(tmp == NULL)
					{
						result.n=-8;//矩阵不存在逆矩阵
						return result;
					}
					else a=*tmp;
				}
			}
			result.out[k]=*tmp;
			save.out[save.top]=*tmp;
			save.top++;
			k++;
		}
		i++;
	}
	result.n=k;
	return result;
}
void resultsave()
{
	FILE *fp;
	int i,j,k;
	char *name,*va;
	va=(char*)malloc(init*sizeof(char));
	name=(char*)malloc(nl*sizeof(char));
	sprintf(name,"result-%d",list);
	fp=fopen(name,"w+");
	for(k=0;k<save.top;k++)
	{
		fprintf(fp,"%dx%d:\n",save.out[k].row,save.out[k].col);
		strcpy(va,"[");
		for(i=0;i<save.out[k].row;i++)
		{
			for(j=0;j<save.out[k].col;j++)
			{
				sprintf(name,"%d",save.out[k].value[i][j]);
				strcat(va,name);
				if(j != save.out[k].col-1) strcat(va,",");
			}
			if(i != save.out[k].col) strcat(va,";");
		}
		strcat(va,"]\n\n");
	}
}
void ShowOut(varType result)
{
	int i,j;
	char *out,*number;
	number=(char*)malloc(nl*sizeof(char));
	out=(char*)malloc(init*sizeof(char));
	if(result.row == 1 && result.col == 1)
	{
		sprintf(out,"%.3lf",result.value[0][0]);
		//gtk_entry_set_text(GTK_ENTRY(entry),out);
		return;
	}
	strcpy(out,"[");
	for(i=0;i<result.row;i++)
	{
		for(j=0;j<result.col;j++)
		{
			sprintf(number,"%.3lf",result.value[i][j]);
			strcat(out,number);
			if(j != result.col-1) strcat(out,",");
		}
		if(i != result.row-1) strcat(out,";");
	}
	strcat(out,"]");
	//gtk_entry_set_text(GTK_ENTRY(entry),out);
}
void caculate(char *input)
{
	varType *Ans;
	stack prefix;
	prefix.n=-11;
	Ans=(varType*)malloc(sizeof(varType));
	if(strlen(input) != 0) prefix=anaylisis(input);
	if(prefix.n != -11)
	{
		if(prefix.n < 0)
		{
			// if(result.n == -1) gtk_entry_set_text(GTK_ENTRY(entry),"Unbalanced or unexpected parenthesis or bracket");
			// else if(result.n == -2) gtk_entry_set_text(GTK_ENTRY(entry),"Unexpected operator");
			// else if(result.n == -3) gtk_entry_set_text(GTK_ENTRY(entry),"The input character is not valid in statements or expressions.");
			// else if(result.n == -4) gtk_entry_set_text(GTK_ENTRY(entry),"Overlimit");
			// else if(result.n == -5) gtk_entry_set_text(GTK_ENTRY(entry),"Stack Error");
			// else if(result.n == -6) gtk_entry_set_text(GTK_ENTRY(entry),"Matrix dimensions must agree");
			// else if(result.n == -7) gtk_entry_set_text(GTK_ENTRY(entry),"Non-automated:Inner matrix dimensions must agree.");
			// else if(result.n == -8) gtk_entry_set_text(GTK_ENTRY(entry),"Matrix is singular to working precision.");
			// else if(result.n == -9) gtk_entry_set_text(GTK_ENTRY(entry),"Automated:Inner matrix dimensions must agree.");
			// else if(result.n == -10) gtk_entry_set_text(GTK_ENTRY(entry),"% is only for figure");
			// else if(result.n == -12) gtk_entry_set_text(GTK_ENTRY(entry),"Matrix must be square.");
			return NULL;
		}
		else ShowOut(prefix.out[0]);
	}
	//else gtk_entry_set_text(GTK_ENTRY(entry),"anaylisis error");
}
int fileread(char *file)
{
	int a,l=0;
	char *line;
	FILE *fp;
	line=(char*)malloc(init*sizeof(char));
	fp=fopen(file,"r");
	if(fp == NULL) return 0;//文件无法打开
	else
	{
		while(fgets(line,init,fp) != NULL)
		{
			if(strchr(line,'=') != NULL)
			{
				a=strchr(line,'=')-line;
				giveValue(line,a);
			}
			else continue;
			l++;
		}
		fclose(fp);
	}
}
int main()
{
	char *s[]={"(12-3)*5+6-16/8","[1,2,3;2,3,4;3,4,5]*2+3","[2,3]*[3;3]","[2;3]*[3,3]","[2]*[3]"};
	varType *result;
	caculate(s[4]);
	printf("%d\n", result->row);
}
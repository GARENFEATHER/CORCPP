#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int ppow(int n,int m)
{
	int i=0,s=1;
	if(m == 0) return 1;
	else
	{
		for(i=0;i<m;i++)
			s=s*n;
		return s;
	}
}
void change(int origin,int target,char* n)
{
	int i=0,sum=0,k=0,l=0;
	char temp="";
	char ss[100]={""};
	while(n[l]!='\0') l++;
	for(i=0;i<l;i++)
	{
		if(n[i]<'a' && (n[i])>=origin+'0')
		{
			printf("Υ������\n");
			return;
		}
		else if(n[i]>'a' && n[i]-'a'+10>=origin)
		{
			printf("Υ������\n");
			return;
		}
		sum=sum+(n[i]-'0')*ppow(origin,l-i-1);
	}
	while(sum >= target)
	{
		if((sum%target) >= 10) temp='a'+((sum%target)-10);
		else temp=(sum%target)+'0';
		ss[k++]=temp;
		sum=sum/target;
	}
	if(sum >= 10) temp='a'+(sum-10);
	else temp=sum+'0';
	ss[k]=temp;
	for(i=k;i>=0;i--)
		printf("%c",ss[i]);
	printf("\n");
}
int main()
{
	int origin,target;
	char n[100];
	while(1)
	{
		printf("����������ԭʼ���ƣ�Ŀ����ƺ�ԭʼ���ݣ�\n");
		scanf("%d",&origin);
		if(origin == -1) return;
		scanf("%d%s",&target,&n);
		if(!(origin >=2 && origin<=16)) printf("ԭʼ���Ʋ���2~16��Χ��");
		else if(!(target>=2 && target<=16)) printf("Ŀ����Ʋ���2~16��Χ��");
		else
		{
			printf("������ȷ��%d���Ƶ�%sת����%d���ƣ�\n",origin,n,target);
			change(origin,target,n);
		}
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
int init=100000,ch=50,space=20,initall=1000000;
typedef struct x
{
	int n,space;
	char **item;
}unix;
typedef struct u
{
	int n;
	char **item;
	int supcount;
	struct u *next;
}itemset;
int quicksort(int low,int high,char **all)
{
	char *tmp;
	tmp=(char*)malloc(ch*sizeof(char));
	strcpy(tmp,all[low]);
	while(low < high)
	{
		while(low < high && strcmp(all[high],tmp) >= 0) high--;
		strcpy(all[low],all[high]);
		while(low < high && strcmp(all[low],tmp) <= 0) low++;
		strcpy(all[high],all[low]);
	}
	strcpy(all[low],tmp);
	return low;
}
void qsort(int low,int high,char **all)
{
	int mid;
	if(low < high)
	{
		mid=quicksort(low,high,all);
		qsort(low,mid-1,all);
		qsort(mid+1,high,all);
	}
}
void freespace(itemset* C)
{
	if(C->next != NULL) freespace(C->next);
	free(C);
	C=NULL;
}
itemset* get_n_itemset(int n,char **item,int add)
{
	int i;
	itemset *L;
	L=(itemset*)malloc(sizeof(itemset));
	L->n=n+add;
	L->item=(char**)malloc(L->n*sizeof(itemset*));
	L->next=NULL;
	L->supcount=0;
	for(i=0;i<n;i++)
	{
		L->item[i]=(char*)malloc(ch*sizeof(itemset));
		strcpy(L->item[i],item[i]);
	}
	L->item[i]=(char*)malloc(ch*sizeof(itemset));
	return L;
}
int has_infrequent_subset(itemset *L, itemset *c)//infrequent返回1,else 返回0
{
	itemset *p;
	int i,j,k;
	for(i=0;i<c->n;i++)
	{
		p=L;
		while(p != NULL)
		{
			for(j=0,k=0;j<L->n && k<L->n;j++,k++)
			{
				if(k == i) k++;
				if(strcmp(p->item[j],c->item[k]) != 0) break;
			}
			if(j == L->n-1) break;
			p=p->next;
		}
		if(p == NULL) return 1;//infrequent
	}
	return 0;
}
itemset* apriori_gen(itemset *L)
{
	int i,j,n,u;
	itemset *c,*p,*t,*cp,*ct;
	n=L->n;
	c=NULL;
	cp=NULL;
	ct=NULL;
	t=L;
	p=t->next;
	while(t->next != NULL)
	{
		while(p != NULL)
		{
			for(i=0;i<n;i++)
				if(strcmp(t->item[i],p->item[i]) != 0) break;
			if(i == n-1)
			{
				cp=get_n_itemset(n,t->item,1);
				if(c == NULL) c=cp;
				else ct->next=cp;
				strcpy(cp->item[n],p->item[n-1]);
				if(has_infrequent_subset(L,cp))
				{
					if(ct != NULL) ct->next=NULL;
					if(c == cp) c=NULL;
					free(cp);
				}
				else ct=cp;
			}
			p=p->next;
		}
		t=t->next;
		p=t->next;
	}
	return c;
}
itemset** apriori(unix *db,char **all,int trans_count,int item_count,int min_support,int item_max)
{
	int i,k,tag,u,j;
	itemset **L,*p,*q,*t,**C;
	qsort(0,item_count-1,all);
	strcpy(all[item_count],"\0");//防止越界
	for(i=0;i<trans_count;i++)
		qsort(0,db[i].n-1,db[i].item);
	L=(itemset**)malloc(item_max*sizeof(itemset*));
	C=(itemset**)malloc(item_max*sizeof(itemset*));
	for(i=0;i<item_max;i++)
	{
		// L[i]=(itemset*)malloc(sizeof(itemset));
		// C[i]=(itemset*)malloc(sizeof(itemset));
		L[i]=NULL;
		C[i]=NULL;
	}
	for(i=0;i<item_count;i++)
	{
		k=i;
		while(strcmp(all[i],all[i+1]) == 0) i++;
		if(i-k+1 >= min_support)
		{
			if(L[0] == NULL)
			{
				L[0]=get_n_itemset(1,all,0);
				t=p=L[0];
			}
			else
			{
				p=get_n_itemset(1,all+i,0);
				t->next=p;
				t=p;
			}
			t->supcount=i-k+1;//概念上的冲突，↓，1频繁项集与其他频繁项集的supcount计算方式不同？
		}
	}
	for(k=1;L[k-1]!=NULL;k++)//TID L1、L1、L2、L2、L3这样的存在{L1、L2、L3}supcount仅算1，避免因为一个人同样的大量操作影响结果？
	{
		C[k]=apriori_gen(L[k-1]);
		for(i=0;i<trans_count;i++)
		{
			p=C[k];
			while(p != NULL)
			{
				for(j=0;j<k+1;j++)
				{
					for(u=0;u<db[i].n;u++)
						if(strcmp(p->item[j],db[i].item[u]) == 0) break;
					if(u == db[i].n) break;
				}
				if(j == k+1) p->supcount++;
				p=p->next;
			}
		}
		q=C[k];
		i=0;
		while(q != NULL)
		{
			if(q->supcount >= min_support)
			{
				if(i == 0)
				{
					L[k]=get_n_itemset(k+1,q->item,0);
					p=t=L[k];
				}
				else
				{
					p=get_n_itemset(k+1,q->item,0);
					t->next=p;
					t=p;
				}
				t->supcount=q->supcount;
				i++;
			}
			q=q->next;
		}
		//freespace(C[k]);
	}
	return L;
}
void show(itemset** L,int read,int caculate,int file,int sup)
{
	char *s="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\",*tmp;
	FILE *fp;
	int i,j;
	itemset *p;
	tmp=(char*)malloc(ch*4*sizeof(char));
	sprintf(tmp,"%sout_unix%d_support%d.txt",s,file,sup);
	fp=fopen(tmp,"w+");
	for(i=0,p=L[0];L[i] != NULL;i++)
	{
		p=L[i];
		fprintf(fp,"%d-itemset:\n",i+1);
		while(1)
		{
			fprintf(fp,"support:%d\t{",p->supcount);
			for(j=0;j<i+1;j++)
				if(j != i) fprintf(fp,"%s,",p->item[j]);
				else fprintf(fp,"%s}\n",p->item[j]);
			p=p->next;
			if(p == NULL)
			{
				printf("\n\n\n");
				break;
			}
		}
	}
	fprintf(fp,"scan_time:%d\ncaculate_time:%d\n",caculate,read);
	fclose(fp);
}
int main()
{
	char *f0="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER0\\sanitized_all.981115184025";
	char *f1="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER1\\sanitized_all.981115184025";
	char *f2="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER2\\sanitized_all.981115184025";
	char *f3="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER3\\sanitized_all.981115184025";
	char *f4="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER4\\sanitized_all.981115184025";
	char *f5="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER5\\sanitized_all.981115184025";
	char *f6="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER6\\sanitized_all.981115184025";
	char *f7="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER7\\sanitized_all.981115184025";
	char *f8="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER8\\sanitized_all.981115184025";
	char *ftst="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER0\\testdata.981115184025";
	char *fn="G:\\RANDOM\\Assignment2\\dataset\\UNIX_usage\\USER0\\neww.981115184025";
	char *ltmp,**all;
	FILE *fp;
	unix *db;
	itemset **L;
	int i,j,trans_count,u=0,item_count,item_max=0,k,a,start,end,read,min_support;
	start=clock();
	fp=fopen(f5,"r");
	db=(unix*)malloc(init*sizeof(unix));
	ltmp=(char*)malloc(ch*sizeof(char));
	all=(char**)malloc(initall*sizeof(char*));
	for(i=0;i<initall;i++)
		all[i]=(char*)malloc(ch*sizeof(char));
	for(i=0;i<init;i++)
	{
		db[i].item=(char**)malloc(space*sizeof(char*));
		for(j=0;j<space;j++)
			db[i].item[j]=(char*)malloc(ch*sizeof(char));
		db[i].space=space;
		db[i].n=0;
	}
	i=0;
	j=0;
	while(fgets(ltmp,init,fp))
	{
		if(strcmp(ltmp,"**SOF**\n") == 0) continue;
		else if(strcmp(ltmp,"**EOF**\n") == 0)
		{
			db[i].n=j;
			if(db[i].n > item_max) item_max=db[i].n;
			i++;
			j=0;
		}
		else
		{
			*(ltmp+strlen(ltmp)-1)='\0';
			strcpy(db[i].item[j],ltmp);
			strcpy(all[u],ltmp);
			u++;
			if(u >= initall)
			{
				int k;
				initall=initall*2;
				all=(char**)realloc(all,initall*sizeof(char*));
				for(k=0;k<initall;k++)
					all[k]=(char*)malloc(ch*sizeof(char));
			}
			j++;
			if(j >= db[i].space)
			{
				int k;
				db[i].space=db[i].space*2;
				db[i].item=(char**)realloc(db[i].item,db[i].space*sizeof(char*));
				for(k=j;k<db[i].space;k++)
					db[i].item[k]=(char*)malloc(ch*sizeof(char));
			}
		}
		if(i >= init)
		{
			init=init*2;
			db=(unix*)realloc(db,init*sizeof(unix));
			for(k=i;k<init;k++)
			{
				db[k].item=(char**)malloc(space*sizeof(char*));
				for(a=0;a<space;a++)
					db[k].item[a]=(char*)malloc(ch*sizeof(char));
				db[k].space=space;
				db[k].n=0;
			}
		}
	}
	min_support=320;
	fclose(fp);
	end=clock();
	read=end-start;
	trans_count=i;
	item_count=u;
	start=clock();
	L=apriori(db,all,trans_count,item_count,min_support,item_max);
	end=clock();
	show(L,read,end-start,5,min_support);
	getchar();
	return 0;
}
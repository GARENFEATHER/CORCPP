#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
int init=10000,ch=50,space=20,initall=10000;
typedef struct x
{
	int n,space;
	char **item;
}unix;
typedef struct l
{
	int n;
	char *item;
	struct l **next;
	struct l *same,*parent;
	int supcount;
}Node;
typedef struct p
{
	char *item;
	int supcount;
	struct l *next;
}freq;
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
		quicksort(low,mid-1,all);
		quicksort(mid+1,high,all);
	}
}
int halfsearch(freq *F,int nfreq,char *item)
{
	int low,high,mid;
	low=0;
	high=nfreq-1;
	while(low < high)
	{
		mid=(low+high)/2;
		if(strcmp(item,F[mid].item) == 0) return mid;
		else if(strcmp(item,F[mid].item) >= 0) low=mid+1;
		else high=mid-1;
	}
	return -1;
}
Node* newnode(char *item)
{
	Node *T;
	T=(Node*)malloc(sizeof(Node));
	T->item=(char*)malloc(ch*sizeof(char));
	T->n=0;
	T->next=NULL;
	T->supcount=0;
	T->same=NULL;
	T->parent=NULL;
	return T;
}
Node* fptree(unix *db,char **all,int trans_count,int item_count,int min_support)
{
	int i,k,nfreq=0,u,j;
	Node *root,*p,*t,**final;
	freq *F,tmp;
	strcpy(all[item_count],"\0");//防止越界
	for(i=0;i<trans_count;i++)
		qsort(0,db[i].n-1,db[i].item);
	root=newnode("root");
	root->n=1;
	root->next=(Node**)malloc(sizeof(Node*));
	for(i=0;i<item_count;i++)
	{
		while(strcmp(all[i],all[i+1]) == 0) i++;
		nfreq++;
	}
	F=(freq*)malloc(nfreq*sizeof(freq));
	for(i=0,nfreq=0;i<nfreq;i++)
	{
		F[i].item=(char*)malloc(ch*sizeof(char));
		F[i].supcount=0;
		F[i].next=NULL;
	}
	for(i=0,k=0;i<item_count;i++)
	{
		strcpy(F[k].item,all[i]);
		while(strcmp(all[i],all[i+1]) == 0) i++;
	}
	for(i=0;i<trans_count;i++)
		for(k=0;k<nfreq;k++)
			for(j=0;j<db[i].n;j++)
				if(strcmp(F[k].item,db[i].item[j]) == 0)
				{
					F[k].supcount++;
					break;
				}
	for(i=0;i<nfreq;i++)
		for(j=0;j<nfreq-i-1;j++)
			if(F[j].supcount < F[j+1].supcount)
			{
				tmp=F[j];
				F[j]=F[j+1];
				F[j+1]=tmp;
			}
	for(i=0;i<nfreq;i++)
		if(F[i].supcount < min_support) break;
	nfreq=i+1;
	final=(Node**)malloc(nfreq*sizeof(Node*));
	for(i=0;i<nfreq;i++)
		final[i]=NULL;
	for(i=0;i<trans_count;i++)
	{
		t=p=root;
		for(j=0;j<db[i].n;j++)
		{
			while(strcmp(db[i].item[j],db[i].item[j+1]) == 0) j++;
			for(k=0;k<p->n;k++)
				if(strcmp(p->next[k]->item,db[i].item[j]) == 0) break;
			if(k != p->n)
			{
				t=p;
				p=p->next[k];
			}
			else
			{
				t=p;
				p=newnode(db[i].item[j]);
				t->next[t->n]=p;
				p->parent=t;
				t->n++;
			}
			p->supcount++;
			u=halfsearch(F,nfreq,db[i].item[j]);
			if(final[u] == NULL) final[u]=F[u].next=p;
			else
			{
				final[u]->same=p;
				final[u]=final[u]->same;
			}
		}
	}
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
	Node *root;
	int i,j,trans_count,u=0,item_count,item_max=0,k,a,start,end,read,min_support=2;
	start=clock();
	fp=fopen(ftst,"r");
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
	fclose(fp);
	end=clock();
	read=end-start;
	trans_count=i;
	item_count=u;
	start=clock();
	root=fptree(db,all,trans_count,item_count,min_support);
	end=clock();
	getchar();
	return 0;
}
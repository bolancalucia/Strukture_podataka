#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

/*
Za dvije sortirane liste L1 i L2 (mogu se proèitati iz datoteke ili unijeti ruèno, bitno je samo da su sortirane), 
napisati program koji stvara novu vezanu listu tako da raèuna:
a) L1 unija L2,
b) L1 presjek L2.
Liste osim pokazivaèa na slijedeæu strukturu imaju i jedan cjelobrojni element, po kojem su sortirane.
*/
struct Lista;
typedef struct Lista * Pos;
typedef struct Lista
{
	int el;
	Pos Next;

}_Lista;

Pos CreateNode();
int ReadList(Pos,char *);
int InsertSort(Pos);
int Print(Pos);
int Presjek(Pos,Pos,Pos);
int Unija(Pos,Pos,Pos);


void main()
{
	Pos p,l1,l2,r,u;
	char izbor;
	p=CreateNode();
	p->Next=NULL;
	l1=CreateNode();
	l1->Next=NULL;
	l2=CreateNode();
	l2->Next=NULL;
	r=CreateNode();
	r->Next=NULL;
	u=CreateNode();
	u->Next=NULL;

	puts("Zelite li liste unijeti rucno(r) ili iz datoteke(d):");
	scanf(" %c",&izbor);
	switch(tolower(izbor))
	{
	case 'r':
		InsertSort(l1);
		InsertSort(l2);
		break;
	case 'd':
		ReadList(l1,"L1.txt");
		ReadList(l2,"L2.txt");
		break;
	default:
		puts("Niste ispravno unijeli!");
	}
	Print(l1);
	puts("");
	Print(l2);
	puts("");

	Presjek(l1,l2,r);
	puts("Presjek:");
	Print(r);
	puts("");
	Unija(l1,l2,u);
	puts("Unija:");
	Print(u);
	puts("");

}

Pos CreateNode()
{
	Pos q;
	q=(Pos)malloc(sizeof(_Lista));
	if(NULL==q)
	{
		printf("NIJE SE ALOCIRALO!");
		return NULL;
	}
	else return q;
}

int ReadList(Pos p,char * dat)
{
	Pos q,temp=p;
	FILE *fp;
	fp=fopen(dat,"r");
	if(NULL==fp)
	{
		puts("DATOTEKA SE NIJE OTVORILA!");
		return -1;
	}
	while(!feof(fp))
	{
		q=CreateNode();
		if(NULL==q)
			return -1;
		fscanf(fp," %d",&q->el);

		while(p->Next!=NULL && p->Next->el < q->el)
		{
			p=p->Next;
		}

		q->Next=p->Next;
		p->Next=q;
		p=temp;
	}
	return 0;

}

int InsertSort(Pos p)
{
	return 0;
}

int Print(Pos p)
{
	p=p->Next;
	if(p==NULL)
	{
		printf("PRAZNA LISTA!");
		return -1;
	}
	while(p!=NULL)
	{
		printf("%d \t",p->el);
		p=p->Next;
	}
	return 0;
}

int Presjek(Pos l1,Pos l2,Pos r)
{
	Pos q;
	l1=l1->Next;
	l2=l2->Next;
	while(l1!=NULL && l2!=NULL)
	{
		if(l1->el < l2->el)
		{
			l1=l1->Next;
		}
		else if(l1->el > l2->el)
		{
			l2=l2->Next;
		}
		else if(l1->el==l2->el)
		{
			q=CreateNode();
			if(NULL==q)
				return -1;

			q->el=l1->el;
			l1=l1->Next;
			l2=l2->Next;

			q->Next=r->Next;
			r->Next=q;
			r=q;
		}
	}
	return 0;
}

int Unija(Pos l1,Pos l2,Pos u)
{
	Pos q,temp;
	l1=l1->Next;
	l2=l2->Next;
	while(l1!=NULL && l2!=NULL)
	{
		q=CreateNode();
			if(NULL==q)
				return -1;

		if(l1->el < l2->el)
		{
			q->el=l1->el;
			l1=l1->Next;
		}
		else if(l1->el > l2->el)
		{
			q->el=l2->el;
			l2=l2->Next;
		}
		else if(l1->el==l2->el)
		{
			q->el=l1->el;
			l1=l1->Next;
			l2=l2->Next;
			
		}
		q->Next=u->Next;
		u->Next=q;
		u=q;
	}
	if(l1==NULL)
		temp=l2;
	else temp=l1;

	while(temp!=NULL)
	{
		q=CreateNode();
		if(NULL==q)
				return -1;

		q->el=temp->el;
		temp=temp->Next;

		q->Next=u->Next;
		u->Next=q;
		u=q;
	}
	return 0;
}
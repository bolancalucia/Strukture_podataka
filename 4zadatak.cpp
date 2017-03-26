#define _CRT_SECURE_NO_WARNINGS

/*4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se èitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct Poly;
typedef struct Poly * Pos;
typedef struct Poly {
	int eks;
	int koef;
	Pos Next;

}_Poly;

Pos CreateNode();
int Zbroj(Pos,Pos,Pos);
int Umnozak(Pos,Pos,Pos);
int Print(Pos);
int ReadFile(Pos,char*);

void main()
{
	Pos p,p1,p2,z,u;
	p=CreateNode();
	p->Next=NULL;
	p1=CreateNode();
	p1->Next=NULL;
	p2=CreateNode();
	p2->Next=NULL;
	z=CreateNode();
	z->Next=NULL;
	u=CreateNode();
	u->Next=NULL;


	ReadFile(p1,"p1.txt");
	Print(p1);
	puts("");
	ReadFile(p2,"p2.txt");
	Print(p2);
	puts("");
	Zbroj(p1,p2,z);
	puts("Zbroj polinoma:");
	Print(z);
	puts("");
	Umnozak(p1,p2,u);
	puts("Umnozak polinoma:");
	Print(u);
	puts("");
}

Pos CreateNode()
{
	Pos q=(Pos)malloc(sizeof(_Poly));
	if(NULL==q)
		return NULL;
	else return q;
}

int ReadFile(Pos p,char* datoteka)
{
	Pos q,temp=p;
	FILE *fp;
	fp=fopen(datoteka,"r");
	if(NULL==fp)
	{
		printf("Nije se otvorila datoteka!");
		return -1;
	}
	while(!feof(fp))
	{
		q=CreateNode();
		if(q==NULL)
			return -1;
		fscanf(fp,"%d %d",&q->koef,&q->eks);
	
		while(p->Next!=NULL && p->Next->eks > q->eks)
		{
			p=p->Next;
		}
		q->Next=p->Next;
		p->Next=q;
		p=temp;
	}
	return 0;
}

int Print(Pos p)
{
	if(p->Next==NULL)
	{
		printf("Nema elemenata!");
		return -1;
	}
	p=p->Next;
	while(p!=NULL)
	{
		if(p->koef>0)
		{
			printf("+%dx^%d",p->koef,p->eks);
		}
		else printf("+(%d)x^%d",p->koef,p->eks);
		p=p->Next;
	}
	return 0;
}

int Zbroj(Pos p1,Pos p2,Pos z)
{
	Pos q,temp;

	p1=p1->Next;
	p2=p2->Next;
	while(p1!=NULL && p2!=NULL)
	{
		q=CreateNode();
		if(q==NULL)
			return -1;

		if(p1->eks > p2->eks)
		{
			q->eks=p1->eks;
			q->koef=p1->koef;
			p1=p1->Next;
		}
		else if(p1->eks < p2->eks)
		{
			q->eks=p2->eks;
			q->koef=p2->koef;
			p2=p2->Next;
		}
		else if(p1->eks==p2->eks)
		{
			q->eks=p1->eks;
			q->koef=p1->koef+p2->koef;
			p1=p1->Next;
			p2=p2->Next;
		}
		if(q->koef==0)
			free(q);
		else 
		{
		q->Next=z->Next;
		z->Next=q;
		z=q;
		}
	}
	if(p1!=NULL)
		temp=p1;
	else temp=p2;

	while(temp!=NULL)
	{
		q=CreateNode();
		q->eks=temp->eks;
		q->koef=temp->koef;
		temp=temp->Next;

		q->Next=z->Next;
		z->Next=q;
		z=q;
	}
	return 0;
}

int Umnozak(Pos p1,Pos p2,Pos u)
{
	Pos q,temp1=p1,temp2=p2->Next,temp;

	p1=p1->Next;
	p2=p2->Next;
	while(p1!=NULL)
	{
		p2=temp2;

		while(p2!=NULL)
		{
			
			q=CreateNode();
			if(q==NULL)
				return -1;

			q->eks=p1->eks+p2->eks;
			q->koef=p1->koef*p2->koef;

			temp1=p1;

			while(temp1->Next!=NULL && temp1->Next->eks > q->eks)
				temp1=temp1->Next;

			if(temp1->Next->eks == q->eks)
			{
				temp1->Next->koef+=q->koef;
			
			if(temp1->Next->koef==0)
			{
					temp=temp1->Next;
					temp1->Next=temp1->Next->Next;
					free(temp);
			}
			else
			{
					q->Next=u->Next;
					u->Next=q;
					u=q;
			}
			}
			
		p2=p2->Next;
		}
	p1=p1->Next;
	}
	return 0;
}
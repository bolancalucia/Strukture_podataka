/*6. Napisati program koji pomoæu vezanih listi simulira rad:
a) stoga, dodaj na poèetak skini s poèetka
b) reda.  dodaj na kraj skini s poèetka
Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 -100.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

#define RANGEMAX 100
#define RANGEMIN 10
#define RANGE RANGEMAX-RANGEMIN

struct Lista;
typedef struct Lista * Pos;
typedef struct Lista
{
	int el;
	Pos Next;

}_Lista;

Pos CreateNode();
int Push(Pos);
int PushEnd(Pos);
int Pop(Pos);
int Print(Pos);

void main()
{
	Pos p;
	char odabir;
	char izbor;
	int i=1,x;

	srand((unsigned)time(NULL));
	p=CreateNode();
	p->Next=NULL;


		printf("Zelite li stog ili red (s/r)? ");
		scanf(" %c",&odabir);
		switch (tolower(odabir))
		{
		case 's':
				while(i)
			{
				printf("Stavi element ili skini element u stogu (s/p)");
				scanf(" %c",&izbor);
				switch (tolower(izbor))
				{
				case 's':
					x=Push(p);
					printf("Stavili ste element %d\n",x);
					break;
				case 'p':
					x=Pop(p);
					printf("Skinili ste element %d\n",x);
					puts("Preostali elementi u stogu:");
					Print(p);
					break;

				default:
					printf("Krivo ste unijeli!\n");
					i--;
					break;
				}
			}
				break;
			
		case 'r':
			while(i)
			{
				printf("Stavi element ili skini element u redu (s/p) ");
				scanf(" %c",&izbor);
				switch (tolower(izbor))
				{
				case 's':
					x=PushEnd(p);
					printf("Stavili ste element %d\n",x);
					break;
				case 'p':
					x=Pop(p);
					printf("Skinili ste element %d\n",x);
					puts("Preostali elementi u redu:");
					Print(p);
					break;

				default:
					printf("Krivo ste unijeli!\n");
					i--;
					break;
				}
			}
				break;
		default:
			printf("Krivo ste unijeli!\n");
			i--;
			break;
		}
}

Pos CreateNode()
{
	Pos p;
	p=(Pos)malloc(sizeof(_Lista));
	if(NULL==p)
	{
		printf("NIJE SE ALOCIRALO!");
		return NULL;
	}
	else return p;
}

int Push(Pos p)
{
	int x;
	x=rand()%RANGE+RANGEMIN;
	Pos q;
	q=CreateNode();
	if(NULL==q)
	{
		puts("Nije se alociralo!");
		return -1;
	}
	q->el=x;
	q->Next=p->Next;
	p->Next=q;

	return x;
}

int PushEnd(Pos p)
{
	while(p->Next!=NULL)
	{
		p=p->Next;
	}
	return Push(p);
}

int Pop(Pos p)
{
	int x;
	Pos prev=p,curr=p->Next;

	if(p->Next==NULL)
	{
		printf("Prazan!\n");
		return NULL;
	}

	curr=prev->Next;
	x=curr->el;
	prev->Next=prev->Next->Next;
	free(curr);

	return x;
}

int Print(Pos p)
{
	p=p->Next;
	if(p==NULL)
	{
		printf("Prazan!\n\n");
	}
	while(p!=NULL)
	{
		printf("%d\n",p->el);	
		p=p->Next;
	}
	return 0;
}
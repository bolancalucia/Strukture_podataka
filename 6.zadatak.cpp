/*6. Napisati program koji pomoæu vezanih listi simulira rad:
a) stoga, 
b) reda. 
Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 -100.*/

#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>

struct Lista;
typedef struct Lista * Pos;
typedef struct Lista
{
	int broj;
	Pos Next;

}Lista;

Pos CreateNode()
{
	Pos q;
	q=(Pos)malloc(sizeof(Lista));

	if(q==NULL)
		printf("GREŠKA,nije alocirano!");
	else return q;
}
int PushP(Pos p) //STAVI NA POÈETAK
{
	int x;
	Pos q=CreateNode();
	if( q==NULL)
	{
		printf("GREŠKA!");
		return -1;
	}

	q->Next=p->Next;
	p->Next=q;
	q->broj=(rand()%90)+10;
	x=q->broj;
	return x;

}

int PushK(Pos p) // STAVI NA KRAJ
{
	int x;
	Pos q=CreateNode();
	if(q==NULL)
	{
		printf("GREŠKA!");
		return -1;
	}
	while(p->Next!=NULL)
	{
		p=p->Next;
	}
	q->Next=p->Next;
	p->Next=q;
	q->broj=(rand()%90)+10;
	x=q->broj;
	return x;
}

int PopP(Pos p) // SKINI S POÈETKA
{
	int x;
	Pos prev=p;Pos curr=p->Next;
	
	if(curr!=NULL)
	{
		x=curr->broj;
		prev->Next=curr->Next;
		curr->Next=NULL; //NE triba stavit
		free(curr);
		return x;
		
	}
	else 
	{
		printf("LISTA JE PRAZNA!");
		return -1;
	}

}

int PopK(Pos p) // SKINI S KRAJA
{
	int x;
	Pos prev=p;
	Pos curr=p->Next;

	while(curr->Next!=NULL)
	{
		prev=curr;
		curr=curr->Next;
	}
	if(curr!=NULL)
	{
		x=curr->broj;
		prev->Next=curr->Next;
		curr->Next=NULL; // NE triba stavit
		free(curr);
		return x;
	}
	else 
	{
		printf("LISTA JE PRAZNA!");
		return -1;
	}
}


void main()
{
	srand(unsigned(time(NULL)));
	Pos p;
	char slovo;
	int odabir=0,n=0,x,i,el;
	
	p=CreateNode();
	
	if(p==NULL)
			printf("NIJE SE ALOCIRALO!");
	p->Next=NULL;

	printf("Zelis li stog ili red ( S/R ) :");
	scanf_s(" %c",&slovo);
		if(toupper(slovo)=='S')
		{
			do
				{
					printf("Stavljate random element na stog izmedu 10 i 100:\n");
					el=PushP(p);
					n++;
					printf("Unesen je element %d.\n",el);

					printf("Odaberite '1' da program nastavi, '0' da se prekine\n");
					scanf_s("%d", &odabir);
				}
			while(odabir==1);
	
			puts("ISPIS SVIH ELEMENATA NA STOGU :");
			for (i = 0; i < n; i++)
				{
					x = PopP(p);
					printf("\n%d\t",x);
		
				}
		}
		else if(toupper(slovo)=='R')
		{
			do
				{
					printf("Stavljate random element na red izmedu 10 i 100:\n");
					el=PushP(p);
					n++;
					printf("Unesen je element %d.\n",el);

					printf("Odaberite '1' da program nastavi, '0' da se prekine\n");
					scanf_s("%d", &odabir);
				}
			while(odabir==1);
	
			puts("ISPIS SVIH ELEMENATA U REDU:");
			for (i = 0; i < n; i++)
				{
					x = PopK(p);
					printf("\n%d\t",x);
		
				}
		}
		else
		{
			printf("NISTE DOBRO UNIJELI!");
			exit(1);
		}
	
}
/*
int PopAll(Pos p) //vraca zadnji element u stogu (prvi element koji je usa u stog)
{
	int x;
	Pos prev=p;
	Pos curr=p->Next;

	if (curr==NULL)
	{
		printf("Prazna lista!\n");
		return -1;
	}

	else
	{
		while (curr->Next != NULL)
		{//	prev=curr;
			curr=curr->Next;
		}
		x=curr->Element;
		curr=prev->Next;
		prev->Next=NULL;
		free(curr);
		return x;
	}
} */
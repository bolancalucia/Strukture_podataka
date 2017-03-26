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
#define RANGEMAX 100
#define RANGEMIN 10
#define RANGE RANGEMAX-RANGEMIN

struct Lista;
typedef struct Lista * Pos;
typedef struct Lista
{
int broj;
Pos Next;

}Lista;

Pos CreateNode();
int PushP(Pos p);
int PushK(Pos p);
int PopP(Pos p);
int PopK(Pos p);

void main()
{

Pos p;
char slovo;
int odabir=0,n=0,x=0,y[10],i,el[10];

p=CreateNode();
if(p==NULL)
printf("NIJE SE ALOCIRALO!");
p->Next=NULL;

srand((unsigned)time(NULL));

printf("Zelis li stog ili red ( S/R ) :");
scanf_s(" %c",&slovo);

if(toupper(slovo)=='S')
	{ 
		do{
			printf("Odaberite: \n'1' da program stavi element na stog,\n'2' da skine element sa stoga,\n'0' da se prekine\n");
			scanf_s(" %d",&odabir);
			switch(odabir)
			{
				case 1:
				{
					printf("Stavljate random element na stog izmedu 10 i 100:\n");
					el[n]=PushP(p);
					printf("Unesen je element %d.\n",el[n]);
					n++;
					break;
				}
				case 0:
				{
					break;
				}
				case 2:
				{
					printf("Skidate element sa stoga:");
					y[n]=PopP(p);
					printf("\n%d\n",y[n]);
					n--;
					printf("Preostali elementi na stogu:\n");
					for(i=n-1;i>=0;i--)
					{
					printf("%d\n",el[i]);
					}
					break;
				}
				default: printf("NISTE DOBRO UNIJELI!");
				}
			}
		while(odabir!=0);	
	}	
else if(toupper(slovo)=='R')
	{
		do{
			printf("\nOdaberite: \n'1' da program stavi element na red,\n'2' da skine element iz reda,\n'0' da se prekine\n");
			scanf_s("%d", &odabir);
			switch(odabir)
			{
				case 1:
				{
						printf("Stavljate random element na red izmedu 10 i 100:\n");
						el[n]=PushK(p);
						printf("Unesen je element %d.\n",el[n]);
						n++;
						break;
				}

				case 0:
				{
					break;
				} 
				case 2:
				{
					printf("Skidate element sa reda:");
					y[x]=PopP(p);
					printf("\n%d\n",y[x]);
					
					x++;
					printf("Preostali elementi u redu:\n");
					for(i=n-1;i>=x;i--)
					{
					printf("\n%d\n",el[i]);
					}
					break;
				}
				default: printf("NISTE DOBRO UNIJELI!");
				}
			}
		while(odabir!=0);	
	}
else
{
printf("NISTE DOBRO UNIJELI!");
exit(1);
}
}

Pos CreateNode()
{
Pos q;
q=(Pos)malloc(sizeof(Lista));

if(q==NULL)
{
	printf("GREŠKA,nije alocirano!");
	return NULL;
}
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
q->broj=(rand()%RANGE)+RANGEMIN;
x=q->broj;
return x;

}

int PushK(Pos p) // STAVI NA KRAJ
{
while(p->Next!=NULL)
{
p=p->Next;
}
return PushP(p);
/*int x;
Pos q=CreateNode();
if(q==NULL)
{
printf("GREŠKA!");
return -1;
}

q->Next=p->Next;
p->Next=q;
q->broj=(rand()%RANGE)+RANGEMIN;
x=q->broj;
return x;*/

	/*Pos q;
	  Static Pos last=NULL;

	if(p->Next==NULL)
		last=p;

	q=CreateNode();
	if(q==NULL)
		printf("\nGreska kod alokacije memorije!!");
	else
	{
		printf("\n\tUnesi element: ");
		scanf(" %d",&q->broj);

		q->Next=NULL;
		last->Next=q;
		last=q;
	}
}*/
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

/*
int PopK(Pos p) // SKINI S KRAJA, NIKAD NE KORISTIMO
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
}*/
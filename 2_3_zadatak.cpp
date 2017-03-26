#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Osoba;
typedef struct Osoba* Pos;
typedef struct Osoba
{
	char ime[50];
	char prezime[50];
	int godrodenja;
	Pos Next;

}_Osoba;

void Stars();
void Menu();
Pos CreateNode();
int InsertUserData(Pos);
int PrintUserData(Pos);
int Insert(Pos);
int Print(Pos);
Pos FindLast(Pos);
int InsertLast(Pos);
Pos Find(Pos,char*);
Pos FindPrev(Pos,char*);
int Delete(Pos,char*);
int InsertAfter(Pos,char*);
int InsertBefore(Pos,char*);
int ReadData(Pos,char*);
int PrintData(Pos,char*);
int SortList(Pos);

int main()
{
	Pos p=NULL;
	int i=1;
	char izbor;
	char prezime[50],datoteka[50];
	p=CreateNode();
	if(p==NULL)
		exit(1);
	p->Next=NULL;

	Stars();
	while(i)
	{
	Menu();
	puts("Koju naredbu zelite izvrsiti(odaberite slovo pored nje):");
	scanf_s(" %c",&izbor);

	switch(tolower(izbor))
	{
	case 'a': //dodavanje u listu na pocetak
			Insert(p);
		break;
	case 'b': //ispis liste
			Print(p);
		break;
	case 'c': //dodavanje u listu na kraj
			InsertLast(p);
		break;
	case 'd': //pronalazak po prezimenu
			puts("Po kojem prezimenu zelite traziti?");
			scanf_s(" %[^\n]s", &prezime);
			printf("Prezime koje ste trazili nalazi se na adresi 0x%x\n",Find(p,prezime));
		break;
	case 'e': //brisanje jednog elementa
			puts("Koji element zelite obrisati? (upisite prezime)");
			scanf_s(" %[^\n]s", &prezime);
			Delete(p, prezime);
			printf("Izbrisan je element sa prezimenom %s\n", prezime);
		break;
	case 'f': // din.dodaje novi element iza odredenog elem.
			puts("Upisite prezime nakon kojeg zelite dodati novi element:");
			scanf_s(" %[^\n]s",&prezime);
			InsertAfter(p,prezime);
		break;
	case 'g': //din.dodaje novi element ispred odredenog elem.
			puts("Upisite prezime ispred kojeg zelite dodati novi element:");
			scanf_s(" %[^\n]s",&prezime);
			InsertBefore(p,prezime);
		break;
	case 'h': //sortira listu po prezimenima
			SortList(p);
		break;
	case 'i': //upisuje listu u datoteku
			puts("Upisite ime datoteke u koju zelite upisati listu:");
			scanf_s(" %[^\n]s",&datoteka);
			PrintData(p,datoteka);
		break;
	case 'j': //cita listu iz datoteke
			puts("Upisite ime datoteke  iz koje zelite iscitati podatke u listu:");
			scanf_s(" %[^\n]s",&datoteka);
			ReadData(p,datoteka);
		break;
	case 'k':
			puts("KRAJ PROGRAMA");
			i=0;
			continue;
		break;
	default:
			puts("Niste unijeli odgovarajuci znak!");
	}
	puts("\nZelite li jos odabirati: D/N");
	scanf_s(" %c",&izbor);
	if(toupper(izbor)=='D')
		continue;
	else if(toupper(izbor)=='N')
		{
			i=0;
			puts("KRAJ PROGRAMA!");
		}
	else
		{
			puts("Jeste li sigurni da zelite zavrsiti? D/N\n");
			scanf_s(" %c",&izbor);

			if(toupper(izbor)=='D')
				{
					i=0;
					puts("KRAJ PROGRAMA!");
				}
			else continue;
			
		}
	}
	return 0;
}

void Stars()
{
	puts("* * * * * * * * * * * * * * * * * * * * * * * * * * *");
	puts("* * * * * * * * * * * * * * * * * * * * * * * * * * *");
	puts("* * * * * * * * * * * * * * * * * * * * * * * * * * *");
	puts("* * * * * * * * * * MENU PROGRAMA* * * * * * * * * * ");
	puts("* * * * * * * * * * * * * * * * * * * * * * * * * * *");
	puts("* * * * * * * * * * * * * * * * * * * * * * * * * * *");
	puts("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
}

void Menu()
{
	puts("\t\t\tOPCIJE:\n");
	puts(" a) dinamicki dodaje novi element na pocetak liste");
	puts(" b) ispisuje listu");
	puts(" c) dinamicki dodaje novi element na kraj liste");
	puts(" d) pronalazi element u listi (po prezimenu)");
	puts(" e) brise odreðeni element iz liste");
	puts(" f) dinamicki dodaje novi element iza odredenog elementa");
	puts(" g) dinamicki dodaje novi element ispred odredenog elementa");
	puts(" h) sortira listu po prezimenima osoba");
	puts(" i) upisuje listu u datoteku");
	puts(" j) cita listu iz datoteke");
	puts(" k) KRAJ programa\n");
	
}

Pos CreateNode()
{
	Pos q;
	q=(Pos)malloc(sizeof(_Osoba));
	if(q==NULL)
		return NULL;
	else return q;
}

int InsertUserData(Pos p)
{
	scanf_s("%s %s %d",&p->ime,&p->prezime,&p->godrodenja);
	return 0;
}

int PrintUserData(Pos p)
{
	printf("Ime: %s \t Prezime: %s \t Godina rodenja: %d\n",p->ime,p->prezime,p->godrodenja);
	return 0;
}

int Insert(Pos p)
{
	Pos q=CreateNode();
	if(q==NULL)
	{
		printf("Greska pri alociranju!");
		exit(1);
	}
	InsertUserData(q);
	q->Next=p->Next;
	p->Next=q;
	return 0;
}

int Print(Pos p)
{
	if(p->Next==NULL)
	{
		printf("Lista je prazna!");
		return -1;
	}
	p=p->Next;
	while(p!=NULL)
	{
		PrintUserData(p);
		p=p->Next;
	}
	return 0;
}

Pos FindLast(Pos p)
{
	while(p->Next!=NULL)
	{
		p=p->Next;
	}
	return p;
}

int InsertLast(Pos p)
{
	p=FindLast(p);
	return Insert(p);
}

Pos Find(Pos p,char* prezime)
{
	while(p->Next!=NULL && strcmp(p->prezime,prezime)!=0)
	{
		p=p->Next;
	}
	if(p==NULL)
	{
		printf("Nema tog elementa!");
		return NULL;
	}
	return p;
}

Pos FindPrev(Pos p,char* prezime)
{
	Pos prev=p,curr=p->Next;
	if(curr->Next==NULL)
	{
		printf("Nema tog elementa!");
		return NULL;
	}
	while(curr->Next!=NULL && strcmp(p->prezime,curr->Next->prezime)!=0)
	{
		prev=curr;
		curr=curr->Next;
	}
	if(curr==NULL)
		return NULL;
	else return prev;
}

int Delete(Pos p,char* prezime)
{
	Pos prev=FindPrev(p,prezime),curr=p->Next;

	if(prev==NULL)
	{
		printf("Nema tog elementa!");
		return NULL;
	}
	curr=prev->Next;
	prev->Next=curr->Next;
	free(curr);

	return 0;
}

int InsertAfter(Pos p,char* prezime)
{
	Pos prev=Find(p,prezime);
	Pos curr=NULL,q=NULL;
	if(prev==NULL)
	{
		printf("Nema tog elementa!");
		return -1;
	}
	curr=prev->Next;
	
	q=CreateNode();
	if(q==NULL)
		return -1;
	InsertUserData(q);
	prev->Next=q;
	q->Next=curr;

	return 0;
}

int InserBefore(Pos p,char* prezime)
{
	Pos prev=FindPrev(p,prezime);
	Pos curr=Find(p,prezime);
	Pos q;
	if(curr=NULL)
	{
		printf("Nema tog elementa!");
		return -1;
	}
	if(prev==NULL)
	{
		printf("Nema tog elementa!");
		return -1;
	}
	curr=prev->Next;
	
	q=CreateNode();
	if(q=NULL)
		return -1;
	InsertUserData(q);
	prev->Next=q;
	q->Next=curr;

	return 0;
}

int ReadData(Pos p,char* datoteka)
{
	FILE *fp;
	fopen_s(&fp,datoteka,"r");
	Pos q=NULL;
	if(fp==NULL)
	{
		printf("Greska u otvaranju datoteke!");
		return -1;
	}
	while(!feof(fp))
	{
		Pos q=CreateNode();
		if(q==NULL)
		{
			printf("Greska pri alociranju!");
			exit(1);
		}
		fscanf_s(fp,"%s %s %d",&q->ime,&q->prezime,&q->godrodenja);

		q->Next=p->Next;
		p->Next=q;
		p=q;
	}

	return 0;
}

int PrintData(Pos p,char* datoteka)
{
	FILE *fp;
	fopen_s(&fp,datoteka,"w");
	if(fp==NULL)
	{
		printf("Greska pri otvaranju datoteke!");
		return -1;
	}
	p=p->Next;
	while(p!=NULL)
	{
		fprintf(fp,"Ime: %s \t Prezime: %s \t Godina rodenja: %d\n",p->ime,p->prezime,p->godrodenja);
		p=p->Next;
	}

	return 0;
}

int SortList(Pos p)
{
	Pos pocetak=p->Next;
	Pos prev,curr,curr2,temp;
	p=p->Next;

	while(p->Next->Next!=NULL)
	{
		prev=p;
		curr=prev->Next;
		curr2=curr->Next;

		if( strcmp(curr->prezime,curr2->prezime)>0)
		{
			prev->Next=curr;
			curr->Next=curr2;

			temp=curr2->Next;
			curr2->Next=curr;
			curr->Next=temp;
			prev->Next=curr2;


		}
		else 
		{
			prev=curr;
			curr=curr2;
			curr2=curr2->Next;
		}
		p=pocetak;
	}
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"Strukturepodataka23.h"

void main()
{
	Position p=NULL;
	char izbor;
	int i=1;
	char prezime[50];
	char FileName[100];
	
	p=CreateNode();
	p->Next=NULL;
	p->Prev=NULL;

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
			InsertEnd(p);
		break;
	case 'd': //pronalazak po prezimenu
			puts("Po kojem prezimenu zelite traziti?");
			scanf(" %[^\n]s", &prezime);
			printf("Prezime koje ste trazili nalazi se na adresi 0x%x\n",Find(p,prezime));
		break;
	case 'e': //brisanje jednog elementa
			puts("Koji element zelite obrisati? (upisite prezime)");
			scanf(" %[^\n]s", &prezime);
			Delete(p, prezime);
			printf("Izbrisan je element sa prezimenom %s\n", prezime);
		break;
	case 'f': // din.dodaje novi element iza odredenog elem.
			puts("Upisite prezime nakon kojeg zelite dodati novi element:");
			scanf(" %[^\n]s",&prezime);
			InsertNext(p,prezime);
		break;
	case 'g': //din.dodaje novi element ispred odredenog elem.
			puts("Upisite prezime ispred kojeg zelite dodati novi element:");
			scanf(" %[^\n]s",&prezime);
			InsertPrevious(p,prezime);
		break;
	case 'h': //sortira listu po prezimenima
			SortList(p);
		break;
	case 'i': //upisuje listu u datoteku
			puts("Upisite ime datoteke u koju zelite upisati listu:");
			scanf(" %[^\n]s",&FileName);
			DataToFile(p,FileName);
		break;
	case 'j': //cita listu iz datoteke
			puts("Upisite ime datoteke  iz koje zelite iscitati podatke u listu:");
			scanf(" %[^\n]s",&FileName);
			FileToData(p,FileName);
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
}
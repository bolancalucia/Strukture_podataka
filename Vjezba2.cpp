#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct _student;
typedef struct _student* Position;
struct _student
{
	char ime[128];
	char prezime[128];
	int godina_rodenja;
	Position Next;
};

void Insert(Position);
void PrintList(Position);
void InsertEnd(Position);
Position FindPrez(Position);
void DeletePrez(Position);
void InsertAfter(Position);
Position FindPrevPrez(Position);
void InsertBefore(Position);
void ReadFromFile(Position);
void PrintToFile(Position);
void SortList(Position);

void main(void)
{
	struct _student head;
	Position studentF = NULL;
	char izbor = 0;

	head.Next = NULL;

	while(toupper(izbor) != 'K')
	{
		printf("****************************************\r\n");
		printf("***   VJEZBA BR. 02  -  Vezane liste ***\r\n");
		printf("****************************************\r\n");
		printf("\r\n\r\n");
		printf("\t1. Unos\r\n");
		printf("\t2. Ispis\r\n");
		printf("\t3. Unos na kraj\r\n");
		printf("\t4. Pronadji po prezimenu\r\n");
		printf("\t5. Izbrisi po prezimenu\r\n");
		printf("\t6. Unos nakon studenta\r\n");
		printf("\t7. Unos prije studenta\r\n");
		printf("\t8. Sortiraj\r\n");
		printf("\t9. Ucitaj listu iz datoteke\r\n");
		printf("\tA. Ispisi listu u datoteku\r\n");
		printf("\tK. Izlaz iz programa\r\n");
		printf("\r\n\tIzbor : ");

		scanf_s(" %c", &izbor, 1);

		switch(izbor)
		{
		case '1' :
			Insert(&head);
			break;
		case '2' :
			PrintList(head.Next);
			break;
		case '3' :
			InsertEnd(&head);
			break;
		case '4' :
			studentF = FindPrez(head.Next);
			if(studentF != NULL)
				printf("\r\nTrazeni student je :\r\n%s %s %d\r\n", studentF->ime, studentF->prezime, studentF->godina_rodenja);
			else
				printf("\r\nStudent s trazenim prezimenom nije pronaden\r\n");
			break;
		case '5' :
			DeletePrez(&head);
			PrintList(head.Next);
			break;
		case '6' :
			InsertAfter(&head);
			PrintList(head.Next);
			break;
		case '7' :
			InsertBefore(&head);
			PrintList(head.Next);
			break;
		case '8':
			SortList(&head);
			PrintList(head.Next);
			break;
		case '9':
			ReadFromFile(&head);
			PrintList(head.Next);
			break;
		case 'A' :
			PrintToFile(head.Next);
			break;
		case 'k' :
		case 'K' :
			break;
		default:
			printf("\r\nPogresan izbor <%c>.\r\nPokusajte ponovno.\r\n", izbor);
			break;
		}
	}
}

void Insert(Position P)
{
	Position q;

	q=(Position)malloc(sizeof(struct _student));
	if(q == NULL)
		printf("\r\nGRESKA!\r\nAlokacija memorije neuspjela.\r\n");
	else
	{
		printf("Unesite ime, prezime i godinu rodenja studenta :\r\n");
		scanf_s(" %s %s %d", q->ime, 128, q->prezime, 128, &q->godina_rodenja);

		q->Next = P->Next;
		P->Next = q;
	}
}

void PrintList(Position P)
{
	if(P == NULL)
		printf("\r\nLista je prazna!\r\n");
	else
	{
		printf("\r\n\r\nU listi se nalaze : \r\n");
		while(P != NULL)
		{
			printf("\t%s %s %d\r\n", P->ime, P->prezime, P->godina_rodenja);
			P = P->Next;
		}
	}
	printf("\r\n\r\n");
}

void InsertEnd(Position P)
{
	while(P->Next != NULL)
		P = P->Next;

	Insert(P);
}

Position FindPrez(Position P)
{
	char prez[128];

	printf("\r\nUnesite prezime koje trazite : ");
	scanf_s(" %s", prez, 128);
	while(P != NULL && _strcmpi(P->prezime, prez) != 0)
		P = P->Next;

	return P;
}
void DeletePrez(Position P)
{
	Position tmp;
	char prez[128];

	printf("\r\nUnesite prezime koje zelite izbrisatie : ");
	scanf_s(" %s", prez, 128);
	while(P->Next != NULL && _strcmpi(P->Next->prezime, prez) != 0)
		P = P->Next;

	tmp = P->Next;
	if(tmp != NULL)
	{
		P->Next = tmp->Next;
		printf("\r\nIz liste se brise : %s %s %d", tmp->ime, tmp->prezime, tmp->godina_rodenja);
		free(tmp);
	}
}

void InsertAfter(Position P)
{
	Position tmp;

	tmp = FindPrez(P);

	if(tmp != NULL)
		Insert(tmp);
}

Position FindPrevPrez(Position P)
{
	char prez[128];

	printf("\r\nUnesite prezime koje trazite : ");
	scanf_s(" %s", prez, 128);
	while(P->Next != NULL && _strcmpi(P->Next->prezime, prez) != 0)
		P = P->Next;

	if(P->Next == NULL)
		P = NULL;
	return P;
}

void InsertBefore(Position P)
{
	Position tmp;

	tmp = FindPrevPrez(P);

	if(tmp != NULL)
		Insert(tmp);
}
void ReadFromFile(Position P)
{
	FILE *stream;
	char fname[1024];
	Position q;

	printf("\r\nUnesite datoteku za citanje : ");
	scanf_s(" %s", fname, 1024);

	fopen_s(&stream, fname, "r");
	if(stream == NULL)
		printf("\r\nDatoteka \"%s\" nije otvorena.", fname);
	else
	{
		while(!feof(stream))
		{
			q = (Position)malloc(sizeof(struct _student));
			if(q == NULL)
				printf("Greska!\r\nMemorija nije alocirana.");
			else
			{
				fscanf_s(stream, " %s %s %d", q->ime, 128, q->prezime, 128, &q->godina_rodenja);

				q->Next = P->Next;
				P->Next = q;
			}
		}
		fclose(stream);
	}
}

void PrintToFile(Position P)
{
	FILE *stream;
	char fname[1024];

	printf("\r\nUnesite datoteku za upisivanje : ");
	scanf_s(" %s", fname, 1024);

	fopen_s(&stream, fname, "w+");
	if(stream == NULL)
		printf("\r\nDatoteka \"%s\" nije otvorena.", fname);
	else
	{
		while(P != NULL)
		{
			fprintf(stream, "%s %s %d\r\n", P->ime, P->prezime, P->godina_rodenja);
			P = P->Next;
		}
		fclose(stream);
	}
}

void SortList(Position P)
{
	Position i, j, prev_j, end;

	end = NULL;

	while(P->Next != end)
	{
		i = P;
		prev_j = i->Next;
		j = prev_j->Next;

		while(j != end)
		{
			if(_strcmpi(prev_j->prezime, j->prezime) > 0)
			{
				prev_j->Next = j->Next;
				j->Next = prev_j;
				i->Next = j;
			}
			else
				i = prev_j;
			prev_j = i->Next;
			j = prev_j->Next;
		}
		end = prev_j;
	}
}
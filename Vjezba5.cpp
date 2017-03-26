#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct _Cvor;
typedef struct _Cvor* Position;
struct _Cvor
{
	int koeficijent;
	Position Next;
};

void ReadFromFile(Position);
void PrintList(Position);
void Presijek(Position, Position, Position);
void Unija(Position, Position, Position);

void main(void)
{
	struct _Cvor L1, L2, P, U;

	L1.Next = NULL;
	L2.Next = NULL;
	P.Next = NULL;
	U.Next = NULL;

	ReadFromFile(&L1);
	ReadFromFile(&L2);

	printf("\r\nL1 : ");
	PrintList(L1.Next);

	printf("\r\nL2 : ");
	PrintList(L2.Next);

	Presijek(L1.Next, L2.Next, &P);
	printf("\r\nP : ");
	PrintList(P.Next);

	Unija(L1.Next, L2.Next, &U);
	printf("\r\nP : ");
	PrintList(U.Next);

	printf("\r\n\r\n");
}

void ReadFromFile(Position P)
{
	Position q, tmp;
	char ime_dat[1024];
	FILE *stream;

	printf("Unesite ime dadoteke za citanje : ");
	scanf_s(" %s", ime_dat, 1024);

	fopen_s(&stream, ime_dat, "r");
	if(stream == NULL)
		printf("\r\nGRESKA!\r\n%s datoteka nije otvorena.", ime_dat);
	else
	{
		while(!feof(stream))
		{
			q = (Position) malloc(sizeof(struct _Cvor));
			if(q == NULL)
				printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
			else
			{
				fscanf_s(stream, " %d", &q->koeficijent);

				tmp = P;
				while(tmp->Next != NULL && tmp->Next->koeficijent >= q->koeficijent)
					tmp = tmp->Next;

				q->Next = tmp->Next;
				tmp->Next = q;
			}
		}
		fclose(stream);
	}
}

void PrintList(Position P)
{
	while(P != NULL)
	{
		printf(" %d", P->koeficijent);
		P = P->Next;
	}
}

void Presijek(Position L1, Position L2, Position P)
{
	Position q;

	while(L1 && L2)
	{
		if(L1->koeficijent > L2->koeficijent)
			L1 = L1->Next;
		else if(L1->koeficijent < L2->koeficijent)
			L2 = L2->Next;
		else
		{
			q = (Position)malloc(sizeof(struct _Cvor));
			if(!q)
				printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
			else
			{
				q->koeficijent = L1->koeficijent;

				q->Next = P->Next;
				P->Next = q;

				P = q;
			}
			L1 = L1->Next;
			L2 = L2->Next;
		}
	}
}

void Unija(Position L1, Position L2, Position U)
{
	Position q, tmp;

	while(L1 && L2)
	{
		q = (Position)malloc(sizeof(struct _Cvor));
		if(!q)
		{
			printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
			break;
		}
		else
		{
			if(L1->koeficijent > L2->koeficijent)
			{
				q->koeficijent = L1->koeficijent;
				L1 = L1->Next;
			}
			else if(L1->koeficijent < L2->koeficijent)
			{
				q->koeficijent = L2->koeficijent;
				L2 = L2->Next;
			}
			else
			{
				q->koeficijent = L1->koeficijent;
				L1 = L1->Next;
				L2 = L2->Next;
			}

			if(U->koeficijent == q->koeficijent)
				free(q);
			else
			{
				q->Next = U->Next;
				U->Next = q;
				U=q;
			}
		}
	}

	if(L1)
		tmp = L1;
	else
		tmp = L2;

	while(tmp)
	{
		q = (Position)malloc(sizeof(struct _Cvor));
		if(!q)
		{
			printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
			break;
		}
		else
		{
			q->koeficijent = tmp->koeficijent;

			if(U->koeficijent == q->koeficijent)
				free(q);
			else
			{
				q->Next = U->Next;
				U->Next = q;
				U=q;
			}

			tmp = tmp->Next;
		}
	}
}
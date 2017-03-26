#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct _Cvor;
typedef struct _Cvor* Position;
struct _Cvor
{
	int koeficijent;
	int eksponent;
	Position Next;
};

void ReadFromFile(Position);
void PrintList(Position);
void AddPoly(Position, Position, Position);
void MulPoly(Position, Position, Position);

void main(void)
{
	struct _Cvor P1, P2, S, M;

	P1.Next = NULL;
	P2.Next = NULL;
	S.Next = NULL;
	M.Next = NULL;

	ReadFromFile(&P1);
	ReadFromFile(&P2);

	printf("\r\nP1(x) = ");
	PrintList(P1.Next);

	printf("\r\nP2(x) = ");
	PrintList(P2.Next);

	printf("\r\nS(x) = ");
	AddPoly(P1.Next, P2.Next, &S);
	PrintList(S.Next);

	printf("\r\nM(x) = ");
	MulPoly(P1.Next, P2.Next, &M);
	PrintList(M.Next);

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
				fscanf_s(stream, " %d %d", &q->koeficijent, &q->eksponent);

				tmp = P;
				while(tmp->Next != NULL && tmp->Next->eksponent > q->eksponent)
					tmp = tmp->Next;

				if(tmp->Next != NULL && tmp->Next->eksponent == q->eksponent)
				{
					tmp->Next->koeficijent += q->koeficijent;
					free(q);
					if(tmp->Next->koeficijent == 0)
					{
						q = tmp->Next;
						tmp->Next = q->Next;

						free(q);
					}
				}
				else
				{
					q->Next = tmp->Next;
					tmp->Next = q;
				}
			}
		}
		fclose(stream);
	}
}

void PrintList(Position P)
{
	bool first = true;
	while(P != NULL)
	{
		if(first)
		{
			printf("%dx^%d", P->koeficijent, P->eksponent);
			first = false;
		}
		else
			if(P->koeficijent > 0)
				printf(" +%dx^%d", P->koeficijent, P->eksponent);
			else
				printf(" %dx^%d", P->koeficijent, P->eksponent);

		P = P->Next;
	}
}

void AddPoly(Position P1, Position P2, Position S)
{
	Position q, tmp;
	while(P1 != NULL && P2 != NULL)
	{
		q = (Position) malloc(sizeof(struct _Cvor));
		if(q == NULL)
		{
			printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
			break;
		}
		
		if(P1->eksponent > P2->eksponent)
		{
			q->eksponent = P1->eksponent;
			q->koeficijent = P1->koeficijent;
			P1 = P1->Next;
		}
		else if(P1->eksponent < P2->eksponent)
		{
			q->eksponent = P2->eksponent;
			q->koeficijent = P2->koeficijent;
			P2 = P2->Next;
		}
		else
		{
			q->eksponent = P1->eksponent;
			q->koeficijent = P1->koeficijent + P2->koeficijent;
			P1 = P1->Next;
			P2 = P2->Next;
		}

		q->Next = S->Next;
		S->Next = q;

		S = q;
	}

	if(P1 == NULL)
		tmp = P2;
	else
		tmp = P1;

	while(tmp != NULL)
	{
		q = (Position) malloc(sizeof(struct _Cvor));
		if(q == NULL)
		{
			printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
			break;
		}

		q->eksponent = tmp->eksponent;
		q->koeficijent = tmp->koeficijent;

		q->Next = S->Next;
		S->Next = q;

		S = q;

		tmp = tmp->Next;
	}

}

void MulPoly(Position P1, Position P2, Position M)
{
	Position q, tmp, i, j;

	i = P1;

	while(i != NULL)
	{
		j = P2;
		while(j!=NULL)
		{
			q = (Position) malloc(sizeof(struct _Cvor));
			if(q == NULL)
			{
				printf("\r\nGRESKA!\r\nMemorija nije alocirana.");
				break;
			}

			q->eksponent = i->eksponent + j->eksponent;
			q->koeficijent = i->koeficijent * j->koeficijent;

			tmp = M;

			while(tmp->Next != NULL && tmp->Next->eksponent > q->eksponent)
				tmp = tmp->Next;

			if(tmp->Next != NULL && tmp->Next->eksponent == q->eksponent)
			{
				tmp->Next->koeficijent += q->koeficijent;
				free(q);

				if(tmp->Next->koeficijent == 0)
				{
					q = tmp->Next;
					tmp->Next = q->Next;

					free(q);
				}
			}
			else
			{
				q->Next = tmp->Next;
				tmp->Next = q;
			}

			j = j->Next;
		}
		i = i->Next;
	}


}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

struct _Cvor;
typedef struct _Cvor* Position;
struct _Cvor
{
	int Element;
	Position Next;
};

int RandomGeneratedNumber(int, int);
void PushS(Position, int);
void PushR(Position, int);
void Pop(Position);
void Print(Position);
bool IsThere(Position, int);

void main(void)
{
	int x = 0;
	char izbor = 0;
	struct _Cvor S, R;

	S.Next = NULL;
	R.Next = NULL;

	while(izbor != 'k' && izbor != 'K')
	{
		printf("\r\n\t********************");
		printf("\r\n\t***   IZBORNIK   ***");
		printf("\r\n\t********************");
		printf("\r\n");
		printf("\r\n\t1.\tPush stog");
		printf("\r\n\t2.\tPop stog");
		printf("\r\n\t3.\tPush red");
		printf("\r\n\t4.\tPop red");
		printf("\r\n\tk.\tIzlaz iz programa");
		printf("\r\nIzbor : ");
		scanf_s(" %c", &izbor);
		
		switch(izbor)
		{
		case '1':
			while(x == 0 || IsThere(S.Next, x))
				x = RandomGeneratedNumber(10, 10000);
			PushS(&S, x);
			x = 0;
			Print(S.Next);
			break;
		case '2':
			Pop(&S);
			Print(S.Next);
			break;
		case '3':
			while(x == 0 || IsThere(R.Next, x))
				x = RandomGeneratedNumber(10, 100);
			PushR(&R, x);
			x = 0;
			Print(R.Next);
			break;
		case '4':
			Pop(&R);
			Print(R.Next);
			break;
		case 'k':
			printf("\r\n\r\n***   Bye bye :)   ***\r\n\r\n");
			break;
		default:
			printf("\r\nPogresan unos!\r\nPokusajte ponovno.\r\n\r\n\r\n");
		}
	}

}
int RandomGeneratedNumber(int min, int max)
{
	srand((unsigned)time(NULL));
	return rand()%(max-min) + min;
}

bool IsThere(Position P, int x)
{
	int i = 0;
	while(P != NULL &&  P->Element != x)
		P = P->Next;
	if(P)
		return true;
	else
		return false;
}

void PushS(Position P, int x)
{
	Position q;

	q=(Position)malloc(sizeof(struct _Cvor));
	if(q)
	{
		q->Element = x;

		q->Next = P->Next;
		P->Next = q;
	}
}

void PushR(Position P, int x)
{
	static Position last;
	Position q;

	if(P->Next == NULL)
		last = P;
	q=(Position)malloc(sizeof(struct _Cvor));
	if(q)
	{
		q->Element = x;

		q->Next = last->Next;
		last->Next = q;

		last = q;
	}
}

void Pop(Position P)
{
	Position tmp;

	tmp = P->Next;

	if(tmp)
	{
		P->Next = tmp->Next;
		printf("\r\nBrise se : %d\r\n", tmp->Element);
		free(tmp);
	}
}

void Print(Position P)
{
	if(P)
		printf("\r\nU listi se nalaze :");
	else
		printf("\r\nLista je prazna.");
	while(P)
	{
		printf(" %d", P->Element);
		P = P->Next;
	}

	printf("\r\n\r\n\r\n");
}
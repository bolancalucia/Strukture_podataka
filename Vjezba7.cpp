#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct _Cvor;
typedef struct _Cvor* Position;
struct _Cvor
{
	int Element;
	Position Next;
};

void Push(Position, int);
void Pop(Position, int *);
int Calculate(char, int, int);

int main(void)
{
	FILE *stream;
	char *ime_dat;
	Position NumberStack;

	NumberStack = (Position)malloc(sizeof(struct _Cvor));
	if(NumberStack == NULL)
		return -1;
	NumberStack->Next = NULL;

	ime_dat = (char*)malloc(sizeof(char)*1024);
	if(ime_dat == NULL)
		return -2;

	printf("\r\nUnesite ime datoteke za citanje : \r\n");
	scanf_s(" %s", ime_dat, 1024);
	
	fopen_s(&stream, ime_dat, "r");
	if(stream == NULL)
	{
		printf("\r\nDatoteka %s nije otvorena!", ime_dat);
		return -3;
	}
	else
	{
		char _rbuff[4];
		while(!feof(stream))
		{
			fscanf_s(stream, " %s", _rbuff, 4);
			//printf("\r\n%s", _rbuff);

			if(isdigit(_rbuff[0]))
			{
			//Broj je trebamo ga spremiti na stog
				Push(NumberStack, atoi(_rbuff));
			}
			else
			{
			//Operacija je trebamo dobaviti operande sa stoga, izraèunati operaciju i upisati rezultat na stog
				int x = 0;
				int y = 0;
				int r = 0;
				Pop(NumberStack, &y);
				Pop(NumberStack, &x);
				r = Calculate(_rbuff[0], x, y);
				Push(NumberStack, r);
			}
		}
		fclose(stream);
	}
	printf("\r\n\r\nRezuletat je : %d\r\n", NumberStack->Next->Element);
	free(NumberStack->Next);
	free(NumberStack);
	return 0;
}

void Pop(Position P, int *n)
{
	Position tmp;
	tmp = P->Next;
	if(tmp)
	{
		P->Next = tmp->Next;
		*n =  tmp->Element;
		free(tmp);
	}
}

void Push(Position P, int x)
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

int Calculate(char op, int x, int y)
{
	int result = 0;
	switch(op)
	{
	case '+':
		result = x + y;
		break;
	case '-':
		result = x - y;
		break;
	case '*':
		result = x * y;
		break;
	case '/':
		if(y > 0)
			result = x / y;
		break;
	default:
		;
	}
	//printf("\r\n%d = %d %c %d", result, x, op, y);
	return result;
}
/*
10. Napisati program koji iz datoteke èita postfiks izraz i zatim stvara stablo proraèuna. Iz
gotovog stabla proraèuna upisati u datoteku infiks izraz.
*/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>


struct _Node;
struct _Stack;

typedef struct _Node *NPos;
typedef struct _Stack *SPos;

struct _Node
{
	char* El;
	NPos Right;
	NPos Left;
};

struct _Stack
{
	NPos NodeElement;
	SPos Next;
};


void Push(SPos, NPos);
NPos Pop(SPos);
void InorderPrint(NPos);
void PreorderPrint(NPos);
void PostorderPrint(NPos);


int main(void)
{
	FILE *stream;
	char *ime_dat;
	SPos PosfixStack;
	NPos root;

	PosfixStack = (SPos)malloc(sizeof(struct _Stack));
	if(PosfixStack == NULL)
		return -1;
	PosfixStack->Next = NULL;
	PosfixStack->NodeElement = NULL;

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
		while(!feof(stream))
		{
			NPos q = (NPos)malloc(sizeof(struct _Node));
			if(q)
			{
				q->El = (char*)malloc(sizeof(char)*5);
				q->El[4] = '\0';
				fscanf_s(stream, " %s", q->El, 4);
				q->Left = NULL;
				q->Right = NULL;

				if(atoi(q->El) || isalpha(q->El[0]))
				{
					//Numerièka vrijednost trebamo spremiti na stog
					Push(PosfixStack, q);
				}
				else
				{
					//Operacija je trebamo dobaviti operande sa stoga, povezati ih i ponovno spremiti na stog
					q->Right = Pop(PosfixStack);
					q->Left = Pop(PosfixStack);
					Push(PosfixStack, q);
				}
			}
		}
		fclose(stream);
	}
	root = Pop(PosfixStack);
	printf("\r\n\r\n* Preorder ispis :\t");
	PreorderPrint(root);
	printf("\r\n\r\n* Inorder ispis :\t");
	InorderPrint(root->Left);
	printf(" %s ", root->El);
	InorderPrint(root->Right);
	printf("\r\n\r\n* Postorder ispis :\t");
	PostorderPrint(root);
	printf("\r\n\r\n");
	free(PosfixStack);
	return 0;
}

void Push(SPos S, NPos N)
{
	SPos q;
	q = (SPos)malloc(sizeof(struct _Stack));
	if(q)
	{
		q->NodeElement = N;
		q->Next = S->Next;
		S->Next = q;
	}
}

NPos Pop(SPos S)
{
	SPos tmp;
	NPos q;

	tmp = S->Next;
	S->Next = tmp->Next;
	q = tmp->NodeElement;
	free(tmp);
	return q;
}

void InorderPrint(NPos N)
{
	if(N != NULL)
	{
		if(atoi(N->El) || isalpha(N->El[0]))
			;
		else
			printf("(");
		InorderPrint(N->Left);
		printf(" %s ", N->El);
		InorderPrint(N->Right);
		if(atoi(N->El) || isalpha(N->El[0]))
			;
		else
			printf(")");
	}
}

void PostorderPrint(NPos N)
{
	if(N != NULL)
	{
		PostorderPrint(N->Left);
		PostorderPrint(N->Right);
		printf(" %s", N->El);
	}
}

void PreorderPrint(NPos N)
{
	if(N != NULL)
	{
		printf(" %s", N->El);
		PreorderPrint(N->Left);
		PreorderPrint(N->Right);
	}
}
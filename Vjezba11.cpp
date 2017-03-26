/*
11. Napisati program koji generira 25 sluèajnih brojeva u opsegu od 50 do 1000 i formira
od njih AVL stablo. Ispisati koji su sve brojevi generirani i na kraju formirano stablo.
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define _MIN 50
#define _MAX 1000
#define _NUMEL 25

struct AvlNode;
typedef struct AvlNode * Node;

struct AvlNode
{
	int Element;
	Node Left;
	Node Right;
	int Height;
};

Node Insert(int, Node);
void Print(Node);
int Height(Node);
Node SingleRotateWithLeft(Node);
Node SingleRotateWithRight(Node);
Node DoubleRotateWithLeft(Node);
Node DoubleRotateWithRight(Node);
int Max(int, int);




void main()
{
	Node root = NULL;
	int i = 0;
	
	srand( (unsigned)time( NULL ) );

	printf("\n\tGenerirani su brojevi:\n\t");
	for(i = 0; i<_NUMEL; i++)
	{
		int x = rand()%(_MAX - _MIN) + _MIN;
		printf("%d ", x);
		
		root = Insert(x, root);
	}

	printf("\n\n\n\n\tGenerirano AVL stablo je:\n");
	Print(root);

	
	printf("\n\n\n");


}

Node Insert(int X, Node T)
{
	
	if(NULL == T)
	{
		T = (Node)malloc(sizeof(struct AvlNode));
		T->Left = NULL;
		T->Right = NULL;
		T->Element = X;
		T->Height = 0;
	}
	else if(X > T->Element)
	{
		T->Right = Insert(X, T->Right);
		if(Height(T->Right) - Height(T->Left) == 2)
			if(X>T->Right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
	}
	else if(X < T->Element)
	{
		T->Left = Insert(X, T->Left);
		if(Height(T->Left) - Height(T->Right) == 2)
			if(X<T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
	}
	
	T->Height = Max(Height(T->Left), Height(T->Right))+1;
	return T;
}

void Print(Node T)
{
	static int n = 0;
	int i;

	if(-1 == n)
		n = 0;
	
	if(NULL != T)
	{
		n++;
		Print(T->Right);

		printf("\n");
		for(i = 0; i < n; i++)
			printf("\t");

		printf(" %d", T->Element);
		
		printf("\n");
		n++;
		Print(T->Left);
	}
	n--;
}

int Height(Node P)
{
	if(P == NULL)
		return -1;
	else 
		return P->Height;
}

Node SingleRotateWithLeft(Node K2)
{
	Node K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Left), K2->Height) + 1;

	return K1;
}


Node SingleRotateWithRight(Node K2)
{		
	Node K1;

	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;

	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(K2->Height, Height(K1->Right)) + 1;

	return K1;
}

Node DoubleRotateWithLeft(Node K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);

	return SingleRotateWithLeft(K3);
}


Node DoubleRotateWithRight(Node K3)
{
	K3->Right = SingleRotateWithLeft(K3->Right);

	return SingleRotateWithRight(K3);
}

int Max(int x, int y)
{
	if (x > y)
		return x;
	else 
		return y;
}
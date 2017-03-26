#include<stdio.h>
#include<stdlib.h>
#include <string.h>


struct _student;
typedef struct _student* _pstud;

struct _student
{
	char ime[128];
	char prezime[128];
	int bodovi;
};

int CountRecords(char *);
int ReadRecords(char *, _pstud);

void main(void)
{
	_pstud popis=NULL;
	_pstud spopis=NULL;
	char file_name[1024]={0};
	int nRecords = 0;
	int MaxBod = 0;

	printf("\t\t***************************\r\n");
	printf("\t\t***   POPIS STUDENATA   ***\r\n");
	printf("\t\t***     Vjezba br. 1    ***\r\n");
	printf("\t\t***************************\r\n");
	printf("\r\n");
	printf("\r\n\t\tUnesite naziv datoteke za citanje: \r\n\r\n\t\t");
	scanf_s(" %s", file_name, 1024);
	
	nRecords = CountRecords(file_name);
	if(nRecords > 0)
	{
		popis=(_pstud)malloc(sizeof(struct _student) * nRecords);
		spopis = popis;
		MaxBod = ReadRecords(file_name, spopis);
		printf("\r\n\r\n\t\tU datoteci '%s' je pronadeno %d zapisa.\r\n\r\n", file_name, nRecords);
		printf("\r\n%3s \t%15s\t%15s\t%3s   %3s = %7s\r\n", "Rbr", "Ime", "Prezime", "Bod", "Max", "RelBod");
		for(int i = 0 ; i < nRecords ; i++)
			printf("\r\n%3d.\t%15s\t%15s\t%3d / %3d = % 6.2f", i+1, popis[i].ime, popis[i].prezime, popis[i].bodovi, MaxBod, ((float)popis[i].bodovi/MaxBod) * 100);
	}
	printf("\r\n\r\n");

}

int CountRecords(char *fname)
{
	FILE *dat;
	errno_t err;
	int n = 0;
	char buffer[1024];

	err = fopen_s(&dat, fname, "r");
	if(err != 0)
		printf( "Datoteka '%s' NIJE otvorena\n", fname);
	else
	{
		while(!feof(dat))
		{
			strncpy_s( buffer, _countof(buffer), "", _TRUNCATE ); // Isprazniti buffer -> buffer = *blank

			fgets(buffer, 1024, dat);
			if(strlen(buffer) != 0)
				n++;
		}
		if(fclose(dat))
		{
			printf("Nemogu zatvoriti datoteku '%s'.\r\nZatvaranje svih datoteka.", fname);
			_fcloseall();
		}
	}
	return n;
}

int ReadRecords(char *fname, _pstud P)
{
	FILE *dat;
	errno_t err;
	int nMax = 0;

	err = fopen_s(&dat, fname, "r");
	if(err != 0)
		printf( "Datoteka '%s' NIJE otvorena\n", fname);
	else
	{
		while(!feof(dat))
		{
			fscanf_s(dat, " %s %s %d", P->ime, 128, P->prezime, 128, &P->bodovi);
			if(P->bodovi > nMax)
				nMax = P->bodovi;
			P++;
		}
		if(fclose(dat))
		{
			printf("Nemogu zatvoriti datoteku '%s'.\r\nZatvaranje svih datoteka.", fname);
			_fcloseall();
		}
	}
	return nMax;
}
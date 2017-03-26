/*Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše odreðeni element iz liste,
f) dinamièki dodaje novi element iza odreðenog elementa,
g) dinamièki dodaje novi element ispred odreðenog elementa,
h) sortira listu po prezimenima osoba,
i) upisuje listu u datoteku,
j) èita listu iz datoteke.*/

struct Osoba;

typedef struct Osoba *Position;
typedef struct Osoba{

	char ime[50];
	char prezime[50];
	int godinarodenja;
	Position Next;
	Position Prev;

}Osoba;

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

Position CreateNode() //kreira listu,alocira memoriju i provjerava je li se memorija alocirala
{
	Position q=(Position)malloc(sizeof(Osoba));

	if(q==NULL)
		return NULL;
	else return q;
}

int InsertUserData(Position p) //unosi elemente liste
{
	puts("Unesite ime osobe:");
	scanf(" %[^\n]s", &p->ime);
	puts("Unesite prezime osobe:");
	scanf(" %[^\n]s", &p->prezime);
	puts("Unesite godinu rodenja:");
	scanf_s(" %d",&p->godinarodenja);

	return 0;
}

int PrintUserData(Position p) //ispisuje elemente liste
{
	
	printf("%s %s %d\n",p->ime,p->prezime,p->godinarodenja);

	return 0;
}

int Insert(Position p) // unosi listu,najprije je alocira,provjeri je li se alocirala i jesu li se elementi unijeli pa je veže s drugom listom
{
	Position q;
	int result=0;

	q=CreateNode();

	if(q==NULL)
		return -1;

	result=InsertUserData(q);

	if(result!=0)
	{
		free(q);
		return result;
	}

	q->Next=p->Next;
	p->Next=q;
	q->Prev=p;
	return result;
}

int Print(Position p) // ispisuje listu od pocetka do kraja,ako je lista prazna daje upozorenje
{
	puts("Elementi liste:");
	if(p->Next==NULL)
	{
		puts("Empty list!");
		return 1;
	}
	p=p->Next; // da ne ispisuje head
	while(p!=NULL)
	{
		PrintUserData(p);
		p=p->Next;
	}

	return 0;
}

Position FindLast(Position p) //trazi zadnji clan
{
	while(p->Next!=NULL)
		p=p->Next;

	return p;
}

int InsertEnd(Position p) // prvo pronalazi zadnji clan pa dodaje jedan iza njega
{
	Position q=FindLast(p);
	return Insert(q);
}

Position Find(Position p,char* prezime) // pronalazi clan preko prezimena
{
	while(p!=NULL && strcmp(prezime,p->prezime)!=0)  //strcmp ako su isti vraæa 0
	{
		p=p->Next;
	}
	return p;
}

Position FindPrevious(Position p,char* prezime) //trazi prethodnik tako da je prev head,a curr njegov next i to traje dok ne dode do kraja i vraca prev(ako ne nade vraca NULL)
{
	/*Position prev=p;
	Position curr=prev->Next;

	while(curr!=NULL && strcmp(prezime,curr->prezime)!=0)
	{
		prev=curr;
		curr=curr->Next; //prev->Next;
	}
	if(curr==NULL)
		return NULL;

	return prev;*/

	while(p!=NULL && strcmp(prezime,p->prezime)!=0)
	{
		p->Prev=p;
		p=p->Next;
	}
	if(p==NULL)
		return NULL;
	else return p->Prev;
}

int Delete(Position p,char* prezime)
{
	/*Position curr=NULL;
	Position prev=NULL;

	prev=FindPrevious(p,prezime);

	if(prev!=NULL)
	{
		curr=prev->Next;
		prev->Next=curr->Next; // ili prev->Next->Next;
		free(curr);
	}

	return 0; */

	Position temp=NULL;
	while(p->Next!=NULL && strcmp(prezime,p->prezime)!=0)
	{
		temp=p;
		p=p->Next;
	}
	if(p==NULL)
		return -1;
	temp->Next=p->Next;
	// p->Next=NULL;
	free(p);

	return 0;
}

int InsertPrevious(Position p,char* prezime) //umece clan izmedu p i q
{
	Position q=p->Next;
	Position novi=NULL;

	while(strcmp(q->prezime,prezime)!=0)
	{
		p=q;
		q=q->Next;
	}
	novi=CreateNode();
	InsertUserData(novi);

	p->Next=novi;
	novi->Next=q;
	novi->Prev=p;
	q->Prev=novi;
	
	return 0;
}

int InsertNext(Position p,char* prezime) //umece clan iza q
{
	Position q=p->Next;
	Position novi=NULL;

	while(strcmp(q->prezime,prezime)!=0)
	{
		p=q;
		q=q->Next;
	}
	novi=CreateNode();
	InsertUserData(novi);

	novi->Next=q->Next;
	q->Next=novi;
	novi->Prev=q;
	novi->Next->Prev=q;

	return 0;
}

int SortList(Position p)  /*deklariramo prev,curr,prev_curr,temp i end,sort funkcionira tako da se ide prvo do zadnja dva clana i njih usporedi i sortira,
							te se s kraja pomice ulijevo dok ne dodemo do pocetka tj.do enda */
{
	Position prev=p, curr=NULL, temp=NULL, end=NULL; 

	while (prev->Next != end)
	{
		prev=p; 
		curr = prev->Next;

		while(curr->Next!= end) //provjerava po dva clana (curr i njegov next) dok ne dode do kraja liste
		{
			if(strcmp( curr->prezime, curr->Next->prezime)>0)
			{
				temp =  curr->Next;  //zamjena
				prev->Next=temp; 
				curr->Next = temp->Next;
				temp->Next = curr;

				curr= temp;
			}

			prev=curr; //prev=prev->Next;  NE MOŽE--->jer onda ne obavi zamjenu kroz jedan poziv funkcije
			curr = curr->Next;
		}
		end = curr; // jasan mi je princip al how this shit works
	}
	return 0;
}

int DataToFile(Position p,const char *FileName) //otvorimo datoteku,provjerimo je li postoji,dok ne dodemo do kraja liste ispisujemo u file
{
	FILE *fp;

	fp=fopen(FileName,"a+"); //da nastavi pisat na kraj file-a ako veæ u njemu nesto postoji
	
	if(fp==NULL)
	{
		puts("Datoteka ne postoji!");
		return -1;
	}

	p=p->Next; // da se pomakne s heada na 1.element

	while(p!=NULL)
	{
		fprintf(fp,"%s %s %d\n",p->ime,p->prezime,p->godinarodenja);
		p=p->Next;
	}

	fclose(fp);

	return 0;
}

int FileToData(Position p,const char *FileName) //otvaramo dat.,provjerimo je li postoji,dok ne dodemo do kraja citamo iz datoteke,postavimo pokazivace i idemo na iduci clan
{
	FILE *fp;
	Position q=NULL;

	fp=fopen(FileName,"r");

	if(fp==NULL)
	{
		puts("Datoteka ne postoji!");
		return -1;
	}
	while(!feof(fp))
	{
		q=CreateNode();	

		if(3!=fscanf(fp,"%s %s %d",q->ime,q->prezime,&q->godinarodenja))
		{
			break;
		}

		q->Next=p->Next;
		p->Next=q;
		p=q;
	}
	fclose(fp);

	return 0;
}
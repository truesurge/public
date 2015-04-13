#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <string.h>

#define MAX_STUDENTS 5

struct student
{
	char name[100];
	int  mark[3];
};

student students[MAX_STUDENTS];
int count=0;

void Write()
{
	FILE *f = fopen("data.bin","wb+");
	fwrite(&count,sizeof(int),1,f);
	for(int i=0;i<count;i++)
		fwrite(&students[i],sizeof(struct student),1,f);
	fclose(f);
}

void Read()
{
	FILE *f = fopen("data.bin","rb");
	int c;
	if (fread(&c,sizeof(int),1,f)==0) 
	{
		count=0;
		return;
	}
	else count=c;
	for(int i=0;i<count;i++)
		fread(&students[i],sizeof(struct student),1,f);
	fclose(f);
}

student In()
{
	student t;
	system("cls");
	printf("Name? ");
	fflush(stdin);
	gets(t.name);
	printf("Marks :\nPhysics ? ");
	scanf("%d",&t.mark[0]);
	printf("Math ? ");
	scanf("%d",&t.mark[1]);
	printf("Comp. tech ? ");
	scanf("%d",&t.mark[2]);	
	return t;
}

void  Out(student t,bool line)
{
	printf("³ %15s ³ %1d ³ %1d ³ %1d ³\n",t.name,t.mark[0],t.mark[1],t.mark[2]);
	if (line) printf("ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÅÄÄÄÅÄÄÄ´\n");
}

void Add()
{
	if(count>MAX_STUDENTS) return;
	students[count]=In();
	count++;
}

void Edit()
{
	printf("Which record we are editing?\n");
	int c;
	scanf("%d",&c);
	if( (c>count-1) || (c<0) ) return;
	students[c]=In();
}

void Count_twos()
{
	system("cls");
	int m[3];
	m[0]=m[1]=m[2]=0;
	for(int i=0;i<count;i++)
	{
		if(students[i].mark[0]==2) m[0]++;
		if(students[i].mark[1]==2) m[1]++;
		if(students[i].mark[2]==2) m[2]++;
	}
	printf("There are : \n %d two-s for physics\n %d two-s for math\n %d two-s for comp. science\n",m[0],m[1],m[2]);
	getch();
}

void Print()
{
	system("cls");
	if(count==0)
	{
		printf("There are no students\n");
		getch();
		return;
	}
	printf("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄ¿\n");
	printf("³ %15s ³ %1c ³ %1c ³ %1c ³\n","Name",'P','M','C');
	printf("ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÅÄÄÄÅÄÄÄ´\n");
	for(int i=0;i<count;i++)
		Out(students[i],i==count-1?0:1);
	printf("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÙ\n");
	getch();
}

void Del()
{
	int c;
	printf("Which record we are deleting?\n");
	scanf("%d",&c);
	if(c<0) return;
	for(int i=c;i<count-1;i++)
		students[i]=students[i+1];
	count--;
	getch();
}

void Show_bad()
{
	system("cls");
	if(count==0)
	{
		printf("There are no students\n");
		getch();
		return;
	}
	printf("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÂÄÄÄÂÄÄÄ¿\n");
	printf("³ %15s ³ %1c ³ %1c ³ %1c ³\n","Name",'P','M','C');
	printf("ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÅÄÄÄÅÄÄÄ´\n");
	for(int i=0;i<count;i++)
	{
		if((students[i].mark[0]==2)||(students[i].mark[1]==2)||(students[i].mark[2]==2)) Out(students[i],i==count-1?0:1);
	}	
	printf("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÙ\n");
	getch();	
}

int main(void)
{
	Read();
	int cycle=1;
	while (cycle)
	{
		system("cls");
		printf("What to do :\n  1 - Add a student\n  2 - Del student\n  3 - Show count of two-s\n  4 - Show bad students\n  5 - Show all students\n  6 - Edit student\n  0 - Exit\n");
		scanf("%d",&cycle);
		switch(cycle)
		{
			case 1:
				Add();
				break;
			case 2:
				Del();
				break;
			case 3:
				Count_twos();
				break;
			case 4:
				Show_bad();
				break;
			case 5:
				Print();
				break;
			case 6:
				Edit();
				break;
			default:
				continue;
				break;
		}
	}	
	Write();
	return 0;
}

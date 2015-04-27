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

int Get()
{
	int count = 0;
	student st;
	FILE *f = fopen("data.bin","rb");
	fseek(f,0,SEEK_SET);
	while(fread(&st,sizeof(student),1,f)) count++;
	fclose(f);
	return count;
}

student Read(int pos)
{
	student st;
	
	FILE *f = fopen("data.bin","rb");
	fseek(f,0,SEEK_SET);
	fseek(f,sizeof(student)*pos,SEEK_SET);
	fread(&st,sizeof(student),1,f);
	fclose(f);
	
	return st;
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
	student st=In();
	FILE *f = fopen("data.bin","a+b");
	fwrite(&st,sizeof(struct student),1,f);
	fclose(f);
}

void Edit()
{
	int count= Get(),pos;
	if(count==0) return;
	
	printf("Which we are editing? 0 - %d \n",count);	
	
	scanf("%d",&pos);
	
	student stb=In();
		
	FILE *tmp=fopen("tmp.bin","w+b");
	student st;
	while(count--)
	{
		st=Read(count);
		if((count-1)==pos) st = stb;
		fwrite(&st,sizeof(student),1,tmp);
	}
	
	fclose(tmp);
	remove("data.bin");
	rename("tmp.bin","data.bin");
}

void Count_twos()
{
	system("cls");
	int m[3];
	student st;
	int count = Get();
	m[0]=m[1]=m[2]=0;
	for(int i=0;i<count;i++)
	{
		st=Read(i);
		if(st.mark[0]==2) m[0]++;
		if(st.mark[1]==2) m[1]++;
		if(st.mark[2]==2) m[2]++;
	}
	printf("There are : \n %d two-s for physics\n %d two-s for math\n %d two-s for comp. science\n",m[0],m[1],m[2]);
	getch();
}

void Print()
{
	system("cls");
	int count=Get();
		
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
		Out(Read(i),i==count-1?0:1);
	printf("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÙ\n");
	getch();
}

void Del()
{
	int count = Get();
	if(count==0) return;
	FILE *tmp=fopen("tmp.bin","w+b");
	student st;
	count--;
	while(count--)
	{
		st=Read(count);
		fwrite(&st,sizeof(student),1,tmp);
	}
	fclose(tmp);
	remove("data.bin");
	rename("tmp.bin","data.bin");
}

void Show_bad()
{
	system("cls");
	student st;
	int count = Get();
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
		st=Read(i);
		if((st.mark[0]==2)||(st.mark[1]==2)||(st.mark[2]==2)) Out(st,i==count-1?0:1);
	}	
	printf("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÁÄÄÄÁÄÄÄÙ\n");
	getch();	
}

int main(void)
{
	int cycle=1;
	while (cycle)
	{
		system("cls");
		printf("In file : %d records \n\n",Get());
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
	return 0;
}

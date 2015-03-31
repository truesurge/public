#include <cstdio>
#include <cstdlib>

int main(void)
{
	FILE *f = fopen("file.bin","wb+");
	int n,num;
	printf("How many to input?\n");
	scanf("%d",&n);
	fwrite(&n,sizeof(int),1,f);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&num);
		fwrite(&num,sizeof(int),1,f);
	}
	fclose(f);
	printf("done\n");
	system("pause");
	return 0;
}

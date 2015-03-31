#include <cstdio>
#include <cstdlib>

int main(void)
{
	FILE *in = fopen("file.bin","rb");
	FILE *out = fopen("out.bin","wb+");
	
	int n,*nums;
	fread(&n,sizeof(int),1,in);
	nums=new int[n];
	printf("Source : ");
	for(int i=0;i<n;i++)
	{
		fread(&nums[i],sizeof(int),1,in);
		printf("%d ",nums[i]);
	}
	printf("\n");
	fclose(in);
	
	printf("Altered : ");
	for(int i=0;i<n;i++)
	{
		if(nums[i]>0) nums[i]+=nums[0];
		else 		  nums[i]-=nums[n-1];
		printf("%d ",nums[i]);
		fwrite(&nums[i],sizeof(int),1,out);
	}
	printf("\n");
	fclose(out);
	
	system("pause");
	return 0;
}

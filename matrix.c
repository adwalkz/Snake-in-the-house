#include<stdio.h>
#define MAX_ROW 100
#define MAX_COL 100

void main()
{
	int A[MAX_ROW][MAX_COL];
	int r,c,i,j,I=-1,J=-1;
	
	printf("Enter No of rows: ");
	scanf("%d", &r);
	printf("Enter No. of columns: ");
	scanf("%d", &c);
	
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			printf("Enter A[%d][%d]: \t", i+1, j+1);
			scanf("%d", &A[i][j]);
		}

	printf("\n Your array look like -\n");
	for(i=0;i<r;i++)
	{
		printf("\n");
		for(j=0;j<c;j++)
			printf("%d\t", A[i][j]);
	}
	printf("\n");

	printf("\n Task :- \n\t");
	
	while(++I<r && ++J<c)
	{
		for(i=I;i<r;i++)
			printf("%4d", A[i][I]);

		for(j=J+1;j<c;j++)
			printf("%4d", A[r-1][j]);

		r--;
		for(i=r-1;i>=I;i--)
			printf("%4d", A[i][c-1]);

		c--;
		for(i=c-1;i>I;i--)
			printf("%4d ", A[I][i]);
	}

	printf("\n\n");
}


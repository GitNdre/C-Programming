// Perkalian Matrix
#include <stdio.h>

int main(){
	int column1, row1, column2, row2, a[100][100], b[100][100];
	int ans[100][100];
	printf("Enter row and column of first matrix: ");
	scanf("%d %d", &row1, &column1);
		printf("Enter row and column of second matrix: ");
	scanf("%d %d", &row2, &column2);
	
	while(column1 != row2){
		puts("Invalid Input! column of first matrix not equal to row of second.\n\n");
		printf("Enter row and column of first matrix: ");
		printf("Enter row and column of first matrix: ");
		scanf("%d %d", &row1, &column1);
		printf("Enter row and column of second matrix: ");
		scanf("%d %d", &row2, &column2);
	}

	printf("\nEnter the First Matrix:\n");
	for(int i = 0; i < row1; i++){
		for(int j = 0; j < column1; j++){
			scanf("%d", &a[i][j]);
		}
	}
	
	printf("\nEnter the Second Matrix:\n");
	for(int i = 0; i < row2; i++){
		for(int j = 0; j < column2; j++){
			scanf("%d", &b[i][j]);
		}
	}

	for(int i = 0; i < row1; i++){
		for(int j = 0; j < column2; j++){
			ans[i][j] = 0;
		}
	}

	for(int i = 0; i < row1; i++){
		for(int j = 0; j < column2; j++){
			for(int k = 0; k < column1; k++){
				ans[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	
	printf("\nOutput Matrix:\n");
	for(int i = 0; i < row1; i++){
		for(int j = 0; j < column2; j++){
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}

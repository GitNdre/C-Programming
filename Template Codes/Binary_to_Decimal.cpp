#include <stdio.h>

long long int Convert(char biner[]){
	long long int num = 0;
	int i = 0, n;
	while (biner[i] != '\0'){
		n = biner[i] - 48;
		if(n != 0 && n != 1){
			return -1;
		}
		else{
			num = num * 2 + n;
		}
		i++;
	} 
	return num;
}

int main(){
	char binary[255];
	scanf("%s", binary);
	int decimal = Convert(binary);
	if(decimal == -1){
		printf("INVALID\n");
	}
	else{
		printf("Decimal Number: %d\n", decimal);
	}
}
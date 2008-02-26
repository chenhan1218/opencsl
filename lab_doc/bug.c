#include<stdio.h>

void encode(char* str){

	char* tempStr = str;
	while( *tempStr != 0 ){
		(*tempStr)++;
		tempStr++;
	}
}

int main(int argc, char* argv[]){

	int i;

	for(i = 0; i < argc; i++){
		encode(argv[i+1]);
		printf("%s\n", argv[i+1]);
	}
}

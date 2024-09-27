#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	char* filename = malloc(sizeof(char) * 10);
	scanf("%s", filename);

	int filedes;
	if((filedes = creat(filename, 0644)) == -1){
		printf("failure\n");
		exit(1);
	}
	else{
		printf("file descriptor : %d\n", filedes);
		exit(0);
	}
	return 0;
}
	

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	char* filename = malloc(sizeof(char)*100);
	char* mode = malloc(sizeof(char)*10);
	scanf("%s", filename);
	scanf("%s", mode);
	
	FILE* filedes;
	filedes = fopen(filename, mode);
	if(filedes == NULL){
		printf("open failure\n");
		exit(1);
	}
	else{
		printf("file descriptor : %p\n", filedes);
		exit(0);
	}
}

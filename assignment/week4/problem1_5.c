#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	char* filename = malloc(sizeof(char) * 10);
	scanf("%s", filename);
	
	int filedes;
	if((filedes = open(filename, O_RDONLY)) == -1){
		printf("open failure\n");
		exit(1);
	}
	else{
		char buffer[1024];
		ssize_t nread = 0;
		int word = 0;
		int line = 0;
		while((nread = read(filedes, buffer, 1024)) > 0){
			for(ssize_t i = 0; i < nread; ++i){
				if(buffer[i] == '\n' && buffer[i - 1] != '\n'){
					word++;
					line++;
				}
				else if(buffer[i] == ' ' || buffer[i] == '\t'){
					word++;
				}
			}
		}
		printf("word : %d\n", word);
		printf("line : %d\n", line);
		exit(0);
	}
	return 0;
}

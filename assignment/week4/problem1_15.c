#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	ssize_t nread;
	char buffer[1024];

	char* filename = malloc(sizeof(char) * 100);
	scanf("%s", filename);
	int infile = open(filename, O_RDONLY);
	if(infile == -1){
		printf("infile doesn't exist.\n");
		nread = read(0, buffer, 1024);
	}
	else{
		nread = read(infile, buffer, 1024);
		close(infile);
	}
	scanf("%s", filename);
	int outfile = open(filename, O_WRONLY);
	if(outfile == -1){
		printf("outfile doesn't exist.\n");
		write(1, buffer, nread);
	}
	else{
		write(outfile, buffer, nread);
		close(outfile);
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	char* infilename = malloc(sizeof(char));
	char* outfilename = "out.txt";

	scanf("%s", infilename);
	int infile, outfile;
	if((infile = open(infilename, O_RDONLY)) == -1){
		printf("infile failure\n");
		exit(1);
	}
	else if((outfile = open(outfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1){
		printf("outfile failure\n");
		exit(1);
	}
	else{
		char buffer[1024];
		ssize_t nread;
		while((nread = read(infile, buffer, 1024)) > 0){
			write(outfile, buffer, nread);
		}
		printf("success\n");
		exit(0);
	}
}

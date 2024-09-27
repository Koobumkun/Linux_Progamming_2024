#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	char buffer[41];
	int infile = open("residents", O_RDONLY);
	if(infile == -1){
		printf("infile failure\n");
		exit(1);
	}
	ssize_t nread;
	while((nread = read(infile, buffer, 41)) > 0){
		for(ssize_t i = 0; i < nread; ++i){
			printf("%c", buffer[i]);
		}
	}
	close(infile);
	exit(0);
}

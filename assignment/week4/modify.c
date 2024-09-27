#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int infile = open("residents", O_RDONLY);
	if(infile == -1){
		printf("infile failure\n");
		exit(1);
	}

	int outfile = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(outfile == -1){
		printf("outfile failure\n");
		exit(1);
	}
	char ibuffer[1024];
	char obuffer[41];
	ssize_t nread;
	int seek = 0;
	while((nread = read(infile, ibuffer, 1024)) > 0){
		for(ssize_t i = 0; i < nread; ++i){
			if(ibuffer[i] == '\n'){
				if(seek == 40){
					obuffer[seek] = '\n';
					write(outfile, obuffer, 41);
				}
				else{
					while(seek < 40){
						obuffer[seek] = ' ';
						++seek;
					}
					obuffer[seek] = '\n';
					write(outfile, obuffer, 41);
				}
				seek = 0;
			}
			else{
				obuffer[seek] = ibuffer[i];
				++seek;
			}
		}
	}
	close(infile);
	close(outfile);
	return 0;
}

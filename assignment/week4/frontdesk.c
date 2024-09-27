#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

bool check(const char* residents, const char* empty){
	for(int i = 0; i < 41; ++i){
		if(residents[i] != empty[i]){
			return false;
		}
	}
	return true;
}
bool cmd_check(const char* cmd, const char* menu){
	for(int i = 0; i < 10; ++i){
		if(cmd[i] != menu[i]){
			return false;
		}
	}
	return true;
}
ssize_t findfree(int residents){
	if(residents == -1){
		printf("infile failure\n");
		exit(1);
	}
	if(lseek(residents, (off_t) 0, SEEK_SET) == -1){
		printf("seek failure\n");
		exit(1);
	}
	char empty[41];
	for(int i = 0; i < 41; ++i){
		if(i == 40){
			empty[i] = '\n';
		}
		else{
			empty[i] = ' ';
		}
	}
	ssize_t room = 1;
	ssize_t nread;
	char buffer[41];
	while((nread = read(residents, buffer, 41)) > 0){
		if(check(buffer, empty)){
			return room;
		}
		else{
			lseek(residents, (off_t) 41 * room, SEEK_SET);
			++room;
		}
	}
	return room;
}
void freeroom(int residents, int room){
	if(residents == -1){
		printf("infile failure\n");
		exit(1);
	}
	if(lseek(residents, (off_t) (room - 1) * 41, SEEK_SET) == -1){
		printf("seek failure\n");
		exit(1);
	}
	char empty[41];
	for(int i = 0; i < 41; ++i){
    	if(i == 40){
        	empty[i] = '\n';
        }
        else{             
			empty[i] = ' ';
 		}
   	}
	write(residents, empty, 41);
	exit(0);
}
void addguest(int residents){
	ssize_t room = findfree(residents);
	char* guest = malloc(sizeof(char) * 41);
	scanf("%s", guest);
	char buffer[41];
	for(int i = 0; i < 40; ++i){
		buffer[i] = ' ';
	}
	buffer[40] = '\n';
	for(int i = 0; i < 41; ++i){
		if(guest[i] == '\0'){
			break;
		}
		else{
			buffer[i] = guest[i];
		}
	}
	lseek(residents, (off_t) (room - 1) * 41, SEEK_SET);
	write(residents, buffer, 41);
	exit(0);
}
int main(){
	char* cmd = malloc(sizeof(char)*10);
	scanf("%s", cmd);
	char ff[10] = "findfree";
	char fr[10] = "freeroom";
	char ag[10] = "addguest";
	if(cmd_check(cmd, ff)){
		int residents = open("residents", O_RDONLY);
		if(residents == -1){
			printf("infile failure\n");
			exit(1);
		}
		ssize_t room;
		room = findfree(residents);
		printf("room : %ld\n", room);
	}
	else if(cmd_check(cmd,fr)){
		int residents = open("residents", O_RDWR);
		if(residents == -1){
			printf("infile failure\n");
			exit(1);
		}
		int room;
		scanf("%d", &room);
		freeroom(residents, room);
		printf("free room %d\n", room);
		exit(0);
	}
	else if(cmd_check(cmd, ag)){
		int residents = open("residents", O_RDWR);
		addguest(residents);
		exit(0);
	}
}	

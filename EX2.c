/*
 * EX2.c
 *
 *  Created on: 28 nov. 2023
 *      Author: ensea
 */

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

#define buffsize 128
const char * welcome = "$ ./enseash\nBienvenue dans le shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";
//const char * ensea = "\nenseash % ";

int ex2(int argc, char * argv[]){

	char buffer[buffsize];
	strcpy(buffer,welcome);
	ssize_t ret;

	if(write(STDOUT_FILENO, buffer, buffsize) == -1){perror("write");exit(EXIT_FAILURE);} //writing the welcome message

	while(1){   // REPL = read-eval-print-loop
		while((ret = read(STDIN_FILENO, buffer, buffsize)) > 0){ //reading the command input
			char * command = "fortune";
			buffer[strcspn(buffer, "\n")] = '\0';
			if(strcmp(buffer,command) == 0){
				int pid, status;
				pid = fork();   // creating a new process to execute the command "fortune"

				if(pid == -1){perror("fork");exit(EXIT_FAILURE);}

				if(pid == 0){
					execl("/usr/games/fortune","fortune", (char *)NULL);
					perror("execl");
					exit(EXIT_FAILURE);
				} else if(waitpid(pid,&status,0) == -1){
					perror("wait");
					exit(EXIT_FAILURE);}

			}

			command = "ls";
			buffer[strcspn(buffer, "\n")] = '\0';
			if(strcmp(buffer,command) == 0){
				int pid, status;
				pid = fork();   // creating a new process to execute the command "ls"

				if(pid == -1){perror("fork");exit(EXIT_FAILURE);}

				if(pid == 0){
					execlp("ls","ls", (char *)NULL);
					perror("execlp");
					exit(EXIT_FAILURE);
				} else if(waitpid(pid,&status,0) == -1){
					perror("wait");
					exit(EXIT_FAILURE);}

			}

		}

		if(ret == -1){perror("read");exit(EXIT_FAILURE);}

	}

	exit(EXIT_SUCCESS);
}


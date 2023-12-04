/*
 * EX3.c
 *
 *  Created on: 4 déc. 2023
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
const char * ensea = "\nenseash % ";
const char * goodbye = "Bye bye...\n$";

int main(int argc, char * argv[]){

	char buffer[buffsize];
	strcpy(buffer,welcome);
	ssize_t ret;

	if(write(STDOUT_FILENO, welcome, strlen(welcome)) == -1){perror("write");exit(EXIT_FAILURE);} //writing the welcome message

	while(1){   // REPL = read-eval-print-loop
		while((ret = read(STDIN_FILENO, buffer, buffsize)) > 0){ //reading the command input
			buffer[strcspn(buffer, "\n")] = '\0';
				if(strcmp(buffer, "exit") == 0){
					if(write(STDOUT_FILENO, goodbye, strlen(goodbye)) == -1){perror("write");exit(EXIT_FAILURE);} //writing exit message
					exit(EXIT_SUCCESS);}

				int pid, status;
				pid = fork();   // creating a new process to execute the command entered in buffer

				if(pid == -1){perror("fork");exit(EXIT_FAILURE);}

				if(pid == 0){
					execlp(buffer,buffer, (char *)NULL);
					perror("execlp");
					exit(EXIT_FAILURE);
				} else if(waitpid(pid,&status,0) == -1){
					perror("wait");
					exit(EXIT_FAILURE);}

				if(write(STDOUT_FILENO, ensea, strlen(ensea)) == -1){perror("write");exit(EXIT_FAILURE);} //writing the new line prompt message

		}

		if(ret == -1){perror("read");exit(EXIT_FAILURE);}

	}

	exit(EXIT_SUCCESS);
}


/*
 * EX4.c
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
const char * ensea = "enseash % ";
const char * goodbye = "Bye bye...\n$";

int main(int argc, char * argv[]){

	char buffer[buffsize];
	ssize_t ret;
	int time_1;
	int time_2;

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
					execlp(buffer,buffer, (char *)NULL); //executing the command in the child process
					perror("invalid command");
					exit(EXIT_FAILURE);
				} else if(waitpid(pid,&status,0) == -1){ //the father process is waiting for the child to finish
					perror("wait");
					exit(EXIT_FAILURE);}
				buffer[0] = '\0'; //emptying the buffer

				if ((WIFEXITED(status) != 0)&&(WEXITSTATUS(status) != 0)){ //checking if child ended correctly and that we have a return value
					int exit_status = WEXITSTATUS(status);
					strcat(buffer, "enseash [exit:");
					strcat(buffer, (char*) &exit_status);
					strcat(buffer, "] % ");
					if(write(STDOUT_FILENO, buffer, buffsize) == -1){perror("write");exit(EXIT_FAILURE);}
				} else if((WIFSIGNALED(status) != 0)&&(WTERMSIG(status) != 0)){ //checking the signal that killed the child (if there is one)
					int signal_status = WTERMSIG(status);
					strcat(buffer, "enseash [sign:");
					strcat(buffer, (char*) &signal_status);
					strcat(buffer, "] % ");
					if(write(STDOUT_FILENO, buffer, buffsize) == -1){perror("write");exit(EXIT_FAILURE);}
				}

				if(write(STDOUT_FILENO, ensea, strlen(ensea)) == -1){perror("write");exit(EXIT_FAILURE);} //writing the new line prompt message

		}

	}

	exit(EXIT_SUCCESS);
}



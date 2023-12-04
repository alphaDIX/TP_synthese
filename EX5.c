/*
 * EX5.c
 *
 *  Created on: 4 déc. 2023
 *      Author: aurelien zart - kevin lin
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
#include <time.h>

#define buffsize 128
#define thousand 1000
const char * welcome = "$ ./enseash\nBienvenue dans le shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";
const char * ensea = "\nenseash % ";
const char * goodbye = "Bye bye...\n$";

int main(int argc, char * argv[]){

	char buffer[buffsize];
	ssize_t ret;
	struct timespec start, stop;
	double time;

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
					if(clock_gettime(CLOCK_REALTIME, &start) == -1){perror("clock gettime");exit( EXIT_FAILURE );}
					execlp(buffer,buffer, (char *)NULL); //executing the command in the child process
					perror("invalid command");
					exit(EXIT_FAILURE);
				} else if(waitpid(pid,&status,0) == -1){ //the father process is waiting for the child to finish
					perror("wait");
					exit(EXIT_FAILURE);}
				if(clock_gettime(CLOCK_REALTIME, &stop) == -1){perror("clock gettime");exit( EXIT_FAILURE );}
			    time = ( stop.tv_sec - start.tv_sec )*thousand + ( stop.tv_nsec - start.tv_nsec )/thousand; //converting time from s to ms and ns to ms

				buffer[0] = '\0'; //emptying the buffer
				if ((WIFEXITED(status))){                       //checking if child ended correctly
					int exit_status = WEXITSTATUS(status);
					strcat(buffer, "\nenseash [exit:");
					if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1){perror("write");exit(EXIT_FAILURE);}
					snprintf(buffer,sizeof(exit_status),"%d",exit_status);
				    strcat(buffer, "|");
					if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1){perror("write");exit(EXIT_FAILURE);}
					snprintf(buffer,strlen(buffer),"%lf",time);
					strcat(buffer, "ms] % ");
					if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1){perror("write");exit(EXIT_FAILURE);}
				} else if((WIFSIGNALED(status))){              //checking the signal that killed the child (if there is one)
					int signal_status = WTERMSIG(status);
					strcat(buffer, "\nenseash [sign:");
					if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1){perror("write");exit(EXIT_FAILURE);}
					snprintf(buffer,sizeof(signal_status),"%d",signal_status);
					strcat(buffer, "|");
					if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1){perror("write");exit(EXIT_FAILURE);}
					snprintf(buffer,strlen(buffer),"%lf",time);
					strcat(buffer, "ms] % ");
					if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1){perror("write");exit(EXIT_FAILURE);}
				} else if(write(STDOUT_FILENO, ensea, strlen(ensea)) == -1){perror("write");exit(EXIT_FAILURE);} //writing the new line prompt message


		}

	}

	exit(EXIT_SUCCESS);
}



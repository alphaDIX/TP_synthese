/*
 * EX1.c
 *
 *  Created on: 27 nov. 2023
 *      Author: ensea
 */

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


#define welcome "$ ./enseash\nBienvenue dans le shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash %"
#define buffsize 128

int main(int argc, char * argv[]){

	char buffer[buffsize] = welcome;

	if(write(STDOUT_FILENO, buffer, buffsize) == -1){
		perror("write");
		exit(EXIT_FAILURE);
	}


}

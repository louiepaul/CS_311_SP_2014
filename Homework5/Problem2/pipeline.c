/*************************************
 * NAME: Ian Paul
 * EMAIL: pauli@onid.oregonstate.edu
 * CLASS: CS311-400
 * ASSIGNMENT: Homework 5
 * ***********************************/
 
 #include <sys/wait.h>
 #include "tlpi_hdr.h"
 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/types.h>
 
 
 int main (int argc, char *argv[])
{

//variables
char c;


int fFlag = 0;

char * fValue = NULL;

int pfd1[2];
int pfd2[2];
int pfd3[2];
int pfd4[2];


while((c = getopt(argc, argv, "f:")) != -1)
	switch(c)
		{
		case 'f':
			fFlag = 1;
			fValue = argv[2];
			break;
		case '?':
		  if (optopt == 'f')
		     fprintf(stderr, "Option -%c requires an argument.\n", optopt);
		  else
		     fprintf(stderr, "Unknown option character '\\x%x.\n",optopt);
		  return 1;
		default:
			abort();
		}


//check to make sure you have everything you need in place. Helpful when using tlpi_hdr.h
//printf("Hello Universe\n");

if(fFlag == 1){

if (pipe(pfd1) == -1)
	printf("1 Pipe error");
	
if (pipe(pfd2) == -1)
	printf("2 Pipe error");
	
if (pipe(pfd3) == -1)
	printf("3 Pipe error");
	
if (pipe(pfd4) == -1)
	printf("4 Pipe error");



	
//FORK 1
	switch(fork()){
	
	case -1:
	//this is the error case
	printf("Could not create child");
	//exit(-1);
	
	case 0:

		
		//close 1
		//closing read end of child
		if(close(pfd1[0]) == -1)
			printf("Error closing Pipe 1");
		//making sure that write end is standard out	
		if(pfd1[1] != STDOUT_FILENO){
			if(dup2(pfd1[1], STDOUT_FILENO) == -1)
				printf("error opening dup2 pfd1");
			
			//close 2
			//closing the write end of child
			if(close(pfd1[1]) == -1)
				printf("error opening dup2 pfd1");
		}
		
		//executing reverse function
		//writes to the pipe
		execlp("rev", "rev", (char *)NULL);
			
	default:

		break;
	}
//FORK 2	
		switch(fork()){
		
	case -1:
		//this is the error case
		printf("Could not create child");
		//exit(-1);
	
	case 0:

		//close 3
		if(close(pfd1[1]) == -1)
			printf("Error closing Pipe 1");
		//close 4	
		if(close(pfd2[0]) == -1)
			printf("Error closing Pipe 2");
			
		if(pfd1[0] != STDIN_FILENO){
			if(dup2(pfd1[0], STDIN_FILENO) == -1){
				printf("error opening dup2 pfd1");
			}	
			//close 5
			if(close(pfd1[0]) == -1){
				printf("error opening dup2 pfd1");
			}
		}
		
		if(pfd2[1] != STDOUT_FILENO){
			if(dup2(pfd2[1], STDOUT_FILENO) == -1){
				printf("error opening dup2 pfd2");
			}
			//close 6
			if(close(pfd2[1]) == -1){
				printf("error opening dup2 pfd2");
			}
		}		
		
		execlp("sort", "sort", (char *) NULL);
		


	
	default:

		break;
	}
//FORK 3	
		switch(fork()){


	case -1:
		//this is the error case
		printf("Could not create child");
		//exit(-1);
	
	
	case 0:
		//close 7
		if(close(pfd1[0]) == -1)
			printf("Error closing Pipe 1");
		//close 8
		if(close(pfd1[1]) == -1)
			printf("Error closing Pipe 1");
		//close 9	
		if(close(pfd2[1]) == -1)
			printf("Error closing Pipe 2");
		//close 10	
		if(close(pfd3[0]) == -1)
			printf("Error closing Pipe 3");
			
			
			
			
		if(pfd2[0] != STDIN_FILENO){
			if(dup2(pfd2[0], STDIN_FILENO) == -1){
				printf("error opening dup2 pfd2");
			}
			//close 11
			if(close(pfd2[0]) == -1){
				printf("error opening dup2 pfd2");
			}
		}
		
		if(pfd3[1] != STDOUT_FILENO){
			if(dup2(pfd3[1], STDOUT_FILENO) == -1){
				printf("error opening dup2 pfd2");
			}
			//close 12
			if(close(pfd3[1]) == -1){
				printf("error opening dup2 pfd2");
			}
		}		
		
		execlp("uniq", "uniq", "-c", (char *) NULL);
		

	default:

		break;
	}
	
//FORK 4
		switch(fork()){
	
	case -1:
		//this is the error case
	printf("Could not create child");
		//exit(-1);
	
	case 0:
		
		//close 13
		if(close(pfd1[1]) == -1)
			printf("Error closing Pipe 1");
		//close 14
		if(close(pfd1[0]) == -1)
			printf("Error closing Pipe 1");
			
		//close 15	
		if(close(pfd2[1]) == -1)
			printf("Error closing Pipe 2");
		//close 16
		if(close(pfd2[0]) == -1)
			printf("Error closing Pipe 2");
			
		//close 17	
		if(close(pfd3[1]) == -1)
			printf("Error closing Pipe 3");
		
		//close 18
		if(close(pfd4[0]) == -1)
			printf("Error closing Pipe 4");		
			

			
			
		//making the in and out be from and too the correct pipes/processes		
		if(pfd3[0] != STDIN_FILENO){
			if(dup2(pfd3[0], STDIN_FILENO) == -1){
				printf("error opening dup2 pfd3");
			}
			//close 19
			if(close(pfd3[0]) == -1){
				printf("error opening dup2 pfd3");
			}
		}
		
		//making the in and out be from and too the correct pipes/processes	
		if(pfd4[1] != STDOUT_FILENO){
			if(dup2(pfd4[1], STDOUT_FILENO) == -1){
				printf("error opening dup2 pfd4");
			}
			//close 20
			if(close(pfd4[1]) == -1){
				printf("error opening dup2 pfd4");
			}
		}		
		
		execlp("tee", "tee", fValue, (char *) NULL);
		


	
	default:

		break;
	}
	
	
	
//FORK 5
		switch(fork()){
		
	case -1:
		//this is the error case
		printf("Could not create child");
		//exit(-1);
	
	case 0:

		//execlp("ls", "ls", (char *)NULL);
		//close 21
		if(close(pfd1[0]) == -1)
			printf("Error closing Pipe 1");
		//close 22
		if(close(pfd1[1]) == -1)
			printf("Error closing Pipe 1");
			
		//close 23
		if(close(pfd2[0]) == -1)
			printf("Error closing Pipe 2");
		//close 24
		if(close(pfd2[1]) == -1)
			printf("Error closing Pipe 2");
			
		//close 25
		if(close(pfd3[0]) == -1)
			printf("Error closing Pipe 3");
		//close 26
		if(close(pfd3[1]) == -1)
			printf("Error closing Pipe 3");
		
		//close 27
		if(close(pfd4[1]) == -1)
			printf("Error closing Pipe 4");		
			

			
			
		//making the in and out be from and too the correct pipes/processes	
		if(pfd4[0] != STDIN_FILENO){
			if(dup2(pfd4[0], STDIN_FILENO) == -1){
				printf("error closing dup2 pfd4");
			}
			//close 28
			if(close(pfd4[0]) == -1){
				printf("error closing dup2 pfd4");
			}
		}
		
	
		
		execlp("wc", "wc", (char *) NULL);
		


	
	default:
		break;
	}
	//uber close
	//close 29
	if(close(pfd1[0]) == -1)
		printf("Error closing pipe 1");
	//close 30
	if(close(pfd1[1]) == -1)
		printf("Error closing pipe 1");
	
	//close 31
	if(close(pfd2[0]) == -1)
		printf("Error closing pipe 2");
	//close 32
	if(close(pfd2[1]) == -1)
		printf("Error closing pipe 2");

	//close 33
	if(close(pfd3[0]) == -1)
		printf("Error closing pipe 3");
	//close 34
	if(close(pfd3[1]) == -1)
		printf("Error closing pipe 3");
		
	if(close(pfd4[0]) == -1)
		printf("Error closing pipe 4");
	if(close(pfd4[1]) == -1)
		printf("Error closing pipe 4");

		
		
	//all the waits	
	if(wait(NULL) == -1)
		printf("wait 1");
	if(wait(NULL) == -1)
		printf("wait 2");
	if(wait(NULL) == -1)
		printf("wait 3");
	if(wait(NULL) == -1)
		printf("wait 4");


		
}
	return 0;
}
	

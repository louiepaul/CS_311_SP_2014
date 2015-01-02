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



	//pid_t p;
	
//FORK 1
	switch(fork()){
	
	case -1:
	//this is the error case
	printf("Could not create child");
	//exit(-1);
	
	case 0:
		//this is the child case
		//printf("I am the child. Process ID is %d. Parent ID is: %d\n", getpid(), getppid());
		
		//execlp("ls", "ls", (char *)NULL);
		
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
		//this is the parent case
		//printf("I am the parent. Process ID is %d\n", getpid());

		break;
	}
//FORK 2	
		switch(fork()){
		
	case -1:
		//this is the error case
		printf("Could not create child");
		//exit(-1);
	
	case 0:
		//this is the child case
		//printf("I am the child. Process ID is %d. Parent ID is: %d\n", getpid(), getppid());
		
		//execlp("ls", "ls", (char *)NULL);
		
		if(close(pfd1[1]) == -1)
			printf("Error closing Pipe 1");
			
		if(close(pfd2[0]) == -1)
			printf("Error closing Pipe 2");
			
		if(pfd1[0] != STDIN_FILENO){
			if(dup2(pfd1[0], STDIN_FILENO) == -1){
				printf("error opening dup2 pfd1");
			}	
			if(close(pfd1[0]) == -1){
				printf("error opening dup2 pfd1");
			}
		}
		
		if(pfd2[1] != STDOUT_FILENO){
			if(dup2(pfd2[1], STDOUT_FILENO) == -1){
				printf("error opening dup2 pfd2");
			}
			if(close(pfd2[1]) == -1){
				printf("error opening dup2 pfd2");
			}
		}		
		
		execlp("sort", "sort", (char *) NULL);
		


	
	default:
		//this is the parent case
		//printf("I am the parent. Process ID is %d\n", getpid());

		break;
	}
//FORK 3	
		switch(fork()){


	case -1:
		//this is the error case
		printf("Could not create child");
		//exit(-1);
	
	
	case 0:
		//this is the child case
		//printf("I am the child. Process ID is %d. Parent ID is: %d\n", getpid(), getppid());
		
		//execlp("ls", "ls", (char *)NULL);
		
		if(close(pfd1[0]) == -1)
			printf("Error closing Pipe 1");
		if(close(pfd1[1]) == -1)
			printf("Error closing Pipe 1");
			
		if(close(pfd2[1]) == -1)
			printf("Error closing Pipe 2");
			
		if(close(pfd3[0]) == -1)
			printf("Error closing Pipe 3");
			
			
			
			
		if(pfd2[0] != STDIN_FILENO){
			if(dup2(pfd2[0], STDIN_FILENO) == -1){
				printf("error opening dup2 pfd2");
			}
			if(close(pfd2[0]) == -1){
				printf("error opening dup2 pfd2");
			}
		}
		
		if(pfd3[1] != STDOUT_FILENO){
			if(dup2(pfd3[1], STDOUT_FILENO) == -1){
				printf("error opening dup2 pfd2");
			}
			if(close(pfd3[1]) == -1){
				printf("error opening dup2 pfd2");
			}
		}		
		
		execlp("uniq", "uniq", "-c", (char *) NULL);
		

	default:
		//this is the parent case
		//printf("I am the parent. Process ID is %d\n", getpid());

		break;
	}
	
//FORK 4
		switch(fork()){
	
	case -1:
		//this is the error case
	printf("Could not create child");
		//exit(-1);
	
	case 0:
		//this is the child case
		//printf("I am the child. Process ID is %d. Parent ID is: %d\n", getpid(), getppid());
		
		//execlp("ls", "ls", (char *)NULL);
		
		if(close(pfd1[1]) == -1)
			printf("Error closing Pipe 1");
		if(close(pfd1[0]) == -1)
			printf("Error closing Pipe 1");
			
		if(close(pfd2[1]) == -1)
			printf("Error closing Pipe 2");
		if(close(pfd2[0]) == -1)
			printf("Error closing Pipe 2");
			
		if(close(pfd3[1]) == -1)
			printf("Error closing Pipe 3");
		
		if(close(pfd4[0]) == -1)
			printf("Error closing Pipe 3");		
			

			
			
			
		if(pfd3[0] != STDIN_FILENO){
			if(dup2(pfd3[0], STDIN_FILENO) == -1){
				printf("error opening dup2 pfd2");
			}
			if(close(pfd3[0]) == -1){
				printf("error opening dup2 pfd2");
			}
		}
		
		if(pfd4[1] != STDOUT_FILENO){
			if(dup2(pfd4[1], STDOUT_FILENO) == -1){
				printf("error opening dup2 pfd3");
			}
			if(close(pfd4[1]) == -1){
				printf("error opening dup2 pfd3");
			}
		}		
		
		execlp("tee", "tee", fValue, (char *) NULL);
		


	
	default:
		//this is the parent case
		//printf("I am the parent. Process ID is %d\n", getpid());

		break;
	}
	
	
	
//FORK 5
		switch(fork()){
		
	case -1:
		//this is the error case
		printf("Could not create child");
		exit(-1);
	
	case 0:
		//this is the child case
		//printf("I am the child. Process ID is %d. Parent ID is: %d\n", getpid(), getppid());
		
		//execlp("ls", "ls", (char *)NULL);
		
		if(close(pfd1[0]) == -1)
			printf("Error closing Pipe 1");
		if(close(pfd1[1]) == -1)
			printf("Error closing Pipe 1");
			
		if(close(pfd2[0]) == -1)
			printf("Error closing Pipe 2");
		if(close(pfd2[1]) == -1)
			printf("Error closing Pipe 2");
			
		if(close(pfd3[0]) == -1)
			printf("Error closing Pipe 3");
		if(close(pfd3[1]) == -1)
			printf("Error closing Pipe 3");
		
		if(close(pfd4[1]) == -1)
			printf("Error closing Pipe 3");		
			

			
			
			
		if(pfd4[0] != STDIN_FILENO){
			if(dup2(pfd4[0], STDIN_FILENO) == -1){
				printf("error closing dup2 pfd4");
			}
			if(close(pfd4[0]) == -1){
				printf("error closing dup2 pfd4");
			}
		}
		
	
		
		execlp("wc", "wc", (char *) NULL);
		


	
	default:
		//this is the parent case
		//printf("I am the parent. Process ID is %d\n", getpid());

		break;
	}
	
	if(close(pfd1[0]) == -1)
		printf("close 5");
	if(close(pfd1[1]) == -1)
		printf("close 6");
	
	if(close(pfd2[0]) == -1)
		printf("close 5");
	if(close(pfd2[1]) == -1)
		printf("close 6");

	if(close(pfd3[0]) == -1)
		printf("close 5");
	if(close(pfd3[1]) == -1)
		printf("close 6");
		
	if(close(pfd4[0]) == -1)
		printf("close 5");
	if(close(pfd4[1]) == -1)
		printf("close 6");

		
		
		
	if(wait(NULL) == -1)
		printf("wait 1");
	if(wait(NULL) == -1)
		printf("wait 2");
	if(wait(NULL) == -1)
		printf("wait 3");
	if(wait(NULL) == -1)
		printf("wait 4");




//	exit(1);
		
}




/*
	int pfd[2];
	
	if (pipe(pfd) == -1)
		//errExit("pipe");
		printf("pipe");
	switch (fork()){
	case -1:
		printf("fork");

	case 0:
		if (close(pfd[0]) == -1)
			printf("close 1");
		if (pfd[1] != STDOUT_FILENO){
			if (dup2(pfd[1], STDOUT_FILENO) == -1)
				printf("dup2 1");
			if (close(pfd[1]) == -1)
				printf("close 2");
		}
		
		execlp("ls", "ls", (char *) NULL);	//writes to pipe
		printf("execlp ls");
		
	default:
		break;
	}
	
	switch (fork()){
	case -1:
		printf("fork");
		
	case 0:
		if (close(pfd[1]) == -1)
			printf("close 3");

		if (pfd[0] != STDIN_FILENO){
			if(dup2(pfd[0], STDIN_FILENO) == -1)
				printf("dup2 2");
			if (close(pfd[0]) == -1)
				printf("close 4");
		}
		
		execlp("wc", "wc", "-l", (char *) NULL);
		printf("execlp wp");
		
	default:
		break;
	}
	
	if(close(pfd[0]) == -1)
		printf("close 5");
	if(close(pfd[1]) == -1)
		printf("close 6");
	if(wait(NULL) == -1)
		printf("wait 1");
	if (wait(NULL) == -1)
		printf("wait 2");
		
	//exit(EXIT_SUCCESS);
*/	
	return 0;
	}
	

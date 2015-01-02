/****************************************
 * NAME: Ian Paul
 * EMAIL: pauli@onid.oregonstate.edu
 * CLASS: CS311-400
 * ASSIGNMENT: Homework 4
 * *************************************/


//Standard header from book for most programs
#ifndef TLPI_HDR_H
#define TLPI_HDR_H  //Prevent accidental double inclusion

#include <sys/types.h>  //Type definitions
#include <stdio.h>      //standard I/O functions
#include <stdlib.h>     //prototypes of commonly sed library functions,
			//plus EXIT_SUCCESS and EXIT_FAILURE constants
#include <unistd.h>	//prototypes fro many system calls
#include <errno.h>	//Declares errn and defines error constants
#include <string.h>	//commonly used string-handling functions

//#include "get_num.h"	//Declares our functions for handling numeric arguments
			//(getInt(), getLong())

//#include "error_function.h"  //Declares our error-handling functions

typedef enum {FALSE, TRUE} Boolean;

#define min(m,n) ((m)<(n)?(m):(n))
#define max(m,n) ((m)>(n)?(m):(n))

#endif
//End of standard headers

//Headers for this part of this assignment
#include <signal.h>
#include <getopt.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>



static void
siguser1Handler(int sig)
{
printf("SIGUSR1 has been caught\n");
}

static void
siguser2Handler(int sig)
{
printf("SIGUSR2 has been caught\n");
}

static void
sigintHandler(int sig)
{
printf("SIGINT has been caught, terminating the program\n");
exit(1);
}


int main (int argc, char *argv[])
{

	signal(SIGUSR1, siguser1Handler);

	signal(SIGUSR2, siguser2Handler);

	signal(SIGINT, sigintHandler);

	kill(getpid(), 10);

	kill(getpid(), 12);

	kill(getpid(), 2);

return 0;
}



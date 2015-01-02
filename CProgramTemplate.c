/****************************************
 * NAME: Ian Paul
 * EMAIL: pauli@onid.oregonstate.edu
 * CLASS: CS311-400
 * HOMEWORK: (Write Homework Number Here)
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

#include "get_num.h"	//Declares our functions for handling numeric arguments
			//(getInt(), getLong())

#include "error_function.h"  //Declares our error-handling functions

typedef enum {FALSE, TRUE} Boolean;

#define min(m,n) ((m)<(n)?(m):(n))
#define max(m,n) ((m)>(n)?(m):(n))

#endif
//End of standard header

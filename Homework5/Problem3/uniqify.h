/****************************************
*NAME: Ian Paul
*EMAIL: pauli@onid.oregonstate.edu
*CLASS: CS311-400
*ASSIGNMENT: Homework 5
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>
#include "tlpi_hdr.h"
#include <sys/wait.h>
#include <time.h>
#include <errno.h>
#include <getopt.h>
#include<math.h>

#ifndef DYNAMIC_ARRAY_INCLUDED
#define DYNAMIC_ARRAY_INCLUDED 1


# ifndef TYPE
# define TYPE     double 
# define TYPE_SIZE sizeof(double)
# endif

# ifndef EQ
# define EQ(A, B) (fabs(A - B) < 10e-7)
# endif



typedef struct DynArr DynArr;

/* Dynamic Array Functions */
/*
DynArr *createDynArr(int cap);
void deleteDynArr(DynArr *v);

int sizeDynArr(DynArr *v);

void addDynArr(DynArr *v, char *val);
TYPE getDynArr(DynArr *v, int pos);
void putDynArr(DynArr *v, int pos, TYPE val);
void swapDynArr(DynArr *v, int i, int  j);
void removeAtDynArr(DynArr *v, int idx);
*/


//from lectures
//# define QUEUE_PERMS 0644
# define QUEUE_PERMS 0666


//#include "uniqify.h"
//#include "tlpi_hdr.h"

# endif
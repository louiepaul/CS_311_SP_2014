
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


#include <ctype.h>

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

#include <stdio.h>
#include <getopt.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <ar.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <string.h>
#include <utime.h>
#include <time.h>
#include <dirent.h>

#include <assert.h>
#include <stdlib.h>

#include "uniqify.h"
#include "tlpi_hdr.h"
#define ORPHANAGE 50 /* The maximum number of pipes */


#define WORD_SIZE_MAX 50
#define CAP_CHANGER 32
#define BUFFERSIZE 1


//declairing functions
int alphaMoon(char *charToCheck);

void wordLauncher();
static int cmpstringp(const void *p1, const void *p2);
void galactica();

//functions for dynamic arrays from CS261
void removeAtDynArr(DynArr *v, int idx);
void swapDynArr(DynArr *v, int i, int  j);
void putDynArr(DynArr *v, int pos, TYPE val);
TYPE getDynArr(DynArr *v, int pos);
void addDynArr(DynArr *v, char *val);
int sizeDynArr(DynArr *v);
void _dynArrSetCapacity(DynArr *v, int newCap);
void deleteDynArr(DynArr *v);
void freeDynArr(DynArr *v);
DynArr* createDynArr(int cap);
void initDynArr(DynArr *v, int capacity);
void _initDynArr(struct DynArr *v, int capacity);

void intr_sig(int mySignal);

void childBirth(int numProc, int msqid, int *childProcQueArray);


//declaring the message

typedef struct message {
    long mtype;
    char *mtext[50];
} mess_t;



//declairing dynamic array (from CS261)
struct DynArr
{
	char **data;		// pointer to the data array 
	int size;		// Number of elements in the array 
	int capacity;	// capacity ofthe array 
};


struct DynArr* createDynArr(int cap)
{
	struct DynArr *r;
	assert(cap > 0);
	r = (struct DynArr *)malloc(sizeof( struct DynArr));
	assert(r != 0);
	_initDynArr(r,cap);
	return r;
}




 int main (int argc, char *argv[])
{

static int msqid;
//mess_t msgSend

mess_t sndbuf;
//mess_t recbuf;


DynArr *motherShip;
motherShip = createDynArr(1);


//variables
char c;
int nFlag = 0;
static int numProc = 1;

while((c = getopt(argc, argv, "n")) != -1)
	switch(c)
		{
		case 'n':
			nFlag = 1;
			if (argc == 2){
			numProc = 1;
			}
			else{
			numProc = atoi(argv[2]);
				if(numProc > ORPHANAGE)//can't handle too many children
					{
						printf("Too many processes requested! Exiting...\n");
						exit(1);
					}
			}
			break;
		default:
			abort();
		}


if(nFlag == 1){

key_t key;

if ((key = ftok(__FILE__, 's')) == -1) 
{
	perror("ftok");
	exit(1);
}

/*
//create unique message queues for each sub sort process 
    numProc = 1;
	int childProcQueArray[numProc];    
    int i = 0;
    for (i ; i < numProc; i++)
    {
    //create message queue for each process :
        childProcQueArray[i] = msgget((key + i + 1), QUEUE_PERMS | IPC_CREAT);//mssget returns message queue identifier on success, -1 on error 
    //connect to an existing message queue 
        if((childProcQueArray[i] = msgget(key + i + 1, QUEUE_PERMS)) == -1)
        {
            printf("Error calling message.\n");
        }
    }
*/


	//char wordBuf[2000];
	int i = 0;
	//int j = 0;
	int sizeOfFile;
	sizeOfFile = sizeof(STDIN_FILENO);
	char buf[1];

	char finalWord[50];
	//char spacer[1] = " ";
	int numRead;
	//int checker;
	int z = 0;
	
//getting the queue id
if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) 
	{
	perror("msgget");
	exit(1);
	}	

	
	
	
mess_t recieveQueue;
//creating child process
switch(fork()){

	case -1:
		printf("Error with child\n");
		
	case 0:
		sleep(1);
		
		while(msgrcv(msqid, &recieveQueue, sizeof(recieveQueue.mtext), 0, IPC_NOWAIT | MSG_NOERROR) != -1)
		{
		
			int tempWordL = strlen(recieveQueue.mtext) + 1;
			char * tempWord = malloc(tempWordL);
			
			strcpy(tempWord, recieveQueue.mtext);
			addDynArr(motherShip, tempWord);
			

			}
		
		sleep(5);//gives the processes time to work
			qsort(motherShip->data, motherShip->size, sizeof(char *), cmpstringp);
			int tempNumCount =1;
			//int tempWordLen;

			for (i = 0; i < motherShip->size; i++)
			{
				for (i = 0; i < motherShip->size -1; i++)
				{		
					if((strcmp(motherShip->data[i], motherShip->data[i+1])) == 0)
					{
						tempNumCount++;
					}
					else 
					{
						if(strlen(motherShip->data[i]) != 0)
						{
							printf("\t%d\t%s\n", tempNumCount, motherShip->data[i]);
							tempNumCount = 1;
						}
					}
				}
				printf("\t%d\t%s\n", tempNumCount, motherShip->data[i]);
	
			}		

		_exit(EXIT_SUCCESS);
	default:
		break;
		
}	
	
	
	
	
//reads from text file, chops words up, makes them lower case, sends them to queue	
do{
	numRead = read(STDIN_FILENO, buf, sizeof(buf));
	
		if(numRead == 0 || alphaMoon(&buf[0])==0)
		{
			if(i>0)
			{
						
				sndbuf.mtype = 1;

				wordLauncher(finalWord, msqid, sndbuf);


				z++;
				
				
				i = 0;
				int x = 0;
				for(x; x < sizeof(finalWord); x++)
				{
					finalWord[x] = 0;
				}
					x = 0;
			}
		}
		else
		{
			int y = 0; 
			for (y; y < 1; y++)
			{
				finalWord[i] = buf[0];
				finalWord[i+1] = '\0';
				i++;
			}
		}
	} while(numRead > 0);
	
	sndbuf.mtext[0] = '\0';
    sndbuf.mtype = 1;
    msgsnd(msqid, &sndbuf, 1, 0);
 
		
wait(NULL);

	
int orphans;

for(orphans = 0; orphans<numProc; orphans++)
{
	wait(NULL);
}
	
	
	/*
	THIS IS JUST TESTING QSORT
	//galactica();
	// qsort (stringarray,numStrings,sizeof(char *),
      //              (int (*)(const void *, const void *)) cmp);
      

 //qsort (motherShip,sizeOFM,sizeof(char *),
   //                 (int (*)(const void *, const void *)) cmpstringp);
                    
	  
	//qsort(&argv[1], argc - 1, sizeof(char *), cmpstringp);
	char * fatherShip[] = {"louie", "emma", "becca", "rc", "raleigh"};
	
	qsort(fatherShip, 5, sizeof(char *), cmpstringp);
	
	for (i = 0; i < 5; i++)
	{
		printf("%s ",fatherShip[i]);
	}
	*/
	
}

    if (msgctl(msqid, IPC_RMID, NULL) == -1) 
	{
        perror("msgctl");
        exit(1);
    }
return 0;
}

/*
//helps sort against cylons
void galactica(){

	qsort(motherShip, 10, sizeof(char *), cmpstringp);

	
	printf("nooooooooo");
}
*/

//sends words to queues
void wordLauncher(char *word, int msqid, mess_t sndbuf)
{

memcpy(sndbuf.mtext, word, WORD_SIZE_MAX);
	
	if(msgsnd(msqid, &sndbuf, strlen(sndbuf.mtext) +1, 0) == -1)
	{
		printf("error sending\n");
	}

}


//checks for deliminator, makes caps to lower case
int alphaMoon(char *charToCheck){
	if ((*charToCheck <= 'Z') && (*charToCheck >= 'A'))
		{
			*charToCheck = (*charToCheck) + 32;
			return 1;
		}
	else if((*charToCheck <= 'z') && (*charToCheck >= 'a'))
		{
			return 1;
		}
	else
		{
		return 0;
		}
}


//straight from man page
static int cmpstringp(const void *p1, const void *p2)
       {
           /* The actual arguments to this function are "pointers to
              pointers to char", but strcmp(3) arguments are "pointers
              to char", hence the following cast plus dereference */

           return strcmp(* (char * const *) p1, * (char * const *) p2);
       }
/*   
//from http://eecs.wsu.edu/~sshaikot/docs/Other/qsort_example_code.pdf
static int struct_cmp_by_product(const void *a, const void *b)
{
	struct st_ex *ia = (struct st_ex *)a;
	struct st_ex *ib = (struct st_ex *)b;
	return strcmp(ia-product, ib-product);
}
*/	   

/* ************************************************************************
	Dynamic Array Functions (from CS261)
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/

void _initDynArr(struct DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = malloc(sizeof(char)*WORD_SIZE_MAX*capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;

}
/*
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (char *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;	
}
*/
/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.		
*/

/*
DynArr* createDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}
*/
/* Deallocate data array in dynamic array. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap 

	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/

void _dynArrSetCapacity(struct DynArr *v, int newCap)
{	
	/* FIXME: You will write this function */
	
	TYPE *newData = malloc(newCap *sizeof (char));

	int i;
	char **oldData;
	int oldSize = v->size;
	oldData = v->data;
	
	_initDynArr(v,newCap);
	
	for (i=0; i< oldSize; i++)
	{
		v->data[i] = oldData[i];
	}
	
	v->size = oldSize;
	
	/*
	free(v->data);
	v->data=newData;
	v->capacity=newCap;
	*/
}

/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArr(struct DynArr *v, char *val)
{
	/* FIXME: You will write this function */

	char *word = malloc(WORD_SIZE_MAX);
	strncpy(word, val, WORD_SIZE_MAX);
	
	assert(v !=0);//testing the precondition "the dynArray is not null"

	if(v->size>=v->capacity)
		_dynArrSetCapacity(v, 2 *v->capacity);

		
		v->data[v->size] = word;
		v->size++;

}

/*	Get an element from the dynamic array from a specified position
	
	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/

/*

TYPE getDynArr(DynArr *v, int pos)
{
	// FIXME: You will write this function 
	assert(v !=0);
	assert(v->size>0);
	assert(pos<v->size && pos>=0);

	if(pos<=v->size)

	 FIXME: you must change this return value 
	return v->data[pos];
}

*/

/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there

	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert 
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/

/*
void putDynArr(DynArr *v, int pos, TYPE val)
{
	 FIXME: You will write this function 
	assert(v !=0);
	assert(v->size>0);
	assert(pos>=0 && pos< v->size);
	if(v->size>=v->capacity)
	{
		_dynArrSetCapacity(v, 2* v->capacity);
	}

		v->data[pos]=val;
}
*/
/*	Swap two specified elements in the dynamic array

	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
*/

/*
void swapDynArr(DynArr *v, int i, int  j)
{
	// FIXME: You will write this function 
	assert(v !=0);
	assert(v->size>0);
	assert(i>=0 && j>=0 && i<v->size && j<v->size);

	TYPE temp;
	temp = v->data[i];
	v->data[i]=v->data[j];
	v->data[j]=temp;

}
*/

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{
	/* FIXME: You will write this function */
	assert(v !=0);
	assert(v->size>0);
	assert(idx < v->size && idx >= 0);

	int i = idx;
	for (i=idx; i<v->size;i++)
	{
		v->data[i]=v->data[i+1];
	}
	v->size--;
}
/* ************************************************************************
	END Dynamic Array Functions (from CS261)
************************************************************************ */
void intr_sig(int mySignal){

	psignal(mySignal, "Caught it!");
	printf("Caught mySignal %d: %s\n", mySignal, sys_siglist[mySignal]); //bad idea to use printf here.
	
	if(mySignal == SIGINT){
		//removeQueue();
		exit(EXIT_SUCCESS);
	}
	
	
	return;
}

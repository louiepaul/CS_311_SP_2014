/****************************************
 *NAME: Ian Paul
 *EMAIL: pauli@onid.oregonstate.edu
 *CLASS: CS311-400
 *ASSIGNMENT: Homework 6
 ****************************************/

#include <stdio.h>//
#include <stdlib.h>//
#include <errno.h>//
#include <string.h>
#include <unistd.h>//
#include <signal.h>
//#include <time.h>//
#include <getopt.h>//
#include <math.h>//
#include <fcntl.h>
#include <ar.h>
#include <ctype.h>
#include <dirent.h>
#include <time.h>
#include <utime.h>
#include <pthread.h>
#include <limits.h>
#include <semaphore.h>
#include <libgen.h>

#include <sys/utsname.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>



#include "primeMProc.h"

//global variables
unsigned int curPrime;
unsigned int divideBy;
unsigned int *bitMap;
void *addr;
int shmem_fd;
unsigned int *nextPrimeNum;
unsigned int maxPrime;
unsigned int subProcNum;
sem_t *semaphore;




#define MAXPROCS 20



//functions declarations
void isPrime(unsigned int array[], unsigned int k);
void isNotPrime(unsigned int array[], unsigned int k);
int checkIfPrime(unsigned int array[], unsigned int k);
void *makeNotPrime(unsigned int *bitMap);
void *mount_shmem(char *path, int object_size);

struct data
{
    unsigned int current_prime;
};

int main(int argc, char *argv[])
{
    unsigned long i;
    unsigned int mult;
    int j;
    
    unsigned int bitMapSize;
    pid_t pid;
    
    char c;
    optarg = NULL;
    subProcNum = 1;
    maxPrime = UINT_MAX; // largest unsigned int which is 4294967295
    int qFlag = 0;
    int mFlag = 0;
    int cFlag = 0;
    //unsigned long i;
    
    //variables for timing
    time_t startTime;
    time_t endTime;
    double totalTime = 0;
    double startTimer;
    double endTimer;
    
    
    
    //get command line arguments
    while((c = getopt(argc, argv, "qm:c:")) !=-1)
    {
        switch(c)
        {
            case 'q':
                qFlag = 1;
                break;
                
            case 'm':
                mFlag = 1;
                maxPrime = atoi(optarg);
                if(maxPrime > UINT_MAX)
                {
                    printf("The max prime cannot be greater than %u, select a smaller number\n", UINT_MAX);
                }
                break;
                
            case 'c':
                cFlag = 1;
                subProcNum = atoi(optarg);
                if(subProcNum > MAXPROCS)
                {
                    printf("There must be less than %d threads, select a smaller number\n", MAXPROCS);
                    exit(-1);
                }
                break;
                
            default:
                printf("Error: commands not understood. Exiting\n");
                exit(-1);
        }
    }
    
    
    if(qFlag == 1)
    {
       // printf("Selected q\n");
        startTimer = time(&startTime);
    }
    
    
    //Creating shared mem
    unsigned int size = ((maxPrime/32));
    bitMapSize = size * sizeof(unsigned int);
    bitMapSize = bitMapSize + sizeof(unsigned int);
    
    void *addr = mount_shmem("/IPprimeMProcIP", bitMapSize);
   // printf("made it past first mount\n");
    bitMap = (unsigned int*)addr;
    
    void *addr2 = mount_shmem("/IPprimeMProc2IP", sizeof(int));
    nextPrimeNum = (int *)addr2;
    
    semaphore = sem_open("/IPmy_own_semaphore", O_CREAT, S_IRUSR | S_IWUSR, 1);
    if(!semaphore)
    {
        printf("Error creating/initializing semaphore");
        exit(-1);
    }
    
    
    //make the whole bitmap 1s
    for(i = 0; i<maxPrime; i++)
    {
        isPrime(bitMap, i);
    }
    
    
    //set 0 and 1 as not prime, just to make sure
    isNotPrime(bitMap, 0);
    isNotPrime(bitMap, 1);
    
    
    //mark all multiples of 2 as not prime
    mult = 2;
    divideBy = floor(maxPrime / mult);
    
    for(i = 1; i <= divideBy; i++)
    {
        if((i*mult) != mult)
        {
            isNotPrime(bitMap, (i*mult));
        }
    }
    
    
    *nextPrimeNum = 3;
    
    
    //create processes
    for(i = 0; i < subProcNum; i++)
    {
        switch(pid = fork())
        {
            case -1:
                printf("Error creating child process\n");
                exit(-1);
                break;
            case 0:
                makeNotPrime(bitMap);
                j = munmap(addr, bitMapSize);
                if(j != 0)
                {
                    printf("Error unmapping child processes\n");
                    exit(-1);
                }
                j - munmap(addr2, sizeof(int));
                if(j != 0)
                {
                    printf("Error unmapping child process\n");
                    exit(-1);
                }
                _exit(1);
                break;
            default:
                break;
        }
    }
    
    if(close(shmem_fd == -1))
    {
        printf("Error closing fd\n)");
        exit(-1);
    }
    
    /*
    int shotgun; //best zombie killing weapon
    for(shotgun = 0; shotgun < subProcNum; shotgun++)
    {
        wait(NULL);
    }
     */
    
    if(qFlag == 1)
    {
        //printf("Selected q\n");
        endTimer = time(&endTime);
        totalTime = (endTime - startTime);
        printf("Total time to complete: %.f seconds\n", totalTime);
    }
    
    
    if(qFlag == 0)
    {
        for(i=0; i < (maxPrime - 2); i++)
        {
            if(checkIfPrime(bitMap, i) == 1)
            {
                if(checkIfPrime(bitMap, i+2) == 1)
                {
                    printf("%lu %lu\n", i, i+2);
                }
            }
        }
    }
    
    
    /*
     if(mFlag == 1)
     {
     printf("selected m\n");
     printf("Max Prime is: %d\n", maxPrime);
     
     }
     
     if(cFlag == 1)
     {
     printf("selected c\n");
     printf("Number of threads is: %d\n", threadNum);
     }
     printf("Hello world\n");
     printf("Attempt with Xcode\n");
     */
    
    return 0;
    
}

//functions
void isPrime(unsigned int array[], unsigned int k)
{
    unsigned int i = k/32;
    unsigned int pos = k%32;
    unsigned int flag = 1;
    flag = flag << pos;
    array[i] = array[i] | flag;
}

void isNotPrime(unsigned int array[], unsigned int k)
{
    unsigned int i = k/32;
    unsigned int pos = k%32;
    unsigned int flag = 1;
    flag = flag << pos;
    flag = ~flag;
    array[i] = array[i] & flag;
}


int checkIfPrime(unsigned int array[], unsigned int k)
{
    unsigned int i = k/32;
    unsigned int pos = k%32;
    unsigned int flag = 1;
    flag = flag << pos;
    if (array[i] & flag)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//from lecture
void *mount_shmem(char *path, int object_size)
{
	shmem_fd = shm_open(path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); 
	if(shmem_fd == -1)
	{
		printf("Failed to open shared memory\n");
		exit(-1);
	}
    
	if(ftruncate(shmem_fd, object_size) == -1) 
	{
		printf("Failed to resize shared memory\n");
		exit(-1);
	}
    
	addr = mmap(NULL, object_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
    
	if(addr == MAP_FAILED)
	{
		printf("Failed to map shared memory\n");
		exit(-1);
	}
    
	return addr;
}


void *makeNotPrime(unsigned int *bitMap)
{
    unsigned int currentPos;
    unsigned int maxPos;
    divideBy = sqrt(maxPrime);
    
    while (*nextPrimeNum <= divideBy)
    {
        
        sem_wait(semaphore);
        currentPos = *nextPrimeNum;
        
        do
        {
            *nextPrimeNum = *nextPrimeNum + 2;
        }while(checkIfPrime(bitMap, *nextPrimeNum) != 1);
        sem_post(semaphore);
        
        maxPos = floor(maxPrime / currentPos);
        unsigned int j;
        
        for(j = 2; j <= maxPrime; j++)
        {
            isNotPrime(bitMap, (j*currentPos));
        }
    }
    return NULL;
}
/****************************************
 *NAME: Ian Paul
 *EMAIL: pauli@onid.oregonstate.edu
 *CLASS: CS311-400
 *ASSIGNMENT: Homework 6
 ****************************************/
#include "primeMProc.h"


#define MAXTHREADS 20


//global variables
pthread_mutex_t mutex;
unsigned int maxPrime;
unsigned int *bitArray;
unsigned int numberOfThreads;
unsigned int nextPrime;
unsigned int deivideBy;


//declare functions
void isAPrime(unsigned int A[ ], unsigned int k);
void isNotAPrime(unsigned int A[ ], unsigned int k);
int checkIfPrime(unsigned int A[ ], unsigned int k);
void *makeNotPrime(void *threadPointer);

int main(int argc, char *argv[])
{
	char c;
	optarg = NULL;
	numberOfThreads = 1;
	maxPrime = UINT_MAX; //this is the max unsigned int, 4294967295
	int qflag = 0;
	unsigned long i;
    
    //time variables
	time_t start;
	time_t end;
	double totalTime = 0;
	double startTime;
	double endTime;
    
    while((c = getopt(argc, argv, "qm:c:"))!= -1)
	{
		switch(c)
		{
			case 'q':
				qflag = 1;
				break;
			case 'm':
				maxPrime = atoi(optarg);
				if(maxPrime > UINT_MAX)
				{
					printf("Largest prime cannot be greater than: %u \n", UINT_MAX);
				}
				break;
			case 'c':
				numberOfThreads = atoi(optarg);
				if(numberOfThreads > MAXTHREADS)
				{
					printf("Number of threads must be less than: %d\n", MAXTHREADS);
					exit(-1);
				}
				break;
			default:
				printf("Unknown command\n");
				exit(-1);
                
		}
	}
	
//only used for timing
    if(qflag == 1)
    {
        startTime = time(&start);
    }
    
//we know that you don't have to check beyond the square root of the prime, based on greek guys math
	deivideBy = sqrt(maxPrime);
	
//allocating memory. Only need /32 because we are using bits, not ints. also, calloc flushes the memory so there
//are no weird things going on
	unsigned int size = (maxPrime/32);
	bitArray = calloc(size,(sizeof(unsigned int)));
    
    //sets all possitions in the bitmap as 1, denoting that they are prime. This is how the greek math guy set it up
    for ( i = 0; i < maxPrime; i++ )
    {
        isAPrime(bitArray, i);
    }
    
    //just making sure that 0 and 1 are not primes
	isNotAPrime(bitArray, 0);
	isNotAPrime(bitArray, 1);
    
//all even numbers are prime, so we can skip them
	unsigned int multiplyBy = 2;
	unsigned int deivideBy = maxPrime;
	deivideBy = floor(maxPrime / multiplyBy);
	
	for(i = 1; i <= deivideBy; i++)
	{
		if((i*multiplyBy) != multiplyBy)//don't want to set the prime as a not prime
		{
			isNotAPrime(bitArray, (i*multiplyBy));
		}
	}
    
    //must declare memory
	pthread_t *thread = (pthread_t*) malloc(sizeof(pthread_t) * numberOfThreads);
    
    //giving threads an attribute of detachable
	pthread_attr_t attr;
    
	if(pthread_attr_init(&attr) != 0)
	{
		printf("Error initializing threads\n");
		exit(-1);
	}
	if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) != 0)
	{
		printf("Error setting detachable state\n");
		exit(-1);
	}
    
    //initialize mutex. From TLPI pg 642
	pthread_mutex_init(&mutex, NULL);
    
    nextPrime = 3; //we already took care of 2
    deivideBy = sqrt(maxPrime);
    
    //create the threads
	for (i = 0; i < numberOfThreads; i++)
	{
		if (pthread_create(&thread[i], &attr, makeNotPrime, NULL) != 0)
		{
			printf("Error creating threads\n");
		}
	}
    
//joining is like wait, but for threads
	for (i = 0; i < numberOfThreads; i++)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			printf("Error joining threads\n");
		}
	}
    
    if(qflag == 1)
    {
        endTime = time(&end);
        totalTime = (endTime - startTime);
        printf("Total Time: %.f seconds \n", totalTime);
    }
    
    if(qflag == 0) //if q specified on commands line then we won't print
    {
        //print twin primes
        for(i = 0; i < (maxPrime - 2); i++)
        {
            if (checkIfPrime(bitArray, i) == 1) //if it's a prime
            {
                if(checkIfPrime(bitArray, (i+2)) == 1)
                {
                    printf("%lu %lu\n", i, (i+2));
                }
            }
        }
    }
    
    //Destroy threads
	if (pthread_attr_destroy(&attr) != 0)
	{
		printf("Error destroying thread attribute\n");
	}
	if (pthread_mutex_destroy(&mutex) != 0)
	{
		printf("Error destroying mutex\n");
	}
    
    //free the memory that was used
	free(bitArray);
	free(thread);
	pthread_exit(NULL);
    
	return 0;
    
}



//functions

//function passed in when creating threads
void *makeNotPrime(void * holder)
{
	unsigned int curNum = 3;
	unsigned int max;
	
	while(nextPrime <= deivideBy)
	{
		pthread_mutex_lock(&mutex);
		curNum = nextPrime;
		do
		{
            nextPrime =  nextPrime + 2;
		} while( checkIfPrime(bitArray, nextPrime) != 1 );
		
        
        pthread_mutex_unlock(&mutex);
        
		max = floor(maxPrime / curNum);
		
        unsigned int z;
        
		for(z = 2; z <= max ; z++)
		{
			isNotAPrime(bitArray, (z*curNum));
		}
	}
    return NULL;
}

//marks position in bit array as prime
void isAPrime(unsigned int A[ ], unsigned int k)
{
	unsigned int i = k/32;
	unsigned int pos = k%32;
	unsigned int flag = 1;
	flag = flag << pos;
	A[i] = A[i] | flag;
}

//checks if a position in bit array is marked as prime or not
int checkIfPrime(unsigned int A[ ], unsigned int k)
{
    unsigned int i = k/32;
    unsigned  int pos = k%32;
    unsigned int flag = 1;
    flag = flag << pos;
    if ( A[i] & flag )
        return 1;
    else
        return 0;
}

//marks position in bit array as not a prime
void isNotAPrime(unsigned int A[ ], unsigned int k)
{
    unsigned int i = k/32;
    unsigned int pos = k%32;
    unsigned int flag = 1;
    flag = flag << pos;
    flag = ~flag;
    A[i] = A[i] & flag;
}



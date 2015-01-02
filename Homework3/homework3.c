/*************************************
 * NAME: Ian Paul
 * EMAIL: pauli@onid.oregonstate.edu
 * CLASS: CS311-400
 * ASSIGNMENT: Homework 3
 * ***********************************/


//Includes Go Here

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

int main (int argc, char *argv[])
{

// variables
char c;
char *buffer;

int vFlag = 0;
int fFlag = 0; //filename
int oFlag = 0; //offset1
int lFlag = 0; //len
int OFlag = 0; //offset2
int eFlag = 0; //elen    extra credit

char *fValue = NULL;
int oValue = 0;
int lValue = 0;
int OValue = 0;
int eValue = 0;

int fileDescriptor;
int newOffset;
int newOffset2;
int endOffset;


int lenMax = 10000;
int fStart = 0;

//opperation for getting arguments

while((c = getopt(argc, argv, "vf:o:l:O:e:")) != -1)
	switch (c)
		{
		case 'v':
			vFlag=1;
			break;	
		case 'f':
			fFlag=1;
			fValue = optarg;
			break;
		case 'o':
			oFlag=1;
			oValue = atoi(optarg);
			if(oValue<fStart){
				printf("-o argument must be greater than %d", fStart);
				exit(1);
				}
			break;
		case 'l':
			lFlag=1;
			lValue = atoi(optarg);
			if(lValue<0){
				printf("Number of bytes must be greater than 0");
				exit(1);
				}
			if(lValue>lenMax){
				printf("Number must be less than %d", lenMax);
				exit(1);
				}
			break;
		case 'O':
			OFlag=1;
			OValue = atoi(optarg);
			break;
		case 'e':
			eFlag=1;
			eValue=atoi(optarg);
			break;
		case '?':
		  if (optopt == 'f' || optopt == 'o' || optopt == 'l' || optopt == 'O' || optopt == 'e')
		     fprintf(stderr, "Option -%c requires an argument.\n", optopt);
		  else
		     fprintf(stderr, "Unknown option character '\\x%x.\n",optopt);
		  return 1;
		default:
			abort();
		}

//if statements that actually do the work
//
//-v option just prints what the command line arguments were
if(vFlag == 1){
	printf("These are your command line argument options\n");
	printf("-v Verbose requires no arguments\n");
	printf("-f filename requires a [file name] argument\n");
	printf("-l len requires a [length] argument\n");
        printf("-o offset1 requires a [offset] argument and -l [length] argument\n");
	printf("-O offset2 requires a [offset] argument and -l [length] argument\n");
	printf("-e elen requires a [end length] argument\n");

}

//-f option is which file gets opened 
if (fFlag == 1){
  fileDescriptor=open(fValue, O_RDONLY);
  if(fileDescriptor ==-1){
    printf("Error. Cannot open %s. Exiting program.", fValue);
    exit(1);
  }
  else{
    printf("%s successfully oppened\n", fValue);
  }
}

//-l option is the length to be printed
if(lFlag == 1){
  if(oFlag != 1 || OFlag != 1 || eFlag !=1){
    char buf[lValue];
    if(fileDescriptor == -1){
      printf("Can't open file");
      exit(1);
    }
    ssize_t lengthToRead;
    lengthToRead=read(fileDescriptor,buf,lValue);
  }
}

//-o option is the first offset
if(oFlag == 1){
  if(lFlag != 1){
    printf("Please be sure to specify length\n");
    exit(1);
  }
  newOffset = lseek(fileDescriptor, oValue, SEEK_CUR);
  buffer = malloc(sizeof(char)*lValue);
  printf("\n+++++++++++++++++++++<Offset 1>++++++++++++++++++++++++++\n");
  read(fileDescriptor, buffer, lValue);
  write(1, buffer, lValue);
  printf("\n=================<END of Offset 1>====================\n");
}


//-O option is the second offset
if(OFlag == 1){
  if(lFlag != 1){
     printf("Please be sure to specify length\n");
    exit(1);
  }
  newOffset2 = lseek(fileDescriptor, OValue, SEEK_CUR);
  buffer = malloc(sizeof(char)*lValue);
  printf("\n+++++++++++++++++++++<Offset 2>++++++++++++++++++++++++++\n");
  read(fileDescriptor, buffer, lValue);
  write(1, buffer, lValue);
  printf("\n=================<END of Offset 2>====================\n");
}

//-e option is the first offset
if(eFlag == 1){
  endOffset = lseek(fileDescriptor, -(eValue), SEEK_END);
  buffer = malloc(sizeof(char)*eValue);
  printf("\n+++++++++++++++++++++<E Option Start>++++++++++++++++++++++++++\n");
  read(fileDescriptor, buffer, eValue);
  write(1, buffer, eValue);
  printf("\n=================<E Option End>====================\n");
}

return 0;
}


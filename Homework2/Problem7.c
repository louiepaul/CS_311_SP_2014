/***************************************************
 *NAME: Ian Paul
 *EMAIL: pauli@onid.oregonstate.edu
 *CLASS: CS311-400
 *ASSIGNMENT: Homework 2
 **************************************************/

#include <stdio.h>
#include <getopt.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main (int argc, char *argv[])
{
  char c;
  struct utsname uname_pointer;
  time_t time_raw_format;
  struct stat s;
  
  
  int hflag = 0;
  int tflag = 0;
  int fflag = 0;
  char *fvalue = NULL;
  
  while( (c = getopt(argc, argv, "htf:")) != -1)
	switch (c)
		{
		case 'h':
			hflag = 1;
			break;
		case 't':
			tflag = 1;
			break;
		case 'f':
			fflag = 1;
			fvalue = optarg;
			break;
		case '?':
		  if (optopt == 'f')
		     fprintf (stderr, "Option -%c requires an argumen.\n", optopt);
		  else if (isprint (optopt))
		     fprintf (stderr, "Unknown option '-%c'.\n", optopt);
		  else
		     fprintf (stderr, "Unknown option character '\\x%x.\n", optopt);
		  return 1;
		default:
			abort();
		  }
if (hflag == 1){
  uname(&uname_pointer);
  printf("Hostname = %s \n", uname_pointer.nodename);
  }

if (tflag == 1){
  time(&time_raw_format);
  printf("The current local time: %s", ctime(&time_raw_format));
  }

if (fflag == 1){
  if (stat(fvalue, &s) == 0) {
	printf("size of file '%s' is %d bytes\n", fvalue, (int) s.st_size);
  }
  else {
	printf("file '%s' not found\n",fvalue);
  }
}

return 0;
}

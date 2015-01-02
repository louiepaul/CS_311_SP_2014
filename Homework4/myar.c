/*************************************
 * NAME: Ian Paul
 * EMAIL: pauli@onid.oregonstate.edu
 * CLASS: CS311-400
 * ASSIGNMENT: Homework 4
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

#include <ar.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <string.h>
#include <utime.h>
#include <time.h>
#include <dirent.h>


#include "file_perms.h" //this is copied from the book on pg 296
#define STR_SIZE sizeof("rwxrwxrwx")

#define FILE_PERMS (S_IRUSR | S_IWUSR | S_IRGRP)
#define BLOCKSIZE 1


//function declorations
void checkForFileFunc(char *fileToCheck);
void qFuncAdd(char *archName, char *fileToAdd);
int qFuncNoAdd(char *archName);
void tFunc(char *archName);
void vFunc(char *archName);
char * filePermStr(mode_t perm, int flags);

void scanDir();
void xScanForArch(char *archName);



int main (int argc, char *argv[])
{

// variables
char c;
//char *buffer;

int qFlag = 0; //quickly append named files to archive
int xFlag = 0; //xtract named members from archive
int tFlag = 0; //print table of contents
int vFlag = 0; //verbose table of contents of the archive
int dFlag = 0; //delete named files from archive
int AFlag = 0; //quickly append all reular files in current directories
int wFlag = 0; //extra credit. add modified files to archive

char *xValue = NULL;
char *AValue = NULL;
char *archName = NULL;


//opperation for getting arguments

while((c = getopt(argc, argv, "q:x:t:v:dAw")) != -1)
	switch (c)
		{
		case 'q':
			qFlag=1;
			archName = argv[2];
			
			if (argc > 3){
			
			int i = 3;
			while(i < argc){
				

				checkForFileFunc(argv[i]);
								
				i++;
				}
			}
			
			if (qFuncNoAdd(archName) == 1){
				printf("myar: creating %s\n", archName);
			}
			break;	
		case 'x':
			xFlag=1;
			xValue = argv[2];
			xScanForArch(xValue);
			
			break;
		case 't':
			tFlag=1;
			archName = optarg;
			break;
		case 'v':
			vFlag=1;
			archName = optarg;
			break;
		case 'd':
			dFlag=1;
			break;
		case 'A':
			AFlag=1;
			AValue= argv[2];
			
			if(argc>3){
				printf("Too many arguments! %s is ignored\n", argv[3]);
			}
			
			if (qFuncNoAdd(AValue) == 1){
				printf("myar: creating %s\n", AValue);
			}
			break;
		case 'w':
			wFlag=1;
			break;
		case '?':
		  if (optopt == 'x' || optopt == 'A')
		     fprintf(stderr, "Option -%c requires an argument.\n", optopt);
		  else
		     fprintf(stderr, "Unknown option character '\\x%x.\n",optopt);
		  return 1;
		default:
			abort();
		}

//if statements that actually do the work
//

//-q option
if(qFlag == 1){
	
	int i = 0;
	
	char *fileToAdd;
	
	for (i = 3; i < argc; i++){
	
		fileToAdd = argv[i];
		qFuncAdd(archName, fileToAdd);
	}
	

}

//-x option
if(xFlag == 1){

	int i = 0;
	
	char *fileToExtract;
	if (argc == 3){
		xTractAll(xValue);
	}
	
	else if (argc > 3){
		
		printf("Sorry, only works for just -x and no arguments\n");
		//for (i = 4; i < argc; i++){
	
			//fileToExtract = argv[i];
			//qFuncAdd(xValue, fileToAdd);
		}
	
	
	
}

//-t option
if(tFlag == 1){
	
	
	tFunc(archName);

}


//-v option just prints what the command line arguments were
if(vFlag == 1){
	vFunc(archName);
}

if(AFlag == 1){
	scanDir(AValue);
}

if(dFlag == 1){
printf("Can't delete\n");
}

if(wFlag == 1){
printf("No such command\n");
}


return 0;
}

void xTractOne(char *xValue, char *fileToExtract){

}

void xTractAll(char *xValue){

	char *arch = xValue;

	
	int in_fd;
	
	char excludeSlash = '/';
	char *finder;
	char *newFile = NULL;
	
	struct ar_hdr header; 
	struct stat st;
	int pos;
	char *buffer;
	int size = 0;
	int fdX;
	int out_fd;
	int archSize;
	int fileSize;
	
	stat(arch, &st);
        archSize = st.st_size;

		st.st_mode = umask(0);
        buffer = malloc(sizeof(char)*archSize);
	
	fdX = open(arch, O_RDONLY);
	
		if(fdX == -1)
		{
			printf("myar: %s: No such directory\n", arch);
			exit(1);
		}


		pos = lseek(fdX, SARMAG, 0);

        while(pos<archSize){

        read(fdX, buffer, 16);
        memcpy(header.ar_name, buffer, 15);
	
        read(fdX, buffer, 12);
        memcpy(header.ar_date, buffer, 11);

        read(fdX, buffer, 6);
		memcpy(header.ar_uid, buffer, 5);
        
		read(fdX, buffer, 6);
        memcpy(header.ar_gid, buffer, 5);
   
        read(fdX, buffer, 8);
        memcpy(header.ar_mode, buffer, 7);

        read(fdX, buffer, 10);
        memcpy(header.ar_size, buffer, 9);
		fileSize = atoi(header.ar_size);
		
		read(fdX, buffer, 2);
		memcpy(header.ar_fmag, buffer, 1);
		
		read(fdX, buffer, fileSize);
		
		if(fileSize % 2 != 0)
		{
			pos = lseek(fdX, 1, SEEK_CUR);
		}

		pos = lseek(fdX, 0, SEEK_CUR);
		
		finder = strchr(header.ar_name, excludeSlash);
		
		if (finder)
		{
			size_t newLen = finder - header.ar_name;
			newFile = malloc(newLen +1);
			memcpy(newFile, header.ar_name, newLen);
			newFile[newLen] = '\0';
		}

		out_fd = open(newFile, O_CREAT | O_WRONLY, 0640);
			if(out_fd == -1)
			{
				printf("Error: Unable to create file %s\n", newFile);
			}
			
		write(out_fd, buffer, fileSize);
		close(out_fd);
		
	}
	
	close(fdX);
	
}
		





void scanDir(char *AValue){

	char *bigArchName = AValue;
	

	struct stat st;
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if(d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			stat(dir->d_name, &st);
			
			int in_fd;
			
			in_fd = open(dir->d_name, O_RDONLY);
			
			if((strcmp(dir->d_name, bigArchName) == 0)){
				printf("Appending all regular files from directory to archive: %s\n", bigArchName);
			}
			else if(S_ISREG(st.st_mode)){
			
				int fileType = (strlen(dir->d_name))-1;
			
				if(dir->d_name[fileType] != 'o'){
				
				int i;
				int goodFile = 0;
					for(i = 0; i<(fileType + 1); i++){
						if(dir->d_name[i] == '.'){

						goodFile = 1;

						}
					}
					
					if(goodFile == 1){
						qFuncAdd(bigArchName, dir->d_name);
					}
				}
			}
						
		}
		closedir(d);
	}
	
}



void checkForFileFunc(char *fileToCheck){

	int file_fd;
	if((file_fd = (open(fileToCheck, O_RDONLY)) == -1)){
		printf("myar: %s: No such file or directory\n", fileToCheck);
		close(file_fd);
		exit(1);
	}
	close(file_fd);

}

void qFuncAdd(char *archName, char *fileToAdd){


	char *input = fileToAdd;
	char *output = archName;
	
	int in_fd;
	int out_fd;

	in_fd = open(input, O_RDONLY);
	if (in_fd == -1){
		printf("Can't open input file");
		exit(-1);
	}
	
	out_fd = open(output, O_WRONLY | O_APPEND);
	if (out_fd == -1){
		printf("Can't open output file");
		exit(-1);
	}
	

	struct ar_hdr header; 
	struct stat st;
	
	// [mode] [uid]/[gid]	[size][date][name]
	
	stat(fileToAdd, &st);
    
	//note
	int size = st.st_size;
	
	//putting the stat info of the file into the ar_hdr struct
	sprintf(header.ar_name, "%s", fileToAdd);
	sprintf(header.ar_date, "%d", st.st_mtime);
	sprintf(header.ar_uid, "%d", st.st_uid);
	sprintf(header.ar_gid, "%d", st.st_gid);
	sprintf(header.ar_size, "%d", st.st_size);
	
	//converting mode so it works right
	int tempSize = st.st_size;
	unsigned long fileModer = st.st_mode;
	sprintf(header.ar_mode, "%lo", fileModer);
	
	char slasher[2] = "/";
	char spacer[2] = " ";
	
	write(out_fd, header.ar_name, strlen(header.ar_name));
	int restOfName = (16 - (strlen(header.ar_name)));
	write(out_fd, slasher, strlen(slasher));
	
		int g;
		for (g=0; g<restOfName-1; g++){
			write(out_fd, spacer, 1);
		}
	

	write(out_fd, header.ar_date, strlen(header.ar_date));
	int restOfDate = (12 - (strlen(header.ar_date)));
	
		for (g=0; g<restOfDate; g++){
			write(out_fd, spacer, 1);
		}
	
	write(out_fd, header.ar_uid, strlen(header.ar_uid));
	int restOfUid = (6 - (strlen(header.ar_uid)));
	
		for (g=0; g<restOfUid; g++){
			write(out_fd, spacer, 1);
		}
	
	
	write(out_fd, header.ar_gid, strlen(header.ar_gid));
	int restOfGid = (6 - (strlen(header.ar_gid)));
	
		for (g=0; g<restOfGid; g++){
			write(out_fd, spacer, 1);
		}
	
	write(out_fd, header.ar_mode, strlen(header.ar_mode));
	int restOfMode = (8 - (strlen(header.ar_mode)));
	
		for (g=0; g<restOfMode; g++){
			write(out_fd, spacer, 1);
		}
	
	write(out_fd, header.ar_size, strlen(header.ar_size));
	int restOfSize = (10 - (strlen(header.ar_size)));
	
		for (g=0; g<restOfSize; g++){
			write(out_fd, spacer, 1);
		}
	
	write(out_fd, ARFMAG, 2);
	
	char buf[size];
	
	read(in_fd, buf, size);
	write(out_fd, buf, size);
	
	char newLine[] = "\n";
	
	if (tempSize % 2 == 1){
		write(out_fd, newLine, 1);
	}
	
	close(out_fd);
	close(in_fd);
}

//function that checks for or creates an archive
void xScanForArch(char *archName){



		char *output = archName;
	
		int in_fd;
		
		in_fd = open(output, O_RDONLY);
			if (in_fd == -1){
			
			printf("myar: %s: No such file or directory\n", output);
			
			close(in_fd);
			exit(-1);
			}
		
}

//function that checks for or creates an archive
int qFuncNoAdd(char *archName){



		char *output = archName;
		char magicLine[9] = "!<arch>\n";

	
		int in_fd;
		
		in_fd = open(output, O_RDONLY);
			if (in_fd == -1){
			close(in_fd);
		

		in_fd = open(output, O_CREAT | O_WRONLY, 0666);
			if(in_fd == -1){
				exit(1);
			}
			
			printf("in_fd is: %d\n", in_fd);

		write(in_fd, &magicLine, sizeof(&magicLine));

		close(in_fd);
		return 1;
		}
		else{
		close(in_fd);
		return 0;
		}
		
}		

	


void tFunc(char *archName){
	
	char *buffer;

	struct stat st;
	int size = 0;
	int fd;
	struct ar_hdr header; 
	stat(archName, &st);
	size = st.st_size;
	fd = open(archName, O_RDONLY);
	buffer = malloc(sizeof(char)*size);
	char arBuf[16];
	char fileSizeBuf[10];
	int pos = lseek(fd, SARMAG, 0);

	
	while(pos<size){
	read(fd, arBuf, 16);
	
	memcpy(header.ar_name, arBuf, 15);

	//printing out the name minus /
	int nameLength = (int)strlen(header.ar_name);
	int k = 0;
	for (k = 0; k<nameLength; k++)
	{
		if(header.ar_name[k] != '/'){
			printf("%c", header.ar_name[k]);
		}
	}
	pos = lseek(fd, 32, SEEK_CUR);
	read(fd, fileSizeBuf, 10);
	int sizeOfFile;
	sizeOfFile = atoi(fileSizeBuf);
	if(sizeOfFile%2 == 1){
		sizeOfFile = sizeOfFile +3;
	}
	else{
		sizeOfFile = sizeOfFile +2;
	}

	pos = lseek(fd, sizeOfFile, SEEK_CUR);
	printf("\n");
	}
close(fd);
}



void vFunc(char *archName){
	
	struct ar_hdr header; 
	struct stat st;
	
	char *buffer;
	int size = 0;
	int fdV;
	
	stat(archName, &st);
        size = st.st_size;
		umask(FILE_PERMS);
        fdV = open(archName, O_RDONLY, FILE_PERMS);
		st.st_mode = umask(0);
        buffer = malloc(sizeof(char)*size);
	

        int pos;
	pos = lseek(fdV, SARMAG, 0);

        while(pos<size){

        read(fdV, buffer, 16);
        memcpy(header.ar_name, buffer, 15);

        read(fdV, buffer, 12);
        memcpy(header.ar_date, buffer, 11);

        read(fdV, buffer, 6);
		memcpy(header.ar_uid, buffer, 5);
        
		read(fdV, buffer, 6);
        memcpy(header.ar_gid, buffer, 5);
   
        read(fdV, buffer, 8);
        memcpy(header.ar_mode, buffer, 7);

        read(fdV, buffer, 10);
        memcpy(header.ar_size, buffer, 9);

	int fileInArchSize;
	fileInArchSize = atoi(header.ar_size);
	
	int tempFileSize = 0;
	tempFileSize = fileInArchSize;
	int numCount = 0 ;
	
	while(tempFileSize != 0){
		tempFileSize = tempFileSize/10;
		numCount++;
	}

//printing the whole line properly
//[mode] [uid]/[gid]    [size] [date] [name]

int modeLength = 0;
modeLength =(int)strlen(header.ar_mode);

char *modeValue = NULL;
modeValue = malloc(modeLength+1);
memcpy(modeValue, header.ar_mode, modeLength);

char ownerValue = modeValue[3];
char groupValue = modeValue[4];
char otherValue = modeValue[5];


	if(ownerValue == '0'){
		printf("---");
	}
	else if(ownerValue == '1'){
		printf("--x");
	}
	else if(ownerValue == '2'){
		printf("-w-");
	}
	else if(ownerValue == '3'){
		printf("-wx");
	}
	else if(ownerValue == '4'){
		printf("r--");
	}
	else if(ownerValue == '5'){
		printf("r-x");
	}
	else if(ownerValue == '6'){
		printf("rw-");
	}
	else if(ownerValue == '7'){
		printf("rwx");
	}	
	else{
	printf("Error");
	}

	if(groupValue == '0'){
		printf("---");
	}
	else if(groupValue == '1'){
		printf("--x");
	}
	else if(groupValue == '2'){
		printf("-w-");
	}
	else if(groupValue == '3'){
		printf("-wx");
	}
	else if(groupValue == '4'){
		printf("r--");
	}
	else if(groupValue == '5'){
		printf("r-x");
	}
	else if(groupValue == '6'){
		printf("rw-");
	}
	else if(groupValue == '7'){
		printf("rwx");
	}	
	else{
	printf("Error");
	}	


	if(otherValue == '0'){
		printf("---");
	}
	else if(otherValue == '1'){
		printf("--x");
	}
	else if(otherValue == '2'){
		printf("-w-");
	}
	else if(otherValue == '3'){
		printf("-wx");
	}
	else if(otherValue == '4'){
		printf("r--");
	}
	else if(otherValue == '5'){
		printf("r-x");
	}
	else if(otherValue == '6'){
		printf("rw-");
	}
	else if(otherValue == '7'){
		printf("rwx");
	}	
	else{
	printf("Error");
	}	


printf(" ");


//printing the uid and gid
int uidsize = 5;
printf("%.*s/",uidsize, header.ar_uid);
printf("%s\t", header.ar_gid);

//printing the file size
printf("%7d ", fileInArchSize);



//printing the time
struct utimbuf new_times;
struct tm *local;
time_t mtime;
	
mtime = atoi(header.ar_date);
	
local = localtime(&mtime);

	
new_times.actime = mtime;
new_times.modtime = time(NULL);	

char s[1000];
struct tm * p = localtime(&mtime);
strftime(s, 1000, "%b %d %R %Y ", p);
printf("%s",s);


//printing out the name minus /
int nameLength = (int)strlen(header.ar_name);
int k = 0;
for (k = 0; k<nameLength; k++)
{
	if(header.ar_name[k] != '/'){
		printf("%c", header.ar_name[k]);
	}
}
printf("\n");

	if(fileInArchSize%2 == 1){
		fileInArchSize = fileInArchSize+3;
	}
	else{
		fileInArchSize = fileInArchSize+2;
	}
	
	pos = lseek(fdV, fileInArchSize, SEEK_CUR);
}


close(fdV);
}


//function from the book pg 296
char *
filePermStr(mode_t perm, int flags)
{
//	int FP_SPECIAL = 1;

	static char str[STR_SIZE];

	snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c%c",
		(perm & S_IRUSR) ? 'r' : '-', (perm & S_IWUSR) ? 'w' : '-',
		(perm & S_IXUSR) ? 
			(((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
			(((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
		(perm & S_IRGRP) ? 'r' : '-', (perm & S_IWGRP) ? 'w' : '-',
		(perm & S_IXGRP) ?
			(((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
			(((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
		(perm & S_IROTH) ? 'r' : '-', (perm & S_IWOTH) ? 'w' : '-',
		(perm & S_IXOTH) ?
			(((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 't' : 'x') :
			(((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 'T' : '-'));
	return str;
}

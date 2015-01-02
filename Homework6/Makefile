#NAME: Ian Paul
#EMAIL: pauli@onid.oregonstate.edu
#CLASS: CS311-400
#ASSIGNMENT: Homework5
#
# $RCSfile$
# $Revision$
# $Author$
# $Date$
# $Log$
#
#
# Reqs from HW 4 and 5
# -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement


CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall  
LIBLINKS = -lrt -lm -lpthread
PROGS=primeMProc primePThread


all: $(PROGS)
	
primeMProc: primeMProc.o
	$(CC) $(CFLAGS) -o primeMProc primeMProc.o $(LIBLINKS)

primeMProc.o: primeMProc.c
	$(CC) $(CFLAGS) -c primeMProc.c
	
primePThread: primePThread.o
	$(CC) $(CFLAGS) -o primePThread primePThread.o $(LIBLINKS)

primePThread.o: primePThread.c
	$(CC) $(CFLAGS) -c primePThread.c
	
clean:
	rm -f $(PROGS) *.o *~ *#


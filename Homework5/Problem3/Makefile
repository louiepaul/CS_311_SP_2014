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

CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement
PROGS=uniqify

all: $(PROGS)

uniqify: uniqify.o
	$(CC) $(CFLAGS) -o uniqify uniqify.o

uniqify.o: uniqify.c
	$(CC) $(CFLAGS) -c uniqify.c
	
clean:
	rm -f $(PROGS) *.o *~ *#


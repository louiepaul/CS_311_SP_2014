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
PROGS=pipeline

all: $(PROGS)

pipeline: pipeline.o
	$(CC) $(CFLAGS) -o pipeline pipeline.o

pipeline.o: pipeline.c
	$(CC) $(CFLAGS) -c pipeline.c
	
	
test: pipeline.o
	@rm -f bashOutfile1 bashOutfile2 pipeOutfile1 pipeOutfile2
	@pipeline.bash -f bashOutfile2 < words.txt > bashOutfile1
	@pipeline -f pipeOutfile2 < words.txt > pipeOutfile1
	diff bashOutfile1 pipeOutfile1
	diff bashOutfile2 pipeOutfile2

	

clean:
	rm -f $(PROGS) *.o *~ *#


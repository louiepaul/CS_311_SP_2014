#NAME: Ian Paul
#EMAIL: pauli@onid.oregonstate.edu
#CLASS: CS311-400
#ASSIGNMENT: Homework 2

import sys
import urllib2

# two command line arguments
# first one is where the file is
# one is what to save it as

while True:
	try:
		arg1 = sys.argv[1]
		arg2 = sys.argv[2]
		break
	except (NameError, ValueError, TypeError, RuntimeError):
		exit()



f = urllib2.urlopen('http://' + arg1)

fdld = open(arg2, "w") #w stands for write, so it will overwrite
fdld.write(f.read())
fdld.close()


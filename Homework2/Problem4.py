#NAME: Ian Paul
#EMAIL: pauli@onid.oregonstate.edu
#CLASS: CS311-400
#ASSIGNMENT: Homework 2

import sys



primeList = []

while True:
	try:
		arg1 = sys.argv[1]
		break
	except (NameError, ValueError, TypeError, RuntimeError):
		exit()

uNum = int(arg1)
intMax = 3210

if uNum > intMax:
	print 'number too big!!!!!'
	exit()

def primeCheck():

	for x in range(2, 30000):
		prime = True
		for i in range(2, x):
			if(x % i == 0):
				prime = False
		if prime == True:
			primeList.append(x)





primeCheck()

print primeList


#result = primeList[uNum - 1]
toPrint = uNum - 1
print primeList[toPrint]
#print primeList[uNum-1]

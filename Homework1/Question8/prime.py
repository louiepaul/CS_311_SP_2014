# NAME: Ian Paul
# EMAIL: pauli@onid.oregonstate.edu
# CLASS: CS311-400
# ASSIGNMENT: Homework 1
# NOTES: Emma Paul and I were working on this assignment together. We each wrote
#	 our own code, but we helped eachother out when we got stuck on parts.


# Prime number program in python

# Gets user input, prints out thr prime numbers under that and how many there are
# does error handeling



# Print instructions 
print("Welcome to PRIME NUMBERS!")


# sets variables

a = 2
primeList = []

# get's user input and sets it to an int variable
# makes sure the value is an int, repeats prompt if not
while True:
	try:
		uNumString = int(input("Please enter an integer: "))
		break
	except (RuntimeError, TypeError, NameError, ValueError):
		print "Whooh there, partner! We are looking for numbers. Try again"




uNum = int(uNumString)

if uNum > 200:
	print "Too large "
	exit()

# function for checking primes and getting list

def primeCheck(a, uNum):
	while a < uNum: 
    		if a % 2 == 0 and a != 2:
			a = a+1

    		elif a % 3 == 0 and a != 3:
        		a = a+1

    		elif a % 5 == 0 and a != 5:
        		a = a+1

    		elif a % 7 == 0 and a != 7: 
        		a = a+1
		
		elif a % 11 == 0 and a != 11:
			a = a+1

    		else:
        		primeList.append(a)
        		a = a+1

	

	
# print the results
primeCheck(a, uNum)
print("The prime numbers under your number are")
print primeList

sumPrimes = len(primeList)
print('There are ', sumPrimes,  ' prime numbers in the list')



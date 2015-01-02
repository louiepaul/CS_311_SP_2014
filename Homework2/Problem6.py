#NAME: Ian Paul
#EMAIL: pauli@onid.oregonstate.edu
#CLASS: CS311-400
#ASSIGNMENT: Homework 2
#NOTES: I worked with Emma Paul and Andrew Goetz


file = open('P6BigIntList.txt')
numList = file.read()

print numList


biggestInt = 0


i = 0


while i < 996:
	testInt = int(numList[i]) * int(numList[i+1]) * int(numList[i+2]) * int(numList[i+3]) * int(numList[i+4])
	i = i+1
	if testInt > biggestInt:
		biggestInt = testInt


print biggestInt

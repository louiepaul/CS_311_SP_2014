#NAME: Ian Paul
#EMAIL: pauli@onid.oregonstate.edu
#CLASS: CS311-400
#ASSIGNMENT: Homework 2

import sys
import optparse
import getopt
import os

#sets the command line opperations and what to do with them
from optparse import OptionParser

usage = "usage: %prog[options]arg"
parser = OptionParser()
parser.add_option("-t", "--term", action="store", type="string", dest="termname")
parser.add_option("-c", "--class", action="store", type="string", dest="classname")

(options, args) = parser.parse_args()

#checks to make sure there are enough args
if len(sys.argv) !=5:
	parser.error("Not enough arguments")

else:
#stores the command line names in to variables that we can use
	termName = options.termname
	className = options.classname
	dirPath = ('%s/%s' % (termName, className))


# function for making the term and class
# if term exists, check class. if class exists, exit, if not create clase
# if term doesn't exist, create it and the class
def check_for_path(dirPath):
	parDir = os.path.dirname(dirPath)
	if os.path.exists(parDir):
		if not os.path.exists(dirPath):
			os.mkdir(dirPath)
		else:
			print("Class already exists")
			sys.exit()
	if not os.path.exists(parDir):
		os.makedirs(dirPath)

#creates term dir and class dir if they don't exist
check_for_path(dirPath)



#function for creating the sub directory
def sub_dir_creator(dirPath, subDir):
	parDir = os.path.dirname(dirPath)
	if os.path.exists(parDir):
		os.mkdir('%s%s' % (dirPath, subDir))
	else:
		print("Parent directories must exist")



# Variables for the different sub directories
assignmentsVar = ("/assignments")
examplesVar = ("/examples")
examsVar = ("/exams")
lectureNotesVar = ("/lecture_notes")
submissionsVar = ("/submissions")


subDirList = [assignmentsVar, examplesVar, examsVar, lectureNotesVar, submissionsVar]



# function for creating subdirectories
def super_sub_dir_creator(dirPath, subDirList):
	for i in range (len(subDirList)):
		tempSub = subDirList[i]
		sub_dir_creator(dirPath, tempSub)
		print('%s created in %s' % (tempSub, dirPath))
	else:
		print("")



#actually creates the sub directories
super_sub_dir_creator(dirPath, subDirList)


# function for creating the symbolic links
def symbolic_link_creator(dirPath):
	
	symLinkStartVar = ("/usr/local/classes/eecs/")
	readMeVar = ("/src/README")
	srcVar = ("/src")
	readBigBoom = "".join((symLinkStartVar, dirPath, readMeVar))
	srcBigBoom = "".join((symLinkStartVar, dirPath, srcVar))
	readMeName = ("README")
	srcName = ("class_src")
	os.symlink(readBigBoom,readMeName)
	os.symlink(srcBigBoom,srcName)
	print ("created symbolic link %s" %(readBigBoom))
	print ("created symbolic link %s" %(srcBigBoom))

#actually create the symbolic links
symbolic_link_creator(dirPath)

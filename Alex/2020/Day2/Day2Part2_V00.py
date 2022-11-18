#Advent of code 2020
#Day 2 Part 2
#Process corrupted password file and check for validity.

import numpy
import pdb #pdb.set_trace()
import time


#Import and sort File
passwords_corrupted = numpy.genfromtxt("input_day2.txt", dtype='str', delimiter="\n")

#Counter for valid results
numvalid = 0

#Loop through lines
for entry in passwords_corrupted:
	#Extract Data
	entry1 = entry.split("-")
	position1 = int(entry1[0])
	entry1_2 = entry1[1]
	entry2 = entry1_2.split()
	position2 = int(entry2[0])
	searchtermtemp = entry2[1]
	searchterm = searchtermtemp[:1]
	password = entry2[2]
	
	#check validity
	if (password[position1-1] == searchterm or password[position2-1] == searchterm) and not password[position1-1] == password[position2-1]:
		numvalid = numvalid + 1
	

#Result
print(numvalid)
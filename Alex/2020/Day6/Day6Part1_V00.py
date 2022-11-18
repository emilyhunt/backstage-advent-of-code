#Advent of code 2020
#Day 6 Part 1
#26 question form

import numpy
numpy.set_printoptions(threshold=numpy.inf)
import pdb #pdb.set_trace()
import time

start_time = time.time()

#Function to count unique answers
def countuniqueanswers(group):
	
	uniqueonly = []
	
	for char in group:
		if char not in uniqueonly:
			uniqueonly.append(char)
	
	answertypes = len(uniqueonly)
	
	return answertypes


#Import and sort File
answers = []
group=""
groupsize=0
total=0

with open("input_day6.txt") as answersf:

	for line in answersf:
		#If stores group
		if line == "\n":
			#Function to process group and find info
			answertypes = countuniqueanswers(group)
			
			total += answertypes
			
			answers.append([groupsize,group,answertypes])
			group=""
			groupsize = 0
		#Concats group and counts persons
		else:
			line = line[:-1]
			group = group + line
			groupsize += 1
		#pdb.set_trace()

#Result
print(answers)
print(total)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
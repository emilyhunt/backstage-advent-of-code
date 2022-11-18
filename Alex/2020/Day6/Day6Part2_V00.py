#Advent of code 2020
#Day 6 Part 2
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
	
	return answertypes,uniqueonly

#Function to count common answers
def countcommonanswers(group,uniqueonly,groupsize):
	
	commonanswers = 0
	
	for char in uniqueonly:
		if group.count(char) == groupsize:
			commonanswers += 1
	
	return commonanswers

#Import and sort File
answers = []
group=""
groupsize=0
totalunique=0
totalcommon=0

with open("input_day6.txt") as answersf:

	for line in answersf:
		#If stores group
		if line == "\n":
			#Function to find numbers of unique answers
			answertypes = countuniqueanswers(group)
			totalunique += answertypes[0]
			
			#Function to find numbers of common answers
			commonanswers = countcommonanswers(group,answertypes[1],groupsize)
			totalcommon += commonanswers
			
			answers.append([groupsize,group,answertypes[0],commonanswers])
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
print(totalunique)
print(totalcommon)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
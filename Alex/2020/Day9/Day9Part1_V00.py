#Advent of code 2020
#Day 9 Part 1
#XMAS Code

import numpy
numpy.set_printoptions(threshold=numpy.inf)
import pdb #pdb.set_trace()
import time
import bisect

start_time = time.time()

def findTwoSummands(targetSum,sortedlist):
	
	#pdb.set_trace()
	
	#Truncate list to remove values equal to or above targetSum
	#pdb.set_trace()
	n = bisect.bisect_left(sortedlist,targetSum)
	truncsortedlist = sortedlist[0:n]
	
	#Find smallest half and determine direction
	mp = bisect.bisect_left(truncsortedlist,round(n/2))
	if mp<n/2:
		direction = "forward"
		i = 0
	else:
		direction = "reverse"
		i = n - 1
	
	#Find Target Values
	targets = targetSum - truncsortedlist
	
	#Start Search Loop
	chk = 0
	while chk == 0 and i < len(truncsortedlist):
		sortedlist_i = truncsortedlist[i] #Get list value to test
		target_i = targets[i] #Get target value
		match = bisect.bisect_left(truncsortedlist, target_i) #Find closest value
		if match == len(truncsortedlist):
			#Not a match
			chk = 0
		elif truncsortedlist[match] == target_i:#Check if exact match
			#End Loop and calc result
			chk = 1
		if direction == "forward":
			i = i + 1
		else:
			i = i - 1
	
	if i == len(truncsortedlist):
		summand1 = "no match"
		summand2 = summand1
	else:
		summand1 = target_i
		summand2 = sortedlist_i
	
	return summand1, summand2

#Import and sort File
transmission = []

with open("input_day9.txt") as transmissionf:
	for line in transmissionf:
		#Import operations
		transmission.append(int(line))

#Main Code
Preamblelength = 25
i = Preamblelength
for target in transmission[i:]:
	pos_summands = numpy.array(sorted(transmission[(i-Preamblelength):i]))
	summands = findTwoSummands(target,pos_summands)
	if summands[0] == 'no match' or summands[1] == 'no match':
		break
	i += 1



#Result
print(target," at position ",i," has no 2 summands in the previous ",Preamblelength," numbers")

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
#Advent of code 2020
#Day 1
#Find 2 numbers which equal 2020

import numpy
import bisect
import pdb
import time

start_time = time.time()

#Import and sort File
list = numpy.loadtxt("input_day1.txt",comments="#", delimiter="\n", unpack=False)
sortedlist = numpy.array(sorted(list))

#Find smallest half and determine direction
n = len(list)
mp = bisect.bisect_left(sortedlist,1010)
if mp<n/2:
	direction = "forward"
	i = 0
else:
	direction = "reverse"
	i = n - 1

#Find Target Values
targets = 2020 - sortedlist

#Start Search Loop
chk = 0
while chk == 0:
	sortedlist_i = sortedlist[i] #Get list value to test
	target_i = targets[i] #Get target value
	match = bisect.bisect_left(sortedlist, target_i) #Find closest value
	if sortedlist[match] == target_i:#Check if exact match
		#End Loop and calc result
		chk = 1
	if direction == "forward":
		i = i + 1
	else:
		i = i - 1

#Product of list and target
Result = sortedlist_i*target_i
print(str(sortedlist_i) + " x " + str(target_i) + " = " + str(Result))

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")

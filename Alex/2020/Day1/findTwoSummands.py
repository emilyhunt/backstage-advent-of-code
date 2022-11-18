import numpy
import bisect
import pdb
import time

#Function to find to summands that make a given number
def findTwoSummands(targetSum,sortedlist):
	
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
	targets = targetSum - sortedlist
	
	#Start Search Loop
	chk = 0
	while chk == 0 and i < 200:
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
	
	if i == 200:
		summand1 = "no match"
		summand2 = summand1
	else:
		summand1 = target_i
		summand2 = sortedlist_i
	
	return summand1, summand2

#Import and sort File
list = numpy.loadtxt("input_day1.txt",comments="#", delimiter="\n", unpack=False)
sortedlist = numpy.array(sorted(list))

targetSum = 2020

summands = findTwoSummands(targetSum,sortedlist)
print(summands)
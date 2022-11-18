#Advent of code 2020
#Day 10 Part 1
#Adaptor Array

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Function to find list index of next one in list
def f(l, x):
    for i in l:
        if i >x: return l.index(i)

#Import and sort File
adaptors = []

with open("input_10.txt") as adaptorsf:
	for line in adaptorsf:
		#Import operations
		
		adaptors.append(int(line[:-1]))

#Main Code
adaptors.sort()
source = 0#jolts
differances = []

i = 0
while i < len(adaptors):
    
    #pdb.set_trace()
    
    next_adaptor_up = adaptors[f(adaptors,source)]
    diff = next_adaptor_up - source
    differances.append(diff)
    if diff <= 3:
        source = next_adaptor_up
    else:
        break
    if source >= adaptors[len(adaptors)-1]:
        break

source += 3
differances.append(3)

no_of_ones = differances.count(1)
no_of_threes = differances.count(3)

product = no_of_ones*no_of_threes

#Result
print(adaptors)
print(source)



print(no_of_ones)
print(no_of_threes)
print(product)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
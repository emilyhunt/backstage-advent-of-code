#Advent of code 2021
#Day 1 Part 2
#Sonar Sweep

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Import and sort File
depths = []

with open("input_01A.txt") as depthsf:
	for line in depthsf:
		#Import operations
		
		depths.append(int(line[:-1]))

#Main Code
i = 0
raises = 0
drops = 0
sum = []
sum.append(depths[2] + depths[1] + depths[0])
for line in depths:
    if i == 0 or i == 1 or i == 2:
        i += 1
        continue
    
    sum.append(depths[i] + depths[i-1] + depths[i-2])
    diff = sum[i-2] - sum[i-3]
    if diff > 0:
        raises += 1
    if diff < 0:
        drops += 1
    i += 1

#Result
print(raises)
print(drops)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
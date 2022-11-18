#Advent of code 2021
#Day 3 Part 1
#Binary Diagnostic

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Import and sort File
diagnostic = []

with open("input_03.txt") as diagnosticf:
    for line in diagnosticf:
        #Import operations
        
        line = line[:-1]#Remove EOL symbol
        line = [char for char in line]
        
        diagnostic.append(line)

#Main Code
diagnostic = np.array(diagnostic)
gamma = []
epsilon = []

#Finds most and least common bit in each column of array
diagnostic_trans = diagnostic.transpose()
for column in diagnostic_trans:
    zeros = np.count_nonzero(column == '0')
    ones = np.count_nonzero(column == '1')
    
    if ones > zeros:
        gamma.append('1')
        epsilon.append('0')
    else:
        gamma.append('0')
        epsilon.append('1')

gamma = int("".join(gamma), 2)
epsilon = int("".join(epsilon), 2)

result = gamma*epsilon

#Result
print(diagnostic)
print(gamma)
print(epsilon)
print(result)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
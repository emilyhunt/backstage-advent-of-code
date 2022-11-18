#Advent of code 2021
#Day 14 Part 1
#Extended Polymerization

import numpy as np
np.set_printoptions(threshold=np.inf)
np.set_printoptions(linewidth=np.inf)
import pdb #pdb.set_trace()
import time
import copy
import collections

start_time = time.time()

#Functions
#Inserts pairs into a polymer
def insert_pairs(polymer,pair_insertions):
    
    new_polymer = polymer[0]
    
    for i,char in enumerate(polymer):
        if i >= len(polymer) - 1:
            continue
        
        pair = polymer[i] + polymer[i+1]
        insertion = pair_insertions[pair]
        new_polymer = new_polymer + insertion + pair[1]
    
    return new_polymer

#Import and sort File
polymer = []
pair_insertions = {}

with open("input_14.txt") as input_dataf:
    i = 0
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        if i == 0:
            polymer = line
            i += 1
            continue
        
        if line == "":
            continue
        
        line = line.split(" -> ")
        
        pair_insertions[line[0]] = line[1]

###Main Code
#Run all insertions
i = 0
while i <=10-1:
    polymer = insert_pairs(polymer,pair_insertions)
    i += 1

#Count number of letters
counts = collections.Counter(polymer)
maxcount = max(counts, key=counts.get)
maxcountno = max(counts.values())
mincount = min(counts, key=counts.get)
mincountno = min(counts.values())

diff = maxcountno - mincountno

#Result
print(diff)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
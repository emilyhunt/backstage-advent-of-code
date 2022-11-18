#Advent of code 2021
#Day 14 Part 2
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
def insert_pairs(pair_quantity,pair_insertions,letter_quantity):
    
    #Create dict to store the new polymer
    new_pair_quantity = {}
    for pair in pair_insertions:
        new_pair_quantity[pair] = 0
    
    for pair in pair_quantity:
        count = pair_quantity[pair]
        if count == 0:
            continue
        
        insertion = pair_insertions[pair]
        newpairone = pair[0] + insertion
        newpairtwo = insertion + pair[1]
        
        new_pair_quantity[newpairone] += count
        new_pair_quantity[newpairtwo] += count
        letter_quantity[insertion] += count
    
    return new_pair_quantity, letter_quantity

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
#Create dict to store the new polymer pairs
pair_quantity = {}
for pair in pair_insertions:
    pair_quantity[pair] = 0

#Encode Polymer pairs into dict
for i,char in enumerate(polymer):
    if i >= len(polymer) - 1:
            continue
    
    pair = polymer[i] + polymer[i+1]
    pair_quantity[pair] += 1

#Create dict to store the new polymer letters
letter_quantity = {}
for pair in pair_insertions:
    letter_quantity[pair[0]] = 0
    letter_quantity[pair[1]] = 0

#Encode Polymer letters into dict
for i,char in enumerate(polymer):
    letter_quantity[char] += 1

#Insert Pairs
NumIts = 40
i = 0
while i < NumIts:
    result = insert_pairs(pair_quantity,pair_insertions,letter_quantity)
    pair_quantity = result[0]
    letter_quantity = result[1]
    i += 1



#Count number of letters
maxcount = max(letter_quantity, key=letter_quantity.get)
maxcountno = max(letter_quantity.values())
mincount = min(letter_quantity, key=letter_quantity.get)
mincountno = min(letter_quantity.values())

diff = maxcountno - mincountno

#Result
print(diff)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
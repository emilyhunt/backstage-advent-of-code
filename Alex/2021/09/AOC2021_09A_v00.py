#Advent of code 2021
#Day 9 Part 1
#Smoke Basin

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Functions
def function(inputs):
    
    return output

#Import and sort File
heightmap = []

with open("input_09.txt") as heightmapf:
    for line in heightmapf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        line = list(map(int,line))
        
        heightmap.append(line)

###Main Code
heightmap = np.array(heightmap)
risklevels = []

for i, heights in enumerate(heightmap):

    for j, height in enumerate(heights):
        surrounding_heights = []
        if j > 0:#Left
            surrounding_heights.append(heightmap[i][j - 1])
        if j < len(heights) - 1:#Right
            surrounding_heights.append(heightmap[i][j + 1])
        if i > 0:#Above
            surrounding_heights.append(heightmap[i - 1][j])
        if i < len(heightmap) - 1:#Below
            surrounding_heights.append(heightmap[i + 1][j])
        
        #Check if lowpoint
        if height < min(surrounding_heights):
            risklevel = height + 1
            risklevels.append(risklevel)
        

total = sum(risklevels)

#Result
print(heightmap)
print(risklevels)
print(total)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
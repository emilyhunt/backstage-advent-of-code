#Advent of code 2021
#Day 9 Part 2
#Smoke Basin

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy
from random import randrange

start_time = time.time()

#Functions
def find_surrounding_heights(heightmap,heigts,i,j):
    #Finds surrounding heights
    surrounding_heights = []
    
    if j > 0:#Left
        surrounding_heights.append(heightmap[i][j - 1])
    if j < len(heights) - 1:#Right
        surrounding_heights.append(heightmap[i][j + 1])
    if i > 0:#Above
        surrounding_heights.append(heightmap[i - 1][j])
    if i < len(heightmap) - 1:#Below
        surrounding_heights.append(heightmap[i + 1][j])
    
    return surrounding_heights

def find_basin_size(i,j,heightmap):
    #Finds the size of a basin around a given lowpoint
    #basinsize = randrange(1000)
    
    #Heightmap size
    dims = heightmap.shape
    
    #Make Heightmap true / false array
    in_basin = np.zeros(dims, dtype=bool)
    in_basin[i][j] = True
    
    basins_identified = 1
    
    
    while basins_identified > 0:
        basins_identified = 0
        
        for m, heights in enumerate(heightmap):
            for n, height in enumerate(heights):
                #Skip if already in basin or equal to 9
                if in_basin[m][n] == True or heightmap[m][n] == 9:
                    continue
                
                #Find if any nearby values are true
                surrounding_in_basin = find_surrounding_heights(in_basin,height, m,n)
                
                #If next to true is part of basin
                if any(surrounding_in_basin) == True:
                    in_basin[m][n] = True
                    basins_identified += 1
    
    #Calc basin size
    basinsize = np.count_nonzero(in_basin)
    
    return basinsize

def find_max_three_product(sizes):
    #Find product of max 3 values in a list
    sizes = sorted(sizes)
    length = len(sizes)
    product = sizes[length - 1] * sizes[length - 2] * sizes[length - 3]
    return product

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
basinsizes = []

for i, heights in enumerate(heightmap):

    for j, height in enumerate(heights):
        
        surrounding_heights = find_surrounding_heights(heightmap,heights,i,j)
        
        #Check if lowpoint
        if height < min(surrounding_heights):
            basinsize = find_basin_size(i,j,heightmap)
            basinsizes.append(basinsize)
            
        

result = find_max_three_product(basinsizes)

#Result
print(heightmap)
print(basinsizes)
print(result)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
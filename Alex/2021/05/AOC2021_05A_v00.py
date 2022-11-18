#Advent of code 2021
#Day 5 Part 1
#Hydrothermal Venture

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Function: Create list of elements from a range
def list_elements(line):
    if line[0][0] == line[1][0]:#Vertical Line
        y_coords = np.array(range(min(line[0][1],line[1][1]),max(line[0][1],line[1][1])+1,1))
        x_coords = np.ones([1,len(y_coords)])*line[0][0]
        x_coords = x_coords[0]
    elif line[0][1] == line[1][1]:#Horizontal Line
        x_coords = np.array(range(min(line[0][0],line[1][0]),max(line[0][0],line[1][0])+1,1))
        y_coords = np.ones([1,len(x_coords)])*line[0][1]
        y_coords = y_coords[0]
    else:#Diagonal Line
        print("Warning: Line is diagonal")
        x_coords = "Error line is diagonal"
        y_coords = "Error line is diagonal"
    
    return x_coords, y_coords

#Function: Add 1 to given co-ordinates in gris
def add_one_grid(x_coords,y_coords,grid):
    j = 0
    for x in x_coords:
        x = int(x)
        y = int(y_coords[j])
        grid[y][x] += 1
        #pdb.set_trace()
        j += 1
    
    return grid

#Import and sort File
vents = []
grid_size = [0,0]

with open("input_05.txt") as ventsf:
    for line in ventsf:
        #Import operations
        
        line = line.strip("/n")#Remove EOL symbol
        
        line = line.split(" -> ")
        
        i = 0
        for entry in line:
            line[i] = entry.split(",")
            line[i] = [ int(x) for x in line[i] ]
            
            #Expand grid if co-ordinate is larger
            if line[i][0] >= grid_size[0]:
                grid_size[0] = line[i][0] + 1
            if line[i][1] >= grid_size[1]:
                grid_size[1] = line[i][1] + 1
            
            i += 1
        
        vents.append(line)

print(grid_size)

###Main Code
#Initilise Grid
grid = np.zeros([grid_size[1],grid_size[0]])
grid = grid.astype(int)

#Loop Through and Apply Vent positions to Grid
i = 0
for line in vents:
    x_coords = []
    y_coords = []
    
    x_coords, y_coords = list_elements(line)
    
    if x_coords == "Error line is diagonal":
        continue
    
    grid = add_one_grid(x_coords,y_coords,grid)
    
    i += 1

#Count number of overlaps
no_of_overlap = len(np.where(grid>1)[0])

#Result
print(vents)
print(grid_size)
print(grid)
print(no_of_overlap)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
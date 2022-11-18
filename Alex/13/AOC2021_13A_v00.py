#Advent of code 2021
#Day 13 Part 2
#Transparent Origami

import numpy as np
np.set_printoptions(threshold=np.inf)
np.set_printoptions( linewidth=np.inf)
import pdb #pdb.set_trace()
import time
import copy
from PIL import Image as im

start_time = time.time()

#Functions
#Performs a fold operation on the grid
def perform_fold(grid,fold):
    if fold[0] == "y":
        axis_setting = 0
    elif fold[0] == "x":
        axis_setting = 1
    
    grids = np.split(grid,[int(fold[1]),int(fold[1])+1],axis = axis_setting)
    staticgrid = grids[0]
    gridtoflip = grids[2]
    flippedgrid = np.flip(gridtoflip,axis_setting)
    
    for x,row in enumerate(staticgrid):
        for y,position in enumerate(row):
            if position == "." and flippedgrid[x][y] == "#":
                staticgrid[x][y] = "#"
    
    return staticgrid

#Import and sort File
points = []
folds = []

with open("input_13.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        if line == "":#Skips blank lines
            continue
        elif line[0] == "f":#Checks it is a fold
            line = line.strip("fold along ")#Remove text
            line = line.split("=")#Remove =
            folds.append(line)#Save Data
        elif line[0].isdigit():#Check if point or fold
            line = line.split(",")#Split co-ordinate
            line[0] = int(line[0])
            line[1] = int(line[1])
            points.append(line)#Save point to data table

points = np.array(points)
folds = np.array(folds)

##Main Code
###GenerateGrid
#Find Grid Size
array_size = np.amax(points, axis = 0)
array_size = array_size[::-1]
array_size += 1
#Make Blank Grid
grid = np.full(array_size,".")

###Populate Grid
for point in points:
    grid[point[1]][point[0]] = "#"

###Execute Folds
#Execute All Folds
for fold in folds:
    grid = perform_fold(grid,fold)

#Create Image
gridimg = np.char.replace(grid,"#","255")
gridimg = np.char.replace(gridimg,".","0")
gridimg = gridimg.astype(int)
print(gridimg)
gridimg = im.fromarray(gridimg)
gridimg.save("result.png")

#Result
print(points)
print(folds)
print(grid)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
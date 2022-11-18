#Advent of code 2021
#Day 15 Part 1
#Chiton

import numpy as np
np.set_printoptions(threshold=np.inf)
np.set_printoptions(linewidth=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Functions
def function(inputs):
    
    return output

#Import and sort File
riskmap = []

with open("input_15.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        line = list(line)
        
        riskmap.append(line)

riskmap = np.array(riskmap)
riskmap = riskmap.astype(np.int)

###Main Code
totalrisk = 0*riskmap

#Calculate Total Risk moving only down or right
for x,row in enumerate(riskmap):
    for y, risk in enumerate(row):
        if x ==0  and y == 0:
            totalrisk[0][0] = 0
            continue
        if x == 0 and y != 0:
            triskup = np.inf
        else:
            triskup = totalrisk[x-1][y] + risk
        if x != 0  and y == 0:
            triskleft = np.inf
        else:
            triskleft = totalrisk[x][y-1] + risk
        
        totalrisk[x][y] = min([triskleft,triskup])

#Check to see if a loop path would be better and repeat
changecounter = 1
while changecounter > 0:
    changecounter = 0
    for x,row in enumerate(riskmap):
        for y, risk in enumerate(row):
            if x == 0  and y == 0:
                continue
            
            if x == 0 and y != 0:
                triskup = np.inf
            else:
                triskup = totalrisk[x-1][y] + risk
            
            if x != 0  and y == 0:
                triskleft = np.inf
            else:
                triskleft = totalrisk[x][y-1] + risk
            
            if y == riskmap.shape[1] - 1:
                triskright = np.inf
            else:
                triskright = totalrisk[x][y+1] + risk
            
            if x == riskmap.shape[0] - 1:
                triskdown = np.inf
            else:
                triskdown = totalrisk[x+1][y] + risk
            
            mintrisk = min([triskleft,triskright,triskup,triskdown])
            
            if mintrisk < totalrisk[x][y]:
                changecounter += 1
                totalrisk[x][y] = mintrisk

#Result
print(riskmap)
print(totalrisk)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
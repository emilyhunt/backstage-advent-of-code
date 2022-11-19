#Advent of code 2021
#Day 17 Part 1
#Trick Shot

import numpy as np
np.set_printoptions(threshold=np.inf)
np.set_printoptions(linewidth=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Functions
def run_flight(v0,target_area):
    #Takes an initial velocity and runs a flight. Outputs if the target_area was hit
    #condition = 0 means undershoot
    #condition = 1 means target hit
    #condition = 2 means overshoot
    #condition = 3 means shoot through
    #condition = 4 means shot for fucking miles
    
    airborne = 1
    pos = [0,0]
    maxheight = 0
    v = copy.deepcopy(v0)
    
    i = 0
    
    while airborne == 1:
        pos[0] += v[0]
        pos[1] += v[1]
        
        if v[0] > 0:
            v[0] -= 1
        v[1] -= 1
        
        #record new max height
        if pos[1] >= maxheight:
            maxheight = pos[1]
        
        if pos[0] >= target_area[0][0] and pos[0] <= target_area[0][1] and pos[1] >= target_area[1][0] and pos[1] <= target_area[1][1]:
            #Target Area Hit
            condition = 1
            airborne = 0
        
        if pos[1] < target_area[1][0] and pos[0] <= target_area[0][1]:
            #Target undershot
            condition = 0
            airborne = 0
        
        if pos[0] > target_area[0][1]:
            #Target overshot
            condition = 2
            airborne = 0
        
        
        
        
        i += 1
        if i > 10000:
            print("Potential recursive loop")
            condition = 4
            airborne = 0
            #pdb.set_trace()
    
    
    return condition, maxheight

#Import and sort File
target_area = []

with open("input_17.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        #remove start
        line = line[15:]
        line = line.split(", y=")
        line[0] = line[0].split("..")
        line[1] = line[1].split("..")
        
        for item in line:
            target_area.append(list(map(int,item)))

###Main Code
vxlist = list(range(0,max(target_area[0])*2))
vylist = list(range(min(target_area[1]),-min(target_area[1])*2))

hitcounter = 0

for vx in vxlist:
    for vy in vylist:
        [condition,maxheight] = run_flight([vx,vy],target_area)
        if condition == 1:
            hitcounter += 1


#Result
print(target_area)
print(hitcounter)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
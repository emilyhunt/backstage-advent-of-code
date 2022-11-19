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
            pdb.set_trace()
    
    
    return condition, maxheight

#Find max vx which hits target
def find_max_vx(target_area,v0):
    
    diditwork = 0
    v_new = copy.deepcopy(v0)
    condition = 0
    maxheight = -9999999
    while condition < 2:
        maxheight_old = maxheight
        v0_old = copy.deepcopy(v_new)
        v_new[0] += 1
        [condition,maxheight] = run_flight(v_new, target_area)
        if condition == 1:
            diditwork = 1
    
    return maxheight_old, v0_old, diditwork
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
v0 = [20,65] # Initial seed

#pdb.set_trace()

#Increase vy until max vx which hits target
diditwork = 1
maxheight_old = -999999
v0_old = copy.deepcopy(v0)
while diditwork == 1:
    maxheight_reallyold = copy.deepcopy(maxheight_old)
    v0_reallyold = copy.deepcopy(v0_old)
    v0[1] += 1
    print(v0)
    [maxheight_old,v0_old,diditwork] = find_max_vx(target_area,v0)
    
    

#Result
print(target_area)
print(maxheight_reallyold)
print(v0_reallyold)
print(diditwork)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
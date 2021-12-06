#Advent of code 2021
#Day 6 Part 2
#Laternfish

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy
import collections

start_time = time.time()

###Functions
#Brute force calcuates the number of fish from one fish starting with an internal timer of one.
#Outputs the number of fish on each day of evolution
def histo_one_day_one_fish(days):
    
    no_of_fish_by_type = [0,1,0,0,0,0,0,0,0]
    no_of_fish_history = []
    
    for day in days:
        breeding_fish_no = no_of_fish_by_type[0]
        no_of_fish_by_type[0:8] = no_of_fish_by_type[1:9]
        no_of_fish_by_type[6] += breeding_fish_no
        no_of_fish_by_type[8] = breeding_fish_no
        
        no_of_fish_history.insert(0,sum(no_of_fish_by_type))
    
    return no_of_fish_history

###Import and sort File
fishes_start = []

with open("input_06.txt") as fishes_startf:
    for line in fishes_startf:
        #Import operations
        
        line = line.strip("/n")#Remove EOL symbol
        
        line = line.split(",")
        
        fishes_start.append(line)

###Main Code
no_of_days = 256
days = list(range(no_of_days))

#Run evolution of one fish starting with an internal timer of one
n_of_fish_growth_history_for_one_day_one_fish = histo_one_day_one_fish(days)

#Count no of fish starting with each internal timer
no_of_each_fish_dict = collections.Counter(tuple(*fishes_start))

#Multiple Number of each type of fish by single fish number and sum
start_fish_types = ['1','2','3','4','5']
number_of_fish = 0
i = 0
for fish_type in start_fish_types:
    no_of_day_x_fish = no_of_each_fish_dict[fish_type]*n_of_fish_growth_history_for_one_day_one_fish[i]
    number_of_fish += no_of_day_x_fish
    
    i += 1


###Result
#print(fishes_start)
#print(days)
#print(n_of_fish_growth_history_for_one_day_one_fish)
#print(no_of_each_fish_dict)
print(number_of_fish)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
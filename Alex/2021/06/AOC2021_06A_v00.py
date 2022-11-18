#Advent of code 2021
#Day 6 Part 1
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
def brute_force_one_day_one_fish(days):
    
    fishes = [1]
    no_of_fish_history = []
    
    for day in days:
        no_of_new_fish_today = 0 
        i = 0
        for fish in fishes:
            
            if fish == 0:
                no_of_new_fish_today += 1
                fishes[i] = 6
            else:
                fishes[i] -= 1
            
            i += 1
        
        #Add newborns from today
        newborns = [8] * no_of_new_fish_today
        fishes.extend(newborns)
        
        #Store number of fish today
        no_of_fish_history.insert(0,len(fishes))
    
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
no_of_days = 80
days = list(range(no_of_days))

#Run evolution of one fish starting with an internal timer of one
n_of_fish_growth_history_for_one_day_one_fish = brute_force_one_day_one_fish(days)

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
print(fishes_start)
print(days)
print(n_of_fish_growth_history_for_one_day_one_fish)
print(no_of_each_fish_dict)
print(number_of_fish)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
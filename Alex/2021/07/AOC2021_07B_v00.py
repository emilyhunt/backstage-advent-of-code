#Advent of code 2021
#Day 7 Part 2
#The Treachery of Whales

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy
from functools import reduce
import math
from decimal import Decimal

start_time = time.time()

###Functions
def calculate_stats_and_shit(positions):
    #Calculate a lot of averages cos why the fuck not.
    #I'm definetly not going to use all of these lol
    #I had fun everything is fine
    #(My RAM might disagree)
    Sigma_x = sum(positions)
    
    Sigma_x2 = reduce(lambda a, x: a + x**2, [0]+positions)
    
    Sigma_x2_minus_x = reduce(lambda a, x: a + x**2 - x, [0]+positions)
    
    no = len(positions)
    no_dec = Decimal(no)
    
    mean = Sigma_x / no
    
    RMS = ((1/no)*Sigma_x2)**0.5
    MRS = (1/no)*(Sigma_x2)**0.5
    
    positions_plus_one = [x+1 for x in positions]
    product_x_plus_one = Decimal(reduce((lambda x, y: x * y), positions_plus_one))
    GM_add_one = product_x_plus_one**(1/no_dec) - 1
    
    positions_wo_zero = [i for i in positions if i != 0]
    no_wo_zero = Decimal(len(positions_wo_zero))
    product_x_wo_zero = Decimal(reduce((lambda x, y: x * y), positions_wo_zero))
    GM_ignore_zero = product_x_wo_zero**(1/no_wo_zero)
    
    positions_zero_to_one = [i if i != 0 else 1 for i in positions]
    product_x_zero_to_one = Decimal(reduce((lambda x, y: x * y), positions_zero_to_one))
    GM_zero_to_one = product_x_zero_to_one**(1/no_dec)
    return mean, RMS, MRS, GM_add_one, GM_ignore_zero, GM_zero_to_one

def calc_fuel_needed(positions, x):
    total_fuel = 0
    for position in positions:
        distance = abs(position - x)
        fuel = 0
        for num in range(1, distance + 1, 1):
            fuel += num
        total_fuel += fuel
    return total_fuel

#Import and sort File
positions = []

with open("input_07.txt") as positionsf:
    for line in positionsf:
        #Import operations
        
        line = line.strip("/n")#Remove EOL symbol
        
        line = line.split(",")
        
        positions = list(map(int,line))

positions.sort()

###Main Code
mean, RMS, MRS, GM_add_one, GM_ignore_zero, GM_zero_to_one = calculate_stats_and_shit(positions)

#Mean of the Geometric Means
MoGMs = (GM_add_one + GM_ignore_zero + GM_zero_to_one) / 3

#Find to nearest integers
x_lower = int(math.floor(mean))
x_upper = x_lower + 1

#Calculate fuel for nearest integers
total_fuel_lower = calc_fuel_needed(positions, x_lower)
total_fuel_upper = calc_fuel_needed(positions, x_upper)

#Find nearest local minima
#Direction To Search
if total_fuel_lower < total_fuel_upper:
    search_dir = -1
elif total_fuel_lower > total_fuel_upper:
    search_dir = 1
else:
    print('lol that shouldnt happen, fuck this')

i = 0
while (time.time() - start_time) <= 5*60:
    x_lower += search_dir
    x_upper += search_dir
    total_fuel_lower = calc_fuel_needed(positions, x_lower)
    total_fuel_upper = calc_fuel_needed(positions, x_upper)
    
    i += 1
    
    if (total_fuel_lower > total_fuel_upper and search_dir == -1):
        x = x_upper
        total_fuel = total_fuel_upper
        break
    
    if (total_fuel_lower < total_fuel_upper and search_dir == 1):
        x = x_lower
        total_fuel = total_fuel_lower
        break


#Result
print('Input positions are ',positions)
print('Mean is ',mean)
print('Root Mean Square is ',RMS)
print('Mean Root Square is ',MRS)
print('Geometric Mean using the add one to all method is ',GM_add_one)
print('Geometric Mean using the ignore zero method is ',GM_ignore_zero)
print('Geometric Mean using the convert zero to one method is ',GM_zero_to_one)
print('The Mean of the Geometric Means is ',MoGMs)
print('.......')
print('.......')
print('.......')
print('Well that was a lot of silly data')
print('maybe you might like some results now')
print('.......')
print('.......')
print('.......')
print('maybe')
print('.......')
print('.......')
print('.......')
print('The best place for the crab subs to meet is ',x)
print('The fuel usage required for that is ',total_fuel)
print('I did ',i,' loops to find the local optima')

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
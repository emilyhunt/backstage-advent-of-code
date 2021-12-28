#Advent of code 2021
#Day 11 Part 1
#Dumbo Octopus

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Functions
def flash_octopus(energy_levels,line,x,y):
	#Finds surrounding and increments by 1
	if x > 0 and y > 0:#Top Left
		tl = energy_levels[x - 1][y - 1]
		if tl > 0:
			energy_levels[x - 1][y - 1] += 1
	if x > 0:#Top Middle
		tm = energy_levels[x - 1][y]
		if tm > 0:
			energy_levels[x - 1][y] += 1
	if x > 0 and y+1 < len(line):#Top Right
		tr = energy_levels[x - 1][y + 1]
		if tr > 0:
			energy_levels[x - 1][y + 1] += 1
	
	if y > 0:#Left
		l = energy_levels[x][y - 1]
		if l > 0:
			energy_levels[x][y - 1] += 1
	if y+1 < len(line):#Right
		r = energy_levels[x][y + 1]
		if r > 0:
			energy_levels[x][y + 1] += 1
			
	if x+1 < len(energy_levels) and y > 0:#Bottom Left
		bl = energy_levels[x + 1][y - 1]
		if bl > 0:
			energy_levels[x + 1][y - 1] += 1
	if x+1 < len(energy_levels):#Bottom Middle
		bm = energy_levels[x + 1][y]
		if bm > 0:
			energy_levels[x + 1][y] += 1
	if x+1 < len(energy_levels) and y+1 < len(line):#Bottom Right
		br = energy_levels[x + 1][y + 1]
		if br > 0:
			energy_levels[x + 1][y + 1] += 1
	
	return energy_levels

def add_one_to_all(energy_levels):
	for x, line in enumerate(energy_levels):
		for y, octupus in enumerate(line):
			energy_levels[x][y] += 1
	
	return energy_levels

#Import and sort File
energy_levels = []

with open("input_11.txt") as energy_levelsf:
	for line in energy_levelsf:
		#Import operations
		
		line = line.strip("\n")#Remove EOL symbol
		
		line = list(map(int,line))
		
		energy_levels.append(line)

energy_levels = np.array(energy_levels)

###Main Code
no_flash = 0
steps = 100

i = 0
while i < steps:
	
	#add 1
	energy_levels = add_one_to_all(energy_levels)
	
	#Flash all nines and set to zero
	no_flash_old = no_flash - 1
	while no_flash_old < no_flash:
		no_flash_old = no_flash
		for x, line in enumerate(energy_levels):
			for y, octopus in enumerate(line):
				if octopus > 9:
					no_flash += 1
					energy_levels = flash_octopus(energy_levels,line,x,y)
					energy_levels[x][y] = 0
	
	
	i += 1


#Result
print(energy_levels)
print(no_flash)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
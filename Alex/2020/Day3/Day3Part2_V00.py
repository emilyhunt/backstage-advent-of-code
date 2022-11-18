#Advent of code 2020
#Day 3 Part 2
#Avoiding Trees

import numpy
import pdb #pdb.set_trace()
import time

def slideDownHill(map,width,length,dx,dy):
	#Initial Position
	x = 0 #d accross hill
	y = 0 #d down hill
	
	#Counters
	numspace = 0
	numtree = 0
	
	while y < length:
		#pdb.set_trace()
		#Deal with map end
		if x>=width:
			x = x-width
		
		#Find object
		object = map[y][x]
		
		#Record result
		if object =="#":
			numtree = numtree + 1
		else:
			numspace = numspace + 1
		
		#Move onto next position
		x = x + dx
		y = y + dy
	
	#Output Results
	return numtree, numspace



#Import and sort File
map = numpy.genfromtxt("input_day3.txt", dtype='str', delimiter="\n", comments=" ")

#Hill size
width = len(map[0])
length = len(map)

#Define Trajectories
Trajectories = [[1,1],[3,1],[5,1],[7,1],[1,2]]

#Run Trajectories
i = 0
for i in Trajectories:
	#Get Movement
	dx = i[0]
	dy = i[1]
	
	#Run Simulation
	hits = slideDownHill(map,width,length,dx,dy)
	print("Trajectory ",i," found ",hits[0]," trees and ",hits[1]," blank tiles")
	

#Result
#print(numtree)
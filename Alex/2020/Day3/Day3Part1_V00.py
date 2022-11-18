#Advent of code 2020
#Day 3 Part 1
#Avoiding Trees

import numpy
import pdb #pdb.set_trace()
import time


#Import and sort File
map = numpy.genfromtxt("input_day3.txt", dtype='str', delimiter="\n", comments=" ")

#Movement
dy = 1
dx = 3

#Hill size
width = len(map[0])
length = len(map)

#Initial Position
x = 0 #d accross hill
y = 0 #d down hill

#Counters
numspace = 0
numtree = 0

#Move Down Hill
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

#Result
print(numtree)
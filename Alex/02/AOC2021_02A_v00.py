#Advent of code 2021
#Day 2 Part 1
#Dive!

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Import and sort File
course = []

with open("input_02.txt") as coursef:
    for line in coursef:
        #Import operations
        
        line = line[:-1]#Remove EOL symbol
        line = line.split(" ")#split up based on spaces
        line[1] = int(line[1])#convert string to integer
        
        course.append(line)

#Main Code
#course = np.array(course)#convert nested list to array

#starting position
horizontal = 0
depth = 0

#Follow course
for line in course:
    if line[0] == "forward":#move forward
        horizontal += line[1]
    elif line[0] == "backward":#move backward
        horizontal += line[1]
    elif line[0] == "down":#move down
        depth += line[1]
    elif line[0] == "up":#move up
        depth -= line[1]

product = horizontal * depth

#Result
print(course)
print(horizontal)
print(depth)
print(product)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
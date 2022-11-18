#Advent of code 2020
#Day 5 Part 1
#Boarding Pass validation

import numpy
import pdb #pdb.set_trace()
import time

start_time = time.time()

#Import and sort File
manifest = []
with open("input_day5.txt") as manifestf:

	for line in manifestf:
		linebinary = line.replace("F","0")
		linebinary = linebinary.replace("B","1")
		linebinary = linebinary.replace("L","0")
		linebinary = linebinary.replace("R","1")
		row = int(linebinary[0:7],2)
		column = int(linebinary[7:10],2)
		seatno = row * 8 + column
		rowcolseat = [row, column, seatno]
		manifest.append(rowcolseat)

#Find max seat no
manifest = numpy.array(manifest)
maxseatno = max(manifest[:,[2]])

#Result
print(manifest)
print(maxseatno)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
#Advent of code 2020
#Day 5 Part 2
#Boarding Pass validation

import numpy
numpy.set_printoptions(threshold=numpy.inf)
import pdb #pdb.set_trace()
import time

start_time = time.time()

#Make Seatmap
seatmap = numpy.array([[0 for col in range(8)] for row in range(128)])

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
		seatmap[row,column] = 1
		#pdb.set_trace()

#Find max seat no
manifest = numpy.array(manifest)
maxseatno = max(manifest[:,[2]])

#Find empty seat
i = 0
for row in seatmap:
	if sum(row) == 7:
		print(row)
		pdb.set_trace()
		continue
	else:
		i = i + 1

#Result
print(manifest)
print(maxseatno)
print(seatmap)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
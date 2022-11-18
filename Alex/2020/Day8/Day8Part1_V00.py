#Advent of code 2020
#Day 7 Part 2
#Airline Baggage

import numpy
numpy.set_printoptions(threshold=numpy.inf)
import pdb #pdb.set_trace()
import time

start_time = time.time()

#def name(inputs):
#	#
#	return outputs

#Import and sort File
instructions = []

with open("input_day8_test.txt") as instructionsf:
	for line in instructionsf:
		#Import operations
		line = line.split(" ")
		
		operation = line[0]#Type of operation
		value = int(line[1])#Quantity of operation
		executed = 0#Number of times exercuted
		
		instructions.append([operation, value, executed])

#Main Code
i = 0#InsNumber
count = 0
while executed == 0:
	instruction = instructions[i]
	operation = instruction[0]
	value = instruction[1]
	executed = instruction[2]
	
	instructions[i][2] = 1#
	
	#pdb.set_trace()
	
	if operation == 'nop':
		i += 1
	elif operation == 'acc':
		count += value
		i += 1
	elif operation == 'jmp':
		i += value
	elif operation == 'end':
		break
	else:
		raise Exception("Instruction not valid")
	
	#print(operation+"    "+str(value)+"     "+str(count)+"      "+str(executed))
	#pdb.set_trace()

#Reverse Last op if acc
if operation == 'acc':
	count -= value

#Result
print(instructions)
print(count)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
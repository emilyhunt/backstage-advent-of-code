#Advent of code 2020
#Day 7 Part 2
#Airline Baggage

import numpy
numpy.set_printoptions(threshold=numpy.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

def runbootcode(instructions):
	
	localins = copy.deepcopy(instructions)
	#if localins[7][0] == 'nop':
	#pdb.set_trace()
	
	output = ['',0]
	
	i = 0#InsNumber
	count = 0
	executed = 0
	operation = ''
	while executed == 0 and operation !='end':
		instruction = localins[i]
		operation = instruction[0]
		value = instruction[1]
		executed = instruction[2]
		
		#pdb.set_trace()
		localins[i][2] = 1#
		
		#pdb.set_trace()
		
		if operation == 'nop':
			i += 1
		elif operation == 'acc':
			count += value
			i += 1
		elif operation == 'jmp':
			i += value
		elif operation == 'fin':
			break
		else:
			raise Exception("Instruction not valid")
		
		if localins[7][0] == 'nop':
			print(operation+"   "+str(value)+"   "+str(count)+"   "+str(executed))
			#pdb.set_trace()
	
	if executed == 1:
		output[0] = 'fail'
	elif operation == 'fin':
		output[0] = 'pass'
	
	output[1] = count
	
	return output

#Import and sort File
instructions = []

with open("input_day8.txt") as instructionsf:
	for line in instructionsf:
		#Import operations
		line = line.split(" ")
		
		operation = line[0]#Type of operation
		value = int(line[1])#Quantity of operation
		executed = 0#Number of times exercuted
		
		instructions.append([operation, value, executed])

#Main Code
k = 0
for line in instructions:
	#pdb.set_trace()
	if line[0] == 'acc':
		k += 1
		continue
	elif line[0] == 'nop':
		instructions[k][0] = 'jmp'
		#test new boot code
		result = runbootcode(instructions)
		if result[0] == 'fail':
			instructions[k][0] = 'nop'
		elif result[0] == 'pass':
			count = result[1]
			break
		else:
			raise Exception("Test not passed or failed_1")
	elif line[0] == 'jmp':
		instructions[k][0] = 'nop'
		#test new boot code
		result = runbootcode(instructions)
		if result[0] == 'fail':
			instructions[k][0] = 'jmp'
		elif result[0] == 'pass':
			count = result[1]
			break
		else:
			raise Exception("Test not passed or failed_2")
	k += 1

#Result
#print(instructions)
pdb.set_trace()
print(count)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
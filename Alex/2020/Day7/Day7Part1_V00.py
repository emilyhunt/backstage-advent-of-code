#Advent of code 2020
#Day 7 Part 1
#Airline Baggae

import numpy
numpy.set_printoptions(threshold=numpy.inf)
import pdb #pdb.set_trace()
import time

start_time = time.time()

#Function
def findcontainers(searchbag,rules,containers):
	for rule in rules:
		if rule[0] == searchbag:
			continue
		else:
			for item in rule[1:]:
				if item[2:] == searchbag and rule[0] not in containers:
					containers.append(rule[0])
	
	return containers

#Import and sort File
rules = []
j = 0

with open("input_day7.txt") as rulesf:
	for line in rulesf:
		#I
		line = line[:-2]
		line = line.split(" contain ")
		bag = line[0][:-5]
		contents = line[1].replace(' bags','')
		contents = contents.replace(' bag','')
		contents = contents.split(", ")
		
		entry = []
		entry.append(bag)
		for i in contents:
			entry.append(i)
		
		rules.append(entry)
		j = j+1
		#pdb.set_trace()

#Find shiny gold containers
containers = ["shiny gold"]

#Find containers of containers
l = 0
while l < len(containers):
	l = len(containers)
	for searchbag in containers:
		containers = findcontainers(searchbag,rules,containers)
		#pdb.set_trace()


#Result
#print(rules)
print(containers)
print(l - 1)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
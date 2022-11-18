#Advent of code 2020
#Day 7 Part 2
#Airline Baggage

import numpy
numpy.set_printoptions(threshold=numpy.inf)
import pdb #pdb.set_trace()
import time
from anytree import Node, RenderTree
import re

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

def findbags(searchbag,rules):
	newcontents = []
	for rule in rules:
		if rule[0] == searchbag:
			for item in rule[1:]:
				#if item != 'no other':
				#	#print(item)
				newcontents.append(item)
	
	return newcontents

def strip(child):
	#Strips child (or parents) of number and space
	strippedchild = child[2:].replace(" ","")
	return strippedchild

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

#print(rules)
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

#Starting searchbag
searchbags = ['1 shiny gold']

#Starttree
bagdict = {'shinygold':Node('1 shiny gold')}
#bagdictnum = {'shinygold':Node('1')}

#Init value
contents = []

while contents != ['no other']:
	for searchbag in searchbags:#For loop to search deeper
		#pdb.set_trace()
		contents = findbags(searchbag[2:],rules)#Level below search term
		if contents == ['no other']:#End statement
			break
		elder = strip(searchbag)
		for item in contents:#Stores level below as tree
			bagdict |= {strip(item):Node(item,parent=bagdict[elder])}
			#bagdictnum |= {strip(item):Node(item[0],parent=bagdictnum[elder])}
	searchbags = contents
	#pdb.set_trace()

#Result
#print(rules)
#print(containers)
print("Number of bags containing shiny gold " + str(l - 1))
#print(contents)
#print(newcontents)
count = 0#Number of bags
for pre, fill, node in RenderTree(bagdict['shinygold']):
	print("%s%s" % (pre, node.name))#Display Tree
	#pdb.set_trace()
	if str(node.parent) != 'None':
		product = 1
		nums = re.sub("[^0-9]","",str(node.parent))
		for num in nums:
			product *= int(num)
		product *= int(node.name[0])
		count += product
		#print(count)
	#pdb.set_trace()

print(count," bags in shiny gold")

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
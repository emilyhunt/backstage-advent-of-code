#Advent of code 2020
#Day 7 Part 2
#Airline Baggage

import numpy
numpy.set_printoptions(threshold=numpy.inf)
import pdb #pdb.set_trace()
import time
from anytree import Node, RenderTree
import re
from anytree.exporter import DotExporter
import graphviz
import pydot

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

def printtree(RenderTree):
	for pre, fill, node in RenderTree(bagdict['shinygold']):
		print("%s%s" % (pre, node.name))#Display Tree
	return

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
m = 0

while m != len(bagdict):
	m = len(bagdict)
	fullcontents = []
	for searchbag in searchbags:#For loop to search deeper
		#if searchbag[-2:] == '_A':
			#pdb.set_trace()
		#pdb.set_trace()
		contents = findbags(searchbag[2:].replace('_A',''),rules)#Level below search term
		#if fullcontents == ['no other']:#End statement
		#	break
		elder = strip(searchbag)
		k = 0
		for item in contents:#Stores level below as tree
			strippeditem = strip(item)
			if strippeditem != 'shinygold' and item != 'no other':
				test = 0 
				while test == 0:
					try:
						bagdict[strippeditem]
					except KeyError:
						test = 1
						pass
					else:
						#pdb.set_trace()
						strippeditem = strippeditem + '_A'
						item = item + '_A'
						contents[k] = item
			bagdict |= {strippeditem:Node(item,parent=bagdict[elder])}
			#bagdictnum |= {strip(item):Node(item[0],parent=bagdictnum[elder])}
			k += 1
		for content in contents:
			fullcontents.append(content)
		#pdb.set_trace()
	searchbags = fullcontents
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
	if str(node.parent) != 'None' and str(node.name) != 'no other':
		product = 1
		nums = re.sub("[^0-9]","",str(node.parent))
		for num in nums:
			product *= int(num)
		product *= int(node.name[0])
		count += product
		#print(count)
	#pdb.set_trace()

DotExporter(bagdict['shinygold']).to_dotfile("shinygold.dot")
(graph,) = pydot.graph_from_dot_file("shinygold.dot")
graph.write_png("shinygold.png")

print(count," bags in shiny gold")

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
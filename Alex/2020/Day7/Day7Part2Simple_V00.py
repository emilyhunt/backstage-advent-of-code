#Advent of code 2020
#Day 7 Part 2
#Airline Baggage
#Simple test version00

import numpy
numpy.set_printoptions(threshold=numpy.inf)
import pdb #pdb.set_trace()
import time
from anytree import Node, RenderTree

def findbags(searchbag,rules):
	#Finds contents of a bag as per the book of rules
	newcontents = []
	for rule in rules:
		if rule[0] == searchbag:
			for item in rule[1:]:
				newcontents.append(item)
	
	return newcontents

def strip(child):
	#Strips child (or parents) of number and space
	strippedchild = child[2:].replace(" ","")
	return strippedchild

#Input rules data (pre-processed)
rules = [['light red', '1 bright white', '2 muted yellow'], ['dark orange', '3 bright white', '4 muted yellow'], ['bright white', '1 shiny gold'], ['muted yellow', '2 shiny gold', '9 faded blue'], ['shiny gold', '1 dark olive', '2 vibrant plum'], ['dark olive', '3 faded blue', '4 dotted black'], ['vibrant plum', '5 faded blue', '6 dotted black'], ['faded blue', 'no other'], ['dotted black', 'no other']]

#Starting searchbag
searchbags = ['1 shiny gold']

#Starttree
bagdict = {'shinygold':Node('1 shiny gold')}

contents = []

while contents != ['no other']:
	for searchbag in searchbags:
		contents = findbags(searchbag[2:],rules)
		print(contents)
		elder = strip(searchbag)
		for item in contents:
			strippeditem = strip(item)
			bagdict[strippeditem] = Node(item,parent=bagdict[elder])
	searchbags = contents




#Output
for pre, fill, node in RenderTree(bagdict['shinygold']):
	print("%s%s" % (pre, node.name))



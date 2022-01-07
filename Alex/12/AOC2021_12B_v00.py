#Advent of code 2021
#Day 12 Part 1
#Passage Pathing

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy
from collections import Counter

#Start Timer
start_time = time.time()

#Functions
def assign_edge(node1,node2,positive_bool,nodesdict):
	#Takes an edge and popuated the dict of nodes with it
	if positive_bool == False:
		start = node2
		end = node1
	else:
		start = node1
		end = node2
	
	#Assign edge in positive direction
	if start in nodesdict:
		#Assign to existing dict entry (if not already)
		existing_entry = nodesdict[start]
		
		#Check if there already, If not add to dict entry
		if not end in existing_entry:
			new_entry = existing_entry.append(end)
		
	else:
		#Make new dict entry
		nodesdict[start] = [end]
	
	return nodesdict

def make_dict_of_nodes(edges):
	#Takes a list of edges and makes a map of nodes
	nodesdict = {}
	
	for edge in edges:
		start = edge[0]
		end = edge[1]
		
		#Assign edge
		nodesdict = assign_edge(start,end,True,nodesdict)#Positive
		nodesdict = assign_edge(start,end,False,nodesdict)#Negitive
	
	return nodesdict

def can_i_visit_this_small_cave(small_cave,path_count):
	#Evaluates if I can visit the small cave
	#Condition 1: can only visit each small cave once per path
	#Exception 1: may visit one of the small caves a 2nd time per path
	
	visit_small_cave_bool = ''
	
	#Find if a small cave has been visited
	if small_cave in path_count:
		#Small cave has been visited
		#Check to see if another small cave has been visited twice. If not we can visit again
		for cave in path_count:
			cave_occurances = path_count[cave]
			if cave.islower() is True and cave_occurances >= 2:
				#Another cave has been visited twice. We cannot visit our small cave again.
				visit_small_cave_bool = False
		
		if visit_small_cave_bool == '':
			#no other small cave has occured twice. We may visit this one again.
			visit_small_cave_bool = True
		
	else:
		#Small cave has not been visited. You may visit it
		visit_small_cave_bool = True
	
	
	
	return visit_small_cave_bool




def produce_new_paths(path,nodesdict,paths,path_count):
	#Produce new paths from path
	
	new_paths = []
	
	connected_nodes = nodesdict[path[-1]]
	
	for node in connected_nodes:
		if node == 'start':
			continue
		
		if node.islower() is True:
			visit_small_cave_bool = can_i_visit_this_small_cave(node,path_count)
			
			if visit_small_cave_bool == False:
				continue
		
		new_path = path + [node]
		
		if new_path in paths:
			continue
		else:
			new_paths.append(new_path)
		
	
	return new_paths

def check_all_paths_are_ended(paths):
	
	end_nodes = []
	
	for path in paths:
		if path[-1] == 'end':
			end_nodes.append(True)
		else:
			end_nodes.append(False)
	
	bool = all(end_nodes)
	
	return bool

def find_all_small_town_x1_paths(nodesdict):
	
	paths = [['start']]
	len_paths_old = 0
	
	while check_all_paths_are_ended(paths) is False:
		len_paths_old = len(paths)
		
		new_paths = []
		
		for path in paths:
			if path[len(path)-1] == 'end':
				new_paths = new_paths + [path]
				continue
			
			#Count occurances of caves in path
			path_count = Counter(path)
			
			paths_found = produce_new_paths(path,nodesdict,paths,path_count)
			new_paths = new_paths + paths_found
			
			
			
			
		paths = new_paths
	
	return paths


#Import and sort File
edges = []

with open("input_12.txt") as edgesf:
	for line in edgesf:
		#Import operations
		
		line = line.strip("\n")#Remove EOL symbol
		
		line = line.split("-")#Split start / end of edge
		
		edges.append(line)

###Main Code
#Make graph of nodes
nodesdict = make_dict_of_nodes(edges)

#Start at start node and progress through graph recording unique paths
paths = find_all_small_town_x1_paths(nodesdict)

#Count paths
no_of_unique_paths = len(paths)

#Result
print(edges)
print(nodesdict)
print(paths)
print(no_of_unique_paths)

#Time Code
timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
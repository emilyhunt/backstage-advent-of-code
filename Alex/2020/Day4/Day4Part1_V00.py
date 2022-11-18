#Advent of code 2020
#Day 4 Part 1
#Passport validation

import numpy
import pdb #pdb.set_trace()
import time

start_time = time.time()

#Import and sort File
database = []
with open("input_day4.txt") as databasef:
	i = 0 #RecordNo
	record = [] #Initial Record
	for line in databasef:
		
		#database[i].append(line)
		if line == "\n":
			record = sorted(record)
			database.append(record)
			record = []
		else:
			linenoeol = line.replace("\n","")
			linesplit = linenoeol.split(" ")
			for j in linesplit:
				record.append(j)
	
	#Store Final Record
	record = sorted(record)
	database.append(record)
	record = []

#Counters
numvalid = 0
numpassport = 0
numnpc = 0
numinvalid = 0

#Evaluate each record
for k in database:
	passport = []
	#Check length
	if len(k) <= 6 or len(k) >= 9:
		numinvalid += 1
		continue
	
	#Check byr record
	if k[0][0:3] != "byr":
		numinvalid += 1
		continue
	
	#Check cid record validity
	if len(k) == 8:
		passport = 1
		if k[1][0:3] != "cid":
			numinvalid += 1
			continue
	else:
		passport = 0
	
	#Check ecl validity
	if k[1+passport][0:3] != "ecl":
		numinvalid += 1
		continue
	
	#Check eyr validity
	if k[2+passport][0:3] != "eyr":
		numinvalid += 1
		continue
	
	#Check hcl validity
	if k[3+passport][0:3] != "hcl":
		numinvalid += 1
		continue
	
	#Check hgt validity
	if k[4+passport][0:3] != "hgt":
		numinvalid += 1
		continue
	
	#Check iyr validity
	if k[5+passport][0:3] != "iyr":
		numinvalid += 1
		continue
	
	#Check pid validity
	if k[6+passport][0:3] != "pid":
		numinvalid += 1
		continue
	
	numvalid += 1
	if passport == 1:
		numpassport += 1
	else:
		numnpc += 1
	
	
	

#Result
print("Number valid: ",numvalid,". Number invalid: ",numinvalid,". Number passport: ",numpassport,". Number NPC: ",numnpc)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
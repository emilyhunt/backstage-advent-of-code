#Advent of code 2020
#Day 4 Part 2
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
err = 0

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
	elif int(k[0][4:len(k[0])]) < 1920 or int(k[0][4:len(k[0])]) > 2002:
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
	validEcls = {"amb","blu","brn","gry","grn","hzl","oth"}
	if k[1+passport][0:3] != "ecl":
		numinvalid += 1
		continue
	elif len(k[1+passport]) != 7:
		numinvalid += 1
		continue
	elif k[1+passport][4:len(k[1+passport])] not in validEcls:
		numinvalid += 1
		continue
	
	#Check eyr validity
	if k[2+passport][0:3] != "eyr":
		numinvalid += 1
		continue
	elif int(k[2+passport][4:len(k[2+passport])]) < 2020 or int(k[2+passport][4:len(k[2+passport])]) > 2030:
		numinvalid += 1
		continue
	
	#Check hcl validity
	hclrstr = k[3+passport][5:7]
	hclgstr = k[3+passport][7:9]
	hclbstr = k[3+passport][9:len(k[3+passport])]
	try:
		hclr = int(hclrstr,16)
		hclg = int(hclgstr,16)
		hclb = int(hclbstr,16)
	except:
		numinvalid += 1
		err=1
		pass
	
	if k[3+passport][0:3] != "hcl":
		numinvalid += 1
		continue
	elif err == 1:
		err = 0
		continue
	elif hclr < 0 or hclr > 255:
		numinvalid += 1
		continue
	elif hclg < 0 or hclg > 255:
		numinvalid += 1
		continue
	elif hclb < 0 or hclb > 255:
		numinvalid += 1
		continue
	elif len(k[3+passport]) != 11:
		numinvalid += 1
		continue
	
	#Check hgt validity
	hgt = int(k[4+passport][4:(len(k[4+passport])-2)])
	unit = k[4+passport][(len(k[4+passport])-2):len(k[4+passport])]
	if k[4+passport][0:3] != "hgt":
		numinvalid += 1
		continue
	elif unit == "cm":
		if hgt < 150 or hgt > 193:
			numinvalid += 1
			continue
	elif unit == "in":
		if hgt < 59 or hgt > 76:
			numinvalid += 1
			continue
	else:
		numinvalid += 1
		continue
	
	#Check iyr validity
	iyr = int(k[5+passport][4:len(k[5+passport])])
	if k[5+passport][0:3] != "iyr":
		numinvalid += 1
		continue
	elif iyr < 2010 or iyr > 2020:
		numinvalid += 1
		continue
	
	#Check pid validity
	pidstr = k[6+passport][4:len(k[6+passport])]
	try:
		pid = int(pidstr)
	except:
		numinvalid += 1
		err=1
		pass
	if k[6+passport][0:3] != "pid":
		numinvalid += 1
		continue
	elif err == 1:
		err = 0
		continue
	elif len(pidstr) != 9:
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
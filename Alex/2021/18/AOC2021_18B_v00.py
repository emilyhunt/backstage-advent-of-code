#Advent of code 2021
#Day 18 Part 1
#Snailfish

import numpy as np
np.set_printoptions(threshold=np.inf)
np.set_printoptions(linewidth=np.inf)
import pdb #pdb.set_trace()
import time
import copy
import ast

start_time = time.time()

#Functions
def dive(sfno):
    #Dives into a snailfish number and produces a list of numbers and what depth they are at
    depthlist = []
    numberlist = []
    depth = 0
    for i,char in enumerate(sfno):
        if char == "[":
            depth += 1
        elif char == "]":
            depth -= 1
        elif char.isnumeric():
            if sfno[i-1].isnumeric():
                numberlist[len(numberlist)] += char
            else:
                depthlist.append(depth)
                numberlist.append(char)
    
    numberlist = list(map(int,numberlist))
    
    return depthlist, numberlist

def reduce(depthlist,numberlist):
    #Reduces a snailfish number down fully
    
    maxdepth = max(depthlist)
    maxvalue = max(numberlist)
    
    while maxdepth > 4 or maxvalue > 9:
        #print("DL ",depthlist)
        #print("NL ",numberlist)
        
        #Perform explode operations
        if maxdepth > 4:
            [depthlist,numberlist] = explode(depthlist,numberlist)
            
            maxdepth = max(depthlist)
            maxvalue = max(numberlist)
            
        else:
            #Perform single split operation
            if maxvalue > 9:
                [depthlist,numberlist] = split(depthlist,numberlist)
            
            maxdepth = max(depthlist)
            maxvalue = max(numberlist)
    
    return depthlist,numberlist

def explode(depthlist,numberlist):
    #Performs a single explode on the first level 5 pair in a sfno
    
    for i,depth in enumerate(depthlist):
        if depth > 4:
            #if i + 1 == len(depthlist):
            #    pdb.set_trace()
            
            if i != 0:
                numberlist[i-1] += numberlist[i]
            
           
            if i + 2 < len(depthlist):
                numberlist[i+2] += numberlist[i+1]
                
            numberlist[i] = 0
            depthlist[i] -= 1
            
            del numberlist[i+1]
            del depthlist[i+1]
            
            break
    
    return depthlist,numberlist

def split(depthlist,numberlist):
    #Splits first number >9 in a sfno
    
    for i,value in enumerate(numberlist):
        if value > 9:
            
            #Perform a split
            vl = int(value/2)
            if value - 2*vl > 0:
                vr = int(value/2) + 1
            else:
                vr = vl
            
            numberlist.insert(i,vl)
            depthlist.insert(i,depthlist[i]+1)
            numberlist[i+1] = vr
            depthlist[i+1] = depthlist[i]
            
            break
    
    return depthlist,numberlist

def find_magnitude(depthlist,numberlist):
    #Finds the magnitude of a sfno
    length = len(numberlist)
    
    while length > 1:
        maxdepth = max(depthlist)
        
        for i,depth in enumerate(depthlist):
            if depth == maxdepth:
                magnitude = 3*numberlist[i] + 2* numberlist[i+1]
                
                del numberlist[i+1]
                del depthlist[i+1]
                
                numberlist[i] = magnitude
                depthlist[i] -= 1
                
                break
        
        length = len(numberlist)
    
    return magnitude


#Import and sort File
trial = []

with open("input_18_trial.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        #line = ast.literal_eval(line)
        
        trial.append(line)

trialmarks = []

with open("input_18_trialmarks.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        #line = ast.literal_eval(line)
        
        trialmarks.append(line)

test = []

with open("input_18_test.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        #line = ast.literal_eval(line)
        
        test.append(line)

testmarks = []

with open("input_18_testmarks.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        #line = ast.literal_eval(line)
        
        testmarks.append(line)

test2 = []

with open("input_18_test2.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        #line = ast.literal_eval(line)
        
        test2.append(line)

test3 = []

with open("input_18_test3.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        #line = ast.literal_eval(line)
        
        test3.append(line)

hw = []

with open("input_18.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        #line = ast.literal_eval(line)
        
        hw.append(line)

magtrial = []

with open("input_18_magtrial.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        #line = ast.literal_eval(line)
        
        magtrial.append(line)

magtrialmarks = []

with open("input_18_magtrialmarks.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        #line = ast.literal_eval(line)
        
        magtrialmarks.append(line)

###Reduction Trial Code
for i,sfno in enumerate(trial):
    print("begin new trial")
    print("")
    [depthlist, numberlist] = dive(sfno)
    [depthlist_answer, numberlist_answer] = dive(trialmarks[i])
    print("SFNO is ",sfno)
    maxdepth = max(depthlist)
    print("Depthlist is ",depthlist)
    print("Numberlist is ",numberlist)
    print("Max depth is ",maxdepth)
    print("Begin reduction")
    [depthlist, numberlist] = reduce(depthlist, numberlist)
    print("Reduced depthlist is ",depthlist)
    print("Correct answer is ",depthlist_answer)
    print("Reduced number list is ",numberlist)
    print("Correct answer is ",numberlist_answer)
    maxdepth = max(depthlist)
    print("Max depth is ",maxdepth)
    if depthlist_answer == depthlist and numberlist_answer == numberlist:
        print("reduction of sfnos was correct")
    else:
        print("reduction of sfnos was wrong")
        pdb.set_trace()
    print("")

###Mag Trial Code
for i,sfno in enumerate(magtrial):
    print("Start new magnitude trial")
    print("")
    [depthlist, numberlist] = dive(sfno)
    magnitude = find_magnitude(depthlist, numberlist)
    print("Magnitude is ",magnitude)
    magnitude_answer = int(magtrialmarks[i])
    print("Magnitude answer is ",magnitude_answer)
    if magnitude_answer == magnitude:
        print("magnitude was correct")
    else:
        print("magnitude was wrong")
        pdb.set_trace()
    print("")

###Homework Test Code 3
print("begin the test")
print("")
#Dive into each sfno
listofdepthlists = []
listofnumberlists = []
for sfno in test3:
    [depthlist, numberlist] = dive(sfno)
    listofdepthlists.append(depthlist)
    listofnumberlists.append(numberlist)

#Add the first 2 sfnos in the test list until there is only 1 sfno left
length = len(listofnumberlists)
i = 0
while length > 1:
    numberlist = listofnumberlists[0] + listofnumberlists[1]
    depthlist = listofdepthlists[0] + listofdepthlists[1]
    depthlist = [x+1 for x in depthlist]
    
    #pdb.set_trace()
    
    print(depthlist)
    print(numberlist)
    
    [depthlist, numberlist] = reduce(depthlist, numberlist)
    
    listofnumberlists = listofnumberlists[1:]
    listofdepthlists = listofdepthlists[1:]
    
    listofnumberlists[0] = numberlist
    listofdepthlists[0] = depthlist
    
    i += 1
    length -= 1

answer = "[[[[5,0],[7,4]],[5,5]],[6,6]]"
[depthlist_answer, numberlist_answer] = dive(answer)
print("Reduced depthlist is ",depthlist)
print("Correct answer is ",depthlist_answer)
print("Reduced number list is ",numberlist)
print("Correct answer is ",numberlist_answer)
if depthlist_answer == depthlist and numberlist_answer == numberlist:
    print("addition of test3 list was correct")
else:
    print("addition of test3 was wrong")
    pdb.set_trace()
print("")

###Homework Test Code 1
print("begin the test")
print("")
#Dive into each sfno
listofdepthlists = []
listofnumberlists = []
for sfno in test:
    [depthlist, numberlist] = dive(sfno)
    listofdepthlists.append(depthlist)
    listofnumberlists.append(numberlist)

#Add the first 2 sfnos in the test list until there is only 1 sfno left
length = len(listofnumberlists)
i = 0
while length > 1:
    numberlist = listofnumberlists[0] + listofnumberlists[1]
    depthlist = listofdepthlists[0] + listofdepthlists[1]
    depthlist = [x+1 for x in depthlist]
    
    #pdb.set_trace()
    
    print(depthlist)
    print(numberlist)
    
    [depthlist, numberlist] = reduce(depthlist, numberlist)
    
    listofnumberlists = listofnumberlists[1:]
    listofdepthlists = listofdepthlists[1:]
    
    listofnumberlists[0] = numberlist
    listofdepthlists[0] = depthlist
    
    [depthlist_answer, numberlist_answer] = dive(testmarks[i])
    if depthlist_answer == depthlist and numberlist_answer == numberlist:
        print("addition of sfnos was correct")
    else:
        print("addition of sfnos was wrong")
        pdb.set_trace()
    
    i += 1
    length -= 1

answer = "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]"
magnitude_answer = 3488
[depthlist_answer, numberlist_answer] = dive(answer)
print("Reduced depthlist is ",depthlist)
print("Correct answer is ",depthlist_answer)
print("Reduced number list is ",numberlist)
print("Correct answer is ",numberlist_answer)
if depthlist_answer == depthlist and numberlist_answer == numberlist:
    print("addition of test1 list was correct")
else:
    print("addition of test1 was wrong")
    pdb.set_trace()

magnitude = find_magnitude(depthlist, numberlist)

print("Magnitude is ",magnitude)
print("Magnitude answer is ",magnitude_answer)
if magnitude_answer == magnitude:
    print("magnitude was correct")
else:
    print("magnitude was wrong")
    pdb.set_trace()
print("")

###Homework Test Code 2
print("begin the test")
print("")
#Dive into each sfno
listofdepthlists = []
listofnumberlists = []
for sfno in test2:
    [depthlist, numberlist] = dive(sfno)
    listofdepthlists.append(depthlist)
    listofnumberlists.append(numberlist)

#Add the first 2 sfnos in the test list until there is only 1 sfno left
length = len(listofnumberlists)
i = 0
while length > 1:
    numberlist = listofnumberlists[0] + listofnumberlists[1]
    depthlist = listofdepthlists[0] + listofdepthlists[1]
    depthlist = [x+1 for x in depthlist]
    
    #pdb.set_trace()
    
    print(depthlist)
    print(numberlist)
    
    [depthlist, numberlist] = reduce(depthlist, numberlist)
    
    listofnumberlists = listofnumberlists[1:]
    listofdepthlists = listofdepthlists[1:]
    
    listofnumberlists[0] = numberlist
    listofdepthlists[0] = depthlist
    
    i += 1
    length -= 1

answer = "[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]"
magnitude_answer = 4140
[depthlist_answer, numberlist_answer] = dive(answer)
print("Reduced depthlist is ",depthlist)
print("Correct answer is ",depthlist_answer)
print("Reduced number list is ",numberlist)
print("Correct answer is ",numberlist_answer)
if depthlist_answer == depthlist and numberlist_answer == numberlist:
    print("addition of test2 list was correct")
else:
    print("addition of test2 was wrong")
    pdb.set_trace()

magnitude = find_magnitude(depthlist, numberlist)

print("Magnitude is ",magnitude)
print("Magnitude answer is ",magnitude_answer)
if magnitude_answer == magnitude:
    print("magnitude was correct")
else:
    print("magnitude was wrong")
    pdb.set_trace()
print("")

###Actual Homework
print("begin the assignment")
print("")
#Dive into each sfno
listofdepthlists = []
listofnumberlists = []
for sfno in hw:
    [depthlist, numberlist] = dive(sfno)
    listofdepthlists.append(depthlist)
    listofnumberlists.append(numberlist)

#Add the first 2 sfnos in the test list until there is only 1 sfno left
length = len(listofnumberlists)
i = 0
while length > 1:
    numberlist = listofnumberlists[0] + listofnumberlists[1]
    depthlist = listofdepthlists[0] + listofdepthlists[1]
    depthlist = [x+1 for x in depthlist]
    
    #pdb.set_trace()
    
    print(depthlist)
    print(numberlist)
    
    [depthlist, numberlist] = reduce(depthlist, numberlist)
    
    listofnumberlists = listofnumberlists[1:]
    listofdepthlists = listofdepthlists[1:]
    
    listofnumberlists[0] = numberlist
    listofdepthlists[0] = depthlist
    
    i += 1
    length -= 1

[depthlist_answer, numberlist_answer] = dive(answer)
print("Reduced depthlist is ",depthlist)
print("Reduced number list is ",numberlist)

magnitude = find_magnitude(depthlist, numberlist)

print("Magnitude is ",magnitude)
print("")

###START PART 2
print("")
print("TIME TO START PART 2 NOW, EXCITED!")
print("")
print("")

#Test 2 Homework
print("Lets give test 2 a go")
print("Test2 begin")
print("")

#Dive into each sfno
listofdepthlists = []
listofnumberlists = []
for sfno in test2:
    [depthlist, numberlist] = dive(sfno)
    listofdepthlists.append(depthlist)
    listofnumberlists.append(numberlist)

#Create List of magnitudes found
magnitudes = []

#Add each number to every other remaining number
for i,number in enumerate(listofnumberlists):
    #find elements to try adding
    elements = list(range(i+1,len(listofnumberlists)))
    
    #Add each element in both directions and find magnitude
    for k in elements:
        numberlist = listofnumberlists[i] + listofnumberlists[k]
        depthlist = listofdepthlists[i] + listofdepthlists[k]
        depthlist = [x+1 for x in depthlist]
        
        [depthlist, numberlist] = reduce(depthlist, numberlist)
        
        magnitude = find_magnitude(depthlist, numberlist)
        
        magnitudes.append(magnitude)
        
        numberlist = listofnumberlists[k] + listofnumberlists[i]
        depthlist = listofdepthlists[k] + listofdepthlists[i]
        depthlist = [x+1 for x in depthlist]
        
        [depthlist, numberlist] = reduce(depthlist, numberlist)
        
        magnitude = find_magnitude(depthlist, numberlist)
        
        magnitudes.append(magnitude)

max_magnitude = max(magnitudes)
print("Max Magnitude is ",max_magnitude)
max_magnitude_answer = 3993
print("Max Magnitude answer is",max_magnitude)
if max_magnitude_answer == max_magnitude:
    print("magnitude was correct")
else:
    print("magnitude was wrong")
    pdb.set_trace()
print("")

#Part 2 Homework
print("Oay here we go")
print("Part 2 assignment begin")
print("")

#Dive into each sfno
listofdepthlists = []
listofnumberlists = []
for sfno in hw:
    [depthlist, numberlist] = dive(sfno)
    listofdepthlists.append(depthlist)
    listofnumberlists.append(numberlist)

#Create List of magnitudes found
magnitudes = []

#Add each number to every other remaining number
for i,number in enumerate(listofnumberlists):
    #find elements to try adding
    elements = list(range(i+1,len(listofnumberlists)))
    
    #Add each element in both directions and find magnitude
    for k in elements:
        numberlist = listofnumberlists[i] + listofnumberlists[k]
        depthlist = listofdepthlists[i] + listofdepthlists[k]
        depthlist = [x+1 for x in depthlist]
        
        [depthlist, numberlist] = reduce(depthlist, numberlist)
        
        magnitude = find_magnitude(depthlist, numberlist)
        
        magnitudes.append(magnitude)
        
        numberlist = listofnumberlists[k] + listofnumberlists[i]
        depthlist = listofdepthlists[k] + listofdepthlists[i]
        depthlist = [x+1 for x in depthlist]
        
        [depthlist, numberlist] = reduce(depthlist, numberlist)
        
        magnitude = find_magnitude(depthlist, numberlist)
        
        magnitudes.append(magnitude)

max_magnitude = max(magnitudes)
print("Max Magnitude is ",max_magnitude)

#Result
#print(homework)
#print(depthlist)
#print(numberlist)
#print(maxdepth)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
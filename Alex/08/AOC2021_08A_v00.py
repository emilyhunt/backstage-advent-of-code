#Advent of code 2021
#Day 8 Part 1
#Seven Segment Search

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Functions
def identify_easy_digits(digits_to_identify):
    #Identifies the digits with unique numbers of segments: 1, 4, 7, and 8
    identified_digits = []
    no_identified = 0
    
    for i, line in enumerate(digits_to_identify):
        identified_digits.append([])
        
        for j, digit in enumerate(line):
            length = len(digit)
            
            if length == 2:
                identified_digits[i].append(1)
                no_identified += 1
            elif length == 3:
                identified_digits[i].append(7)
                no_identified += 1
            elif length == 4:
                identified_digits[i].append(4)
                no_identified += 1
            elif length == 7:
                identified_digits[i].append(8)
                no_identified += 1
            elif length == 5 or length == 6:
                identified_digits[i].append("HARD")
            else:
                print('This was not a severn segment number')
    
    return identified_digits, no_identified

#Import and sort File
signal_patterns = []#zero to patterns
outputs = []#output digits

with open("input_08.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("/n")#Remove EOL symbol
        
        line = line.split(" | ")
        
        signal_pattern = line[0]
        signal_pattern = signal_pattern.split()
        signal_patterns.append(signal_pattern)
        
        output = line[1]
        output = output.split()
        outputs.append(output)

###Main Code
identified_outputs, no_identified = identify_easy_digits(outputs)



#Result
print(identified_outputs)
print(no_identified)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
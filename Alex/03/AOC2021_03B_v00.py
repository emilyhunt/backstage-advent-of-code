#Advent of code 2021
#Day 3 Part 2
#Binary Diagnostic

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Import and sort File
diagnostic = []

with open("input_03.txt") as diagnosticf:
    for line in diagnosticf:
        #Import operations
        
        line = line[:-1]#Remove EOL symbol
        line = [char for char in line]
        
        diagnostic.append(line)

#Main Code
diagnostic = np.array(diagnostic)
gamma = []
epsilon = []

#Finds oxygen generator rating
diagnostic_trans = diagnostic.transpose()
i = 0
while diagnostic_trans.shape[1] > 1:
    
    column = diagnostic_trans[i]
    
    zeros = np.count_nonzero(column == '0')
    ones = np.count_nonzero(column == '1')
    
    #pdb.set_trace()
    
    if ones >= zeros:
        delete_value = '0'
    else:
        delete_value = '1'
    
    delete_array= []
    for digit in diagnostic_trans[i]:
        if digit == delete_value:
            delete_array.append(False)
        else:
            delete_array.append(True)
    
    #Update diagnostic_trans
    diagnostic_trans_new = []
    for line in diagnostic_trans:
        diagnostic_trans_new.append(line[delete_array])
        
    diagnostic_trans = np.array(diagnostic_trans_new)
    
    i += 1

diagnostic_trans = np.concatenate(diagnostic_trans)
oxy_gen = int("".join(diagnostic_trans), 2)

#Finds CO2 scrubber rating
diagnostic_trans = diagnostic.transpose()
i = 0
while diagnostic_trans.shape[1] > 1:
    
    column = diagnostic_trans[i]
    
    zeros = np.count_nonzero(column == '0')
    ones = np.count_nonzero(column == '1')
    
    #pdb.set_trace()
    
    if ones >= zeros:
        delete_value = '1'
    else:
        delete_value = '0'
    
    delete_array= []
    for digit in diagnostic_trans[i]:
        if digit == delete_value:
            delete_array.append(False)
        else:
            delete_array.append(True)
    
    #Update diagnostic_trans
    diagnostic_trans_new = []
    for line in diagnostic_trans:
        diagnostic_trans_new.append(line[delete_array])
        
    diagnostic_trans = np.array(diagnostic_trans_new)
    
    i += 1

diagnostic_trans = np.concatenate(diagnostic_trans)
CO2_scrub = int("".join(diagnostic_trans), 2)

life_support_rating = oxy_gen*CO2_scrub

#Result
print(diagnostic)
print(oxy_gen)
print(CO2_scrub)
print(life_support_rating)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
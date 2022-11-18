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
def remove_letters_from_string (string, letters_to_remove):
    
    for char in letters_to_remove:
        if char in string:
            string = string.replace(char,"")
    
    return string


def identify_easy_digits(i, line, positions, identified_digits, no_identified):
    for j, digit in enumerate(line):
        length = len(digit)
        
        #pdb.set_trace()
        
        if length == 2:#Digit is a 1
            
            identified_digits[i].append(1)
            no_identified += 1
            
            letters_to_remove = remove_letters_from_string('abcdefg',digit)
            
            #Removes other letters from target segments
            positions[2] = remove_letters_from_string(positions[2],letters_to_remove)
            positions[5] = remove_letters_from_string(positions[5],letters_to_remove)
            
            #remove target segment letters from other segments
            positions[0] = remove_letters_from_string(positions[0],digit)
            positions[1] = remove_letters_from_string(positions[1],digit)
            positions[3] = remove_letters_from_string(positions[3],digit)
            positions[4] = remove_letters_from_string(positions[4],digit)
            positions[6] = remove_letters_from_string(positions[6],digit)
            
        elif length == 3:#Digit is a 7
            identified_digits[i].append(7)
            no_identified += 1
            
            letters_to_remove = remove_letters_from_string('abcdefg',digit)
            
            #Removes other letters from target segments
            positions[0] = remove_letters_from_string(positions[0],letters_to_remove)
            positions[2] = remove_letters_from_string(positions[2],letters_to_remove)
            positions[5] = remove_letters_from_string(positions[5],letters_to_remove)
            
            #remove target segment letters from other segments
            positions[1] = remove_letters_from_string(positions[1],digit)
            positions[3] = remove_letters_from_string(positions[3],digit)
            positions[4] = remove_letters_from_string(positions[4],digit)
            positions[6] = remove_letters_from_string(positions[6],digit)
            
        elif length == 4:#Digit is a 4
            identified_digits[i].append(4)
            no_identified += 1
            
            letters_to_remove = remove_letters_from_string('abcdefg',digit)
            
            #Removes other letters from target segments
            positions[1] = remove_letters_from_string(positions[1],letters_to_remove)
            positions[2] = remove_letters_from_string(positions[2],letters_to_remove)
            positions[3] = remove_letters_from_string(positions[3],letters_to_remove)
            positions[5] = remove_letters_from_string(positions[5],letters_to_remove)
            
            #remove target segment letters from other segments
            positions[0] = remove_letters_from_string(positions[0],digit)
            positions[4] = remove_letters_from_string(positions[4],digit)
            positions[6] = remove_letters_from_string(positions[6],digit)
            
        elif length == 7:#Digit is an 8
            identified_digits[i].append(8)
            no_identified += 1
        elif length == 5:
            identified_digits[i].append("HARD5")
            
            no_identified += 1
        elif length == 6:
            identified_digits[i].append("HARD6")
        else:
            print('This was not a severn segment number')
            
        #print(positions)
    
    return positions, no_identified

def identify_hard_digits(i, line, positions, identified_digits, no_identified):
    
    for j, digit in enumerate(line):
        length = len(digit)
        
        if length == 5:
            
            if positions[4][0] in digit and positions[4][len(positions[4]) - 1] in digit:#Digit is a 2
                identified_digits[i][j] = 2
                no_identified += 1
                
                letters_to_remove = remove_letters_from_string('abcdefg',digit)
                
                #Removes other letters from target segments
                positions[0] = remove_letters_from_string(positions[0],letters_to_remove)
                positions[2] = remove_letters_from_string(positions[2],letters_to_remove)
                positions[3] = remove_letters_from_string(positions[3],letters_to_remove)
                positions[4] = remove_letters_from_string(positions[4],letters_to_remove)
                positions[6] = remove_letters_from_string(positions[6],letters_to_remove)
                
                #remove target segment letters from other segments
                positions[1] = remove_letters_from_string(positions[1],digit)
                positions[5] = remove_letters_from_string(positions[5],digit)
                
            elif positions[2][0] in digit and positions[2][len(positions[2]) - 1] in digit:#Digit is a 3
                identified_digits[i][j] = 3
                no_identified += 1
                
                letters_to_remove = remove_letters_from_string('abcdefg',digit)
                
                #Removes other letters from target segments
                positions[0] = remove_letters_from_string(positions[0],letters_to_remove)
                positions[2] = remove_letters_from_string(positions[2],letters_to_remove)
                positions[3] = remove_letters_from_string(positions[3],letters_to_remove)
                positions[5] = remove_letters_from_string(positions[5],letters_to_remove)
                positions[6] = remove_letters_from_string(positions[6],letters_to_remove)
                
                #remove target segment letters from other segments
                positions[1] = remove_letters_from_string(positions[1],digit)
                positions[4] = remove_letters_from_string(positions[4],digit)
                
            elif positions[3][0] in digit and positions[3][len(positions[3]) - 1] in digit:#Digit is a 5
                identified_digits[i][j] = 5
                no_identified += 1
                
                letters_to_remove = remove_letters_from_string('abcdefg',digit)
                
                #Removes other letters from target segments
                positions[0] = remove_letters_from_string(positions[0],letters_to_remove)
                positions[1] = remove_letters_from_string(positions[1],letters_to_remove)
                positions[3] = remove_letters_from_string(positions[3],letters_to_remove)
                positions[5] = remove_letters_from_string(positions[5],letters_to_remove)
                positions[6] = remove_letters_from_string(positions[6],letters_to_remove)
                
                #remove target segment letters from other segments
                positions[2] = remove_letters_from_string(positions[2],digit)
                positions[4] = remove_letters_from_string(positions[4],digit)
                
            else:
                print('cannot identify digit of length five')
        
        elif length == 6:
            sorteddigit = sorted(digit)
            sorteddigit = ''.join(sorteddigit)
            
            if (positions[1][0] in digit) ^ (positions[3][len(positions[1]) - 1] in digit):#Digit is a 0
                identified_digits[i][j] = 0
                no_identified += 1
                
                letters_to_remove = remove_letters_from_string('abcdefg',digit)
                
                #Removes other letters from target segments
                positions[0] = remove_letters_from_string(positions[0],letters_to_remove)
                positions[1] = remove_letters_from_string(positions[1],letters_to_remove)
                positions[2] = remove_letters_from_string(positions[2],letters_to_remove)
                positions[4] = remove_letters_from_string(positions[4],letters_to_remove)
                positions[5] = remove_letters_from_string(positions[5],letters_to_remove)
                positions[6] = remove_letters_from_string(positions[6],letters_to_remove)
                
                #remove target segment letters from other segments
                positions[3] = remove_letters_from_string(positions[3],digit)
                
            elif (positions[2][0] in digit) ^ (positions[5][len(positions[2]) - 1] in digit):#Digit is a 6
                identified_digits[i][j] = 6
                no_identified += 1
                
                letters_to_remove = remove_letters_from_string('abcdefg',digit)
                
                #Removes other letters from target segments
                positions[0] = remove_letters_from_string(positions[0],letters_to_remove)
                positions[1] = remove_letters_from_string(positions[1],letters_to_remove)
                positions[3] = remove_letters_from_string(positions[3],letters_to_remove)
                positions[4] = remove_letters_from_string(positions[4],letters_to_remove)
                positions[5] = remove_letters_from_string(positions[5],letters_to_remove)
                positions[6] = remove_letters_from_string(positions[6],letters_to_remove)
                
                #remove target segment letters from other segments
                positions[2] = remove_letters_from_string(positions[2],digit)
                
            elif (positions[4][0] in digit) ^ (positions[6][len(positions[6]) - 1] in digit):#Digit is a 9
                identified_digits[i][j] = 9
                no_identified += 1
                
                letters_to_remove = remove_letters_from_string('abcdefg',digit)
                
                #Removes other letters from target segments
                positions[0] = remove_letters_from_string(positions[0],letters_to_remove)
                positions[1] = remove_letters_from_string(positions[1],letters_to_remove)
                positions[2] = remove_letters_from_string(positions[2],letters_to_remove)
                positions[3] = remove_letters_from_string(positions[3],letters_to_remove)
                positions[5] = remove_letters_from_string(positions[5],letters_to_remove)
                positions[6] = remove_letters_from_string(positions[6],letters_to_remove)
                
                #remove target segment letters from other segments
                positions[4] = remove_letters_from_string(positions[4],digit)
                
            else:
                print('cannot identify digit of length six')
    
    
    return positions, no_identified

def identify_set_of_digits(digits_to_identify):
    #Identifies the digits with unique numbers of segments: 1, 4, 7, and 8
    identified_digits = []
    no_identified = 0
    all_positions = []
    
    
    
    for i, line in enumerate(digits_to_identify):
        identified_digits.append([])
        
        positions = ['abcdefg','abcdefg','abcdefg','abcdefg','abcdefg','abcdefg','abcdefg']
        
        positions, no_identified = identify_easy_digits(i, line, positions, identified_digits, no_identified)
        positions, no_identified = identify_hard_digits(i, line, positions, identified_digits, no_identified)
        
        all_positions.append(positions)
    
    
    return identified_digits, no_identified, all_positions

def decode_digits(outputs, all_positions):
    
    identified_outputs = []
    
    for i, line in enumerate(outputs):
        identified_outputs.append([])
        
        #Create code for each number
        positions = all_positions[i]
        zero = sorted([positions[0],positions[1],positions[2],positions[4],positions[5],positions[6]])
        zero = ''.join(zero)
        one = sorted([positions[2],positions[5]])
        one = ''.join(one)
        two = sorted([positions[0],positions[2],positions[3],positions[4],positions[6]])
        two = ''.join(two)
        three = sorted([positions[0],positions[2],positions[3],positions[5],positions[6]])
        three = ''.join(three)
        four = sorted([positions[1],positions[2],positions[3],positions[5]])
        four = ''.join(four)
        five = sorted([positions[0],positions[1],positions[3],positions[5],positions[6]])
        five = ''.join(five)
        six = sorted([positions[0],positions[1],positions[3],positions[4],positions[5],positions[6]])
        six = ''.join(six)
        severn = sorted([positions[0],positions[2],positions[5]])
        severn = ''.join(severn)
        eight = sorted(positions)
        eight = ''.join(eight)
        nine = sorted([positions[0],positions[1],positions[2],positions[3],positions[5],positions[6]])
        nine = ''.join(nine)
        
        keys = [zero,one,two,three,four,five,six,severn,eight,nine]
        
        for j, digit in enumerate(line):
            #sort digit
            digit = sorted(digit)
            digit = ''.join(digit)
            
            for k,key in enumerate(keys):
                #Find which digit it is and store it
                if digit == key:
                    identified_outputs[i].append(k)
                    break
            
        
    
    return identified_outputs


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
#identified_outputs, no_identified = identify_easy_digits(outputs)
identified_signal, no_identified, all_positions = identify_set_of_digits(signal_patterns)

identified_outputs = decode_digits(outputs, all_positions)

total = sum(int(''.join(map(str,x))) for x in identified_outputs)

#Result
print(identified_signal)
print(no_identified)
print(all_positions)
print(identified_outputs)
print(total)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
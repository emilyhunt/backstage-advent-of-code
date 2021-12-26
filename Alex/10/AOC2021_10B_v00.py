#Advent of code 2021
#Day 10 Part 1
#Syntax Scoring

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Functions
def get_opposite_bracket(string):
	
	#DefineSwapDict
	swap_char = {
		'(': ')',
		')': '(',
		'[': ']',
		']': '[',
		'{': '}',
		'}': '{',
		'<': '>',
		'>': '<'
	}
	
	reverse_string = string[::-1]
	opposite_string = ''
	
	for char in reverse_string:
		opposite_string = opposite_string + swap_char[char]
	
	return opposite_string


def checknavinstruction(instruction):
	
	floating_chars = ''
	
	corrupted_bool = False
	offending_char = ''
	expected_char = ''
	incomplete_bool = False
	char_missing = ''
	
	for j, char in enumerate(instruction):
		#print(char)
		#print(floating_chars)
		#pdb.set_trace()
		
		if char == '[' or char == '(' or char == '{' or char =='<':#Open Bracket
			floating_chars = floating_chars + char
		elif char == ']' or char == ')' or char == '}' or char =='>':#Close Bracket
			if floating_chars[-1] == '[' and char == ']':
				floating_chars = floating_chars[0:len(floating_chars)-1]
			elif floating_chars[-1] == '(' and char == ')':
				floating_chars = floating_chars[0:len(floating_chars)-1]
			elif floating_chars[-1] == '{' and char == '}':
				floating_chars = floating_chars[0:len(floating_chars)-1]
			elif floating_chars[-1] == '<' and char == '>':
				floating_chars = floating_chars[0:len(floating_chars)-1]
			else:
				#pdb.set_trace()
				#print('data is corrupt')
				corrupted_bool = True
				offending_char = char
				expected_char = get_opposite_bracket(floating_chars[-1])
				break
	
	#Handle Incompleted
	if floating_chars != '':
		char_missing = get_opposite_bracket(floating_chars)
		incomplete_bool = True
	
	#print(corrupted_bool)
	#print(offending_char)
	#print(expected_char)
	#print(incomplete_bool)
	#print(char_missing)
	#print('Floating chars are ',floating_chars)
	
	#pdb.set_trace()
	
	
	
	return corrupted_bool, offending_char, expected_char, incomplete_bool, char_missing

#Import and sort File
navdata = []

with open("input_10.txt") as navdataf:
	for line in navdataf:
		#Import operations
		
		line = line.strip("\n")#Remove EOL symbol
		
		navdata.append(line)

###Main Code
error_types = []
devious_chars = []

for i, instruction in enumerate(navdata):
	corrupted_bool, offending_char, expected_char, incomplete_bool, char_missing = checknavinstruction(instruction)
	error_types.append([corrupted_bool, incomplete_bool])
	devious_chars.append([offending_char, expected_char, char_missing])

#Calculate sum of illegal chars
illegal_score = {
	')': 3,
	']': 57,
	'}': 1197,
	'>': 25137,
	'': 0
}

syn_err_score = 0

for deviants in devious_chars:
	syn_err_score += illegal_score[deviants[0]]

#Calculate score of incomplete chars
incomplete_score = {
	')': 1,
	']': 2,
	'}': 3,
	'>': 4,
	'': 0
}

incomplete_err_score = []

#pdb.set_trace()

for i, deviants in enumerate(devious_chars):
	err_score = 0
	if error_types[i][0] == True or error_types[i][1] != True:
		continue
	else:
		for char in deviants[2]:
			err_score *= 5
			err_score += incomplete_score[char]
	
	incomplete_err_score.append(err_score)

incomplete_err_score = sorted(incomplete_err_score)
middle_score = incomplete_err_score[int((len(incomplete_err_score)-1)/2)]

#Result
print(navdata)
print(error_types)
print(devious_chars)
print(syn_err_score)
print(middle_score)


timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
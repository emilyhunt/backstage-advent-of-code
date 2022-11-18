#Advent of code 2021
#Day 4 Part 1
#Giant Squid

import numpy as np
np.set_printoptions(threshold=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

##Functions

#Function: Tick off number in card
def tick_off_number(card,value,hit_map):
    k = 0
    for line in card:
        l = 0
        for num in line:
            if num == value:
                hit_map[k][l] = True
            l += 1
        k += 1
    
    return card,hit_map

#Function: Check if player has won
def check_if_won(hit_map):
    won_boolean = False
    k = 0
    for line in hit_map:
        if len(line) == sum (line):
            won_boolean = True
        k += 1
    
    hit_mapT = hit_map.transpose()
    k = 0
    for line in hit_mapT:
        if len(line) == sum (line):
            won_boolean = True
        k += 1
    
    return won_boolean

#Import and sort File
cards = []
card = []
numbers = []

with open("input_04.txt") as inputf:
    i = 0
    for line in inputf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        line = line.strip()
        
        if i == 0:#Store random number call as numbers
            line = line.split(",")
            numbers = np.array(line)
            i += 1
            continue
        
        if line == "":#store current bingo card in cards
            card = np.array(card)
            cards.append(card)
            card = []
            i += 1
            continue
        
        #Store line to current bingo card
        line = line.split()
        card.append(line)
        
        i += 1

card = np.array(card)
cards.append(card)
cards[0] = ""
cards.remove("")

###Main Code

#Make Boolean Array
hit_map_card = np.zeros([5,5],dtype=bool)
hit_maps = [hit_map_card] * len(cards)

#Loop through each number being called
i = 0
for value in numbers:
    
    j = 0
    for card in cards:
        #Mark Numbers as having been called
        hit_map = copy.deepcopy(hit_maps[j])
        card,hit_map = tick_off_number(card,value,hit_map)
        hit_maps[j] = hit_map
        
        #Check if player has won
        won_boolean = check_if_won(hit_map)
        
        if won_boolean == True:
            winning_board = card
            winning_board_num = j
            winning_board_hit_map = hit_map
            value_called_at_win = int(value)
            break
        
        j += 1
    
    else:
        i += 1
        continue
    
    i += 1
    break

#Sum unmarked numbers on winning board
winning_marked_values = winning_board[winning_board_hit_map]
winning_unmarked_values = winning_board[np.invert(winning_board_hit_map)]

sum_of_unmarked_values = np.sum(winning_unmarked_values.astype(int))

result = sum_of_unmarked_values * value_called_at_win

#Result
#print(numbers)
#print(cards)
print("winner is board " + str(winning_board_num))
print(winning_board)
print(winning_board_hit_map)
print(result)

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
#Advent of code 2021
#Day 16 Part 1
#Packet Decoder

import numpy as np
np.set_printoptions(threshold=np.inf)
np.set_printoptions(linewidth=np.inf)
import pdb #pdb.set_trace()
import time
import copy

start_time = time.time()

#Functions
def process_packet(unprocessed_transmission_binary,versionsum,value):
    
    version = unprocessed_transmission_binary[0:3]
    versionsum += int(version,2)
    
    typeID = unprocessed_transmission_binary[3:6]
    unprocessed_transmission_binary = unprocessed_transmission_binary[6:]
    
    if typeID == "100":
        #This packet is a literal value. Process and continue
        print("literal value packet")
        
        lastbyte = "1"
        packet_value = ""
        
        while lastbyte == "1":
            byte = unprocessed_transmission_binary[0:5]
            unprocessed_transmission_binary = unprocessed_transmission_binary[5:]
            lastbyte = byte[0]
            packet_value += byte[1:]
        
        valuedec = int(packet_value,2)
        value += valuedec
        print("value of packet is " + str(valuedec))
        
        
    
    else:
        #This packet is an operator. Process sub-packets accordingly
        print("operator packet")
        packet_values = []
        
        lengthIDtype = unprocessed_transmission_binary[0]
        unprocessed_transmission_binary = unprocessed_transmission_binary[1:]
        
        if lengthIDtype == "0":
            #LengthID is a 15-bit number telling us how many characters each packet takes update
            lengthID = unprocessed_transmission_binary[0:15]
            unprocessed_transmission_binary = unprocessed_transmission_binary[15:]
            bits_toprocess = int(lengthID,2)
            bits_sent = len(unprocessed_transmission_binary)
            bits_processed = 0
            
            while bits_processed < bits_toprocess:
                [sub_packet_value,versionsum,unprocessed_transmission_binary] = process_packet(unprocessed_transmission_binary,versionsum,value)
                bits_processed = bits_sent - len(unprocessed_transmission_binary)
                packet_values.append(sub_packet_value)
            
        else:
            #LengthID is an 11-bit number telling us how many sub-packets to expect
            lengthID = unprocessed_transmission_binary[0:11]
            unprocessed_transmission_binary = unprocessed_transmission_binary[11:]
            packets_left = int(lengthID,2)
            
            while packets_left > 0:
                [sub_packet_value,versionsum,unprocessed_transmission_binary] = process_packet(unprocessed_transmission_binary,versionsum,value)
                packets_left -= 1
                packet_values.append(sub_packet_value)
        
        #ProcessPacketValues
        typeIDdec = int(typeID,2)
        
        if typeIDdec == 0:
            #sum packet
            value = sum(packet_values)
        elif typeIDdec == 1:
            #Product packet
            value = np.product(packet_values)
        elif typeIDdec == 2:
            #Minimum packet
            value = min(packet_values)
        elif typeIDdec == 3:
            #Max packet
            value = max(packet_values)
        elif typeIDdec == 5:
            #Greater than packet
            value_A = packet_values[0]
            value_B = packet_values[1]
            if value_A > value_B:
                value = 1
            else:
                value = 0
        elif typeIDdec == 6:
            #Less than packet
            value_A = packet_values[0]
            value_B = packet_values[1]
            if value_A < value_B:
                value = 1
            else:
                value = 0
        elif typeIDdec == 7:
            #Equal to packet
            value_A = packet_values[0]
            value_B = packet_values[1]
            if value_A == value_B:
                value = 1
            else:
                value = 0
        else:
            print("Packet Type ID not valid")
    
    return value, versionsum, unprocessed_transmission_binary

##Import and sort File
transmission = ""

with open("input_16.txt") as input_dataf:
    for line in input_dataf:
        #Import operations
        
        line = line.strip("\n")#Remove EOL symbol
        
        #line = line.split(" -> ")
        
        transmission = line

print(transmission)

##Settings
hextobin = {}
hextobin["0"] = "0000"
hextobin["1"] = "0001"
hextobin["2"] = "0010"
hextobin["3"] = "0011"
hextobin["4"] = "0100"
hextobin["5"] = "0101"
hextobin["6"] = "0110"
hextobin["7"] = "0111"
hextobin["8"] = "1000"
hextobin["9"] = "1001"
hextobin["A"] = "1010"
hextobin["B"] = "1011"
hextobin["C"] = "1100"
hextobin["D"] = "1101"
hextobin["E"] = "1110"
hextobin["F"] = "1111"

#print(hextobin)

###Main Code
#Convert transmission to binary
transmission_binary = ""
for char in transmission:
    transmission_binary += hextobin[char]
    
print(transmission_binary)

#Identify and make a list of packets
packets_binary = []
unprocessed_transmission_binary = transmission_binary
versionsum = 0
value = 0
[value,versionsum,unprocessed_transmission_binary] = process_packet(unprocessed_transmission_binary,versionsum,value)

print("This transmission has a version sum of " + str(versionsum))
print("This transmission has a total value of " + str(value))


#Result

timetaken = time.time() - start_time
print("Completed in ", timetaken, " seconds")
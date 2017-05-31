import base64

# Calculates the "edit distance" between two bytes.
def calcEditDistByte(byte1, byte2):
	editDist = 0
	editDistByte = byte1^byte2	# Xor the two bytes.
	
	for _ in range(0,8):	# Go through each bit.
		editDist += editDistByte%2	# If the bit is one, the corresponding
									# bits of the two bytes were different.
		editDistByte >>= 1	# Shift the byte 1 to the right
	
	return editDist

# Calculates the "edit distance" between two strings.
# Will need a byte array version of this.
def calcEditDist(string1, string2):
	editDist = 0
	
	# Go throught the two strings. Note: will only work if the two strings are equal length.
	for pos in range(0,len(string1)):
		byte1 = ord(string1[pos])
		byte2 = ord(string2[pos])	# Convert each character to an integer.
		
		editDist += calcEditDistByte(byte1, byte2)	# Calculate the distance between these integers
													# then increment the editDist by that amount.
		
	return editDist

string1 = "this is a test"
string2 = "wokka wokka!!!"

distance = calcEditDist(string1, string2)
print(distance)

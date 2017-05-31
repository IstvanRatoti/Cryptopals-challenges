
# This function accepts strings or arrays of integers.
# It will convert them into byte arrays if needed.
# It will return the cipher in an array of integers.
def repeatingKeyXOR(plaintext, key):
	cipher= []
	keylen = len(key)
	
	for pos in range(0,len(plaintext)):		# Go through the input data.
		if type(plaintext) is str:
			textbyte = ord(plaintext[pos])	# Check if string or integer.
		else:
			textbyte = plaintext[pos]
		
		if type(key) is str:
			keybyte = ord(key[pos%keylen])	# Again, check if string or integer.
		else:
			keybyte = key[pos%keylen]
		
		cipher.append(textbyte^keybyte)		# create and add the new cipher byte to the array.

	return cipher

#text = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
#cipher = repeatingKeyXOR(text, "ICE")
													# Code for challenge 4.
#for byte in cipher:
#	print("%02x" % byte, end='')
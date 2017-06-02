import base64


# Calculates the "edit distance" between two bytes.
def calcEditDistByte(byte1, byte2):
    editDist = 0
    editDistByte = byte1 ^ byte2  # Xor the two bytes.

    for _ in range(0, 8):  # Go through each bit.
        editDist += editDistByte % 2  # If the bit is one, the corresponding
        # bits of the two bytes were different.
        editDistByte >>= 1  # Shift the byte 1 to the right

    return editDist

# Calculates the "edit distance" between two strings.
# Will need a byte array version of this. Done!
def calcStrEditDist(string1, string2):
    editDist = 0

    # Go throught the two strings. Note: will only work if the two strings are equal length.
    for pos in range(0, len(string1)):
        byte1 = ord(string1[pos])
        byte2 = ord(string2[pos])  # Convert each character to an integer.

        editDist += calcEditDistByte(byte1, byte2)  # Calculate the distance between these integers
    # then increment the editDist by that amount.

    return editDist


# Calculates the "edit distance" between two byte arrays.
def calcEditDist(bytes1, bytes2):
    editDist = 0

    # Go throught the two strings. Note: will only work if the two strings are equal length.
    for pos in range(0, len(bytes1)):
        editDist += calcEditDistByte(bytes1[pos], bytes2[pos])  # Calculate the distance between these integers
                                                                # then increment the editDist by that amount.

    return editDist

# Calculates the "normalized edit distance" for a given cipher and keysize.
# Only uses the first 2 keysize size of bytes. Can expand on it if needed.
def getNormEditDist(cipher, keysize):
    return calcEditDist(cipher[0:keysize:], cipher[keysize:2*keysize])/keysize

# Gets the probable keysize between minkeysize and maxkeysize.
# Only returns the "most probable". Can expand on it to return more.
def getProbKeysize(cipher, minkeysize, maxkeysize):
    probEditDist = 0
    probKeysize = 0

    for keysize in range(minkeysize, maxkeysize+1):
        normEditDist = getNormEditDist(cipher, keysize)

        if normEditDist>probEditDist:
            probEditDist = normEditDist
            probKeysize = keysize

    return probKeysize

string1 = "this is a test"
string2 = "wokka wokka!!!"

testdistance = calcStrEditDist(string1, string2)
print(testdistance)



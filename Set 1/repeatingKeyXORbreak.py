import base64
import operator

import repeatingKeyXOR as encrypt

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
    #print(editDist)
    return editDist

# Calculates the "normalized edit distance" for a given cipher and keysize.
# Uses the first "times" keysizes and averages them.
def getNormEditDist(cipher, keysize, times):
    distance = 0

    for num in range(0,times):
        distance += calcEditDist(cipher[num*2*keysize:keysize*(2*num+1):], cipher[keysize*(2*num+1):(num+1)*2*keysize])

    return distance/(times*keysize)

# Gets the probable keysize between minkeysize and maxkeysize.
# Returns the "keys" most probable keysizes.
def getProbKeysize(cipher, minkeysize, maxkeysize, keys, averages):
    editDistkeysizedict = {}
    probKeys = []

    for keysize in range(minkeysize, maxkeysize+1):
        normEditDist = getNormEditDist(cipher, keysize, averages)
        #print("%d: %lf" % (keysize, normEditDist))
        editDistkeysizedict[keysize]=normEditDist

    # Make a sorted list out of the dictionary.
    sorted_dict = sorted(editDistkeysizedict.items(), key=operator.itemgetter(1))
    sorted_dict = sorted_dict[:keys]    # Get the first "keys" number of elements.
    for elem in sorted_dict:
        probKeys.append(elem[0])    # Add the keysize to the list we want to return.

    return probKeys

# Needs an array of bytes, and returns the most probable key byte.
def breakSingleXOR(hex):
    keyByte = 0

    # Loop through cipher bytes from 0 to ff(255, but range excludes the upper bound.)
    for cipher in range(0, 256):
        counter = 0

        for num in hex:  # Loop through the bytes in the hex array.
            decrypted = num ^ cipher  # XOR with the current cipher.

            # If its a character, add it to the tmpstring.
            if ((decrypted>0x40)and(decrypted<0x5b))or((decrypted>0x60)and(decrypted<0x7b))or(decrypted==0x20):
                    counter += 1

        # Choose the string with the most number of characters.
        if counter > chosencounter:  # Note: This code overwrites the "most realistic" string of each input string.
            chosencounter = counter  # If there is more than one encrypted string, only the last of them will be shown.
            keyByte = num
            counter = 0

    return keyByte

#string1 = "this is a test"
#string2 = "wokka wokka!!!"     # Code testing the basic edit distance algorithm.

#testdistance = calcStrEditDist(string1, string2)
#print(testdistance)

string = "Is post each that just leaf no. He connection interested so we an sympathize advantages. To said is it shed want do. Occasional middletons everything so to. Have spot part for his quit may. Enable it is square my an regard. Often merit stuff first oh up hills as he. Servants contempt as although addition dashwood is procured. Interest in yourself an do of numerous feelings cheerful confined."
key = "test"

cipher = encrypt.repeatingKeyXOR(string, key)

print(cipher)

print(getProbKeysize(cipher, 2, 15, 3, 4))

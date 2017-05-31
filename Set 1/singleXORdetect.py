strings = []
hexes = []
chosencounter = 0
chosenstring = ""

with open("4.txt", "r") as file:    # Open the file and start reading stuff.
    
    line = file.readline()

    while 0 != len(line):
        line = line.rstrip()

        strings.append(line)
        line = file.readline()

for string in strings:  # Convert the strings to arrays containing byte arrays(arrayception).
    hex = []
    for i in range(0,len(string),2):    # Jump 2 characters each time.
        num = int(string[0+i:2+i:], 16) # Convert the 2 character long substring as a base16 int.
        hex.append(num)
    hexes.append(hex)

for hex in hexes:   # Loop through the hex arrays first.
    for cipher in range(0,256): # Then Loop through cipher bytes from 0 to ff(255, but range excludes the upper bound.)
        tmpstring = ""
        counter = 0

        for num in hex: # Loop through the bytes in the hex array.
            decrypted = num^cipher  # Xor with the current cipher.

            # If its a character, add it to the tmpstring.
            if ((decrypted>0x40)and(decrypted<0x5b))or((decrypted>0x60)and(decrypted<0x7b))or(decrypted==0x20):
                decrypted = str(chr(decrypted))
                tmpstring += decrypted
                counter += 1

        # Choose the string with the most number of characters.
        if counter>chosencounter:   # Note: This code overwrites the "most realistic" string of each input string.
            chosencounter = counter # If there is more than one encrypted string, only the last of them will be shown.
            chosenstring = tmpstring
            tmpstring = ""
            counter = 0

print(chosenstring)


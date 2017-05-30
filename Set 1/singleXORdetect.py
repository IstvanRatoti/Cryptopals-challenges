strings = []
hexes = []

with open("4.txt", "r") as file:
    newstring = ""
    count = 0
    
    line = file.readline()

    while 0 != len(line):
        line = line.rstrip()

        if 0==(count%2):
            newstring = line
        elif 1==(count%2):
            newstring += line
            strings.append(newstring)

            newstring = ""

        count +=1
        line = file.readline()

for string in strings:
    for i in range(0,len(string),2):
        num = int(string[0+i:2+i:], 16)
        print("0x%x" % num)

#print(strings)

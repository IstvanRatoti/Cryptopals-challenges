#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "functions.h"

// Set 1, Challenge 3.
int main(int argc, char *argv[])
{
	int i, j, counter=0, chosencounter=0, tmpbyte;
	
	char * chosenstr;
	
	hex hexarray = decodehex(argv[1]);
	
	hex tmparray;		// Temporary array holding our XOR-d bytes.
	tmparray.length = hexarray.length;
	tmparray.bytes = (long int *)calloc(hexarray.length, sizeof(long int));
	
	// Loop from 0x00 to 0xff. This will be the byte we XOR with.
	for(i=0;i<0x100;i++)
	{
		// Loop throught the bytes in the given hexstring.
		for(j=0;j<hexarray.length;j++)
		{
			tmparray.bytes[j] = hexarray.bytes[j]^i;	// XOR with the current byte.
			
			// Check for "viable" byte, meaning: "A-Z", "a-z" and "space". If we find one, increment the counter.
			if((tmparray.bytes[j]>0x40)&&(tmparray.bytes[j]<0x5b)||(tmparray.bytes[j]>0x60)&&(tmparray.bytes[j]<0x7b)||(tmparray.bytes[j]==0x20))
				counter++;
		}
		
		//printf("%s %d", hex2string(tmparray, 1), counter);
		
		if(counter>chosencounter)	// The one with the highest counter will be chosen.
		{
			chosencounter = counter;
			chosenstr = hex2string(tmparray, 1);
		}
		
		counter = 0;
	}
	
	// Print the chosen string.
	printf("%s", chosenstr);
	
	free(chosenstr);
	free(hexarray.bytes);	// Free the digital slaves.
	free(tmparray.bytes);
	
	return 0;
}

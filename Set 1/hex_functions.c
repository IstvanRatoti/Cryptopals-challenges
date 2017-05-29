#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "functions.h"

// This function decodes a string into a hex by one byte at a time.
hex decodehex(char * hexstring)
{
	int i, slen = strlen(hexstring);
	hex rethex;
	char bytestr[2];

	if(0!=(slen%2))		// If string is odd length, ts not a hexstring.
	{
		rethex.length = -1;

		return rethex;
	}

	//printf("Strlen: %d\n", slen);
	//getchar();  // Debug code.

	rethex.length = slen/2;		// Create the struct.
	rethex.bytes = (long int *)calloc(slen/2, sizeof(long int));

	for(i=0;i<slen;i+=2)
	{
		bytestr[0] = hexstring[i];
		bytestr[1] = hexstring[i+1];

		// Convert the strings to base16 bytes.
		rethex.bytes[i/2] = strtol(bytestr, NULL, 16);

		//printf("0x%x\t", bytes[i/2]);	// Debug code.
	}

	return rethex;
}

/*
*	Creates a string from a hex struct. Type tells what output it should generate.
*	Type 0 - Bytes converted to their string representation. I. e.: 0x5f -> 5f
*	Type 1 - Bytes converted to ascii chars. I.e.: 0x41 -> A
*/
char * hex2string(hex hexbytes, int type)
{
	int i;

	char * hexstr;
	char * tmpstr;

	if(!type)
	{
		hexstr = (char *)calloc(2*hexbytes.length, sizeof(char));
		tmpstr = (char *)calloc(2, sizeof(char));
	}
	else
	{
		hexstr = (char *)calloc(hexbytes.length, sizeof(char));
		tmpstr = (char *)calloc(1, sizeof(char));
	}

	for(i=0;i<hexbytes.length;i++)
	{
		if(!type)
		{
			sprintf(tmpstr, "%x", hexbytes.bytes[i]);
			strcat(hexstr, tmpstr);
		}
		else
		{
			sprintf(tmpstr, "%c", (char )hexbytes.bytes[i]);
			strcat(hexstr, tmpstr);
		}
	}

	free(tmpstr);

	return hexstr;
}

/*
*   Simple function that converts a string to a hex struct.
*/
hex string2hex(char * str)
{
    int i, slen = strlen(str);

    hex bytes;
    bytes.bytes = (long int *)calloc(slen, sizeof(long int));
    bytes.length = slen;

    for(i=0;i<slen;i++)
        bytes.bytes[i] = (long int )str[i];

    return bytes;
}

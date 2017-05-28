#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "functions.h"

// Set 1, Challenge 2.
int main(int argc, char *argv[])
{
	int i;
	hex xorhex;
	
	hex hex1 = decodehex(argv[1]);	// Get the two strings.
	hex hex2 = decodehex(argv[2]);
	
	xorhex.bytes = (long int *)calloc(hex1.length, sizeof(long int));
	xorhex.length = hex1.length;	// Allocate the struct.
	
	for(i=0;i<hex1.length;i++)
	{
		xorhex.bytes[i] = hex1.bytes[i]^hex2.bytes[i];	// Xor the two byte arrays.
		printf("%x", xorhex.bytes[i]);
	}
	
	free(hex1.bytes);
	free(hex2.bytes);		// Let the memory go free!
	free(xorhex.bytes);
	
	return 0;
}

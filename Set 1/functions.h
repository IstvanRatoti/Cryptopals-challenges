#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct
{
	long int * bytes;
	int length;
}hex;

// This function decodes a string into a hex by one byte at a time.
hex decodehex(char * hexstring);

/*
*	Creates a string from a hex struct. Type tells what output it should generate.
*	Type 0 - Bytes converted to their string representation. I. e.: 0x5f -> 5f
*	Type 1 - Bytes converted to ascii chars. I.e.: 0x41 -> A
*/
char * hex2string(hex hexbytes, int type);

#endif

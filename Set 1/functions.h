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

/*
*   Encodes a hex array to a base64 string.
*/
char * base64_encode(hex bytes);

/*
*   Decodes a base64 into a hex array.
*/
hex base64_decode(char * base64str);

/*
*   A simple function to decode the base64 characters back to integers.
*/
int decode_base64_char(char ch);

/*
*   Simple function that converts a string to a hex struct.
*/
hex string2hex(char * str);

#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// String containing the base64 characters with their positions.
const char indextable[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// The hex code provided on the site, broken into groups of 3 bytes, which makes decoding a lot easier.
const int numbers[16]= {	0x49276d, 0x206b69, 0x6c6c69, 0x6e6720, 0x796f75, 0x722062, 0x726169, 0x6e206c,
						0x696b65, 0x206120, 0x706f69, 0x736f6e, 0x6f7573, 0x206d75, 0x736872, 0x6f6f6d };

// Code that encrypts the hex string given into a base64 string.
char * hex2base64(void);

int main(int argc, char *argv[])
{
	//printf("0x%x", numbers[0]&0x2700);	// Debug code.
	
	char * base64string = hex2string();
	
	printf("%s", base64string);
	
	free(base64string);
	
	return 0;
}

char * hex2base64()
{
	int i, tmpnum;
	
	char * base64string = (char *)calloc(49, sizeof(char));
	
	for(i=0;i<16;i++)
	{
		tmpnum = numbers[i];
		
		// Bitwise and the last 6 bits (using 0x3f), that will give us the base64 "position".
		base64string[3*i+3] = indextable[tmpnum&0x3f];
		tmpnum >>= 6;	// Bit shift left by 6 bytes, so we can get the next 6 bit value.
		
		base64string[3*i+2] = indextable[tmpnum&0x3f];
		tmpnum >>= 6;
		
		base64string[3*i+1] = indextable[tmpnum&0x3f];
		tmpnum >>= 6;
		
		base64string[3*i] = indextable[tmpnum&0x3f];
	}
	
	return base64string;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "functions.h"

// String containing the base64 characters with their positions.
const char indextable[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*
*   Encodes a hex array to a base64 string.
*/
char * base64_encode(hex bytes)
{
    int i, tmpnum, padding, length, paddingbytes = 0;

    int * numbers;

    char * base64str;

    padding = 3 - bytes.length%3;   // Padding needed for the last bytes.
    length = bytes.length/3;        // Number of 3 length bytes.

    numbers = (int *)calloc(length, sizeof(int));

    for(i=0;i<bytes.length+3-padding;i+=3)  // Create the numbers containing 3 bytes each.
    {
        numbers[i/3] += bytes.bytes[i+2];
        numbers[i/3] += bytes.bytes[i+1]*0x100;
        numbers[i/3] += bytes.bytes[i]*0x10000;

        //printf("%d %d\n", bytes.length, i);
        //printf("0x%x", numbers[i/3]);
        //getchar();  // Debug code.

    }

    if(!padding)    // If no padding is needed, only 4*length chars are to be allocated.
        base64str = (char *)calloc(4*length, sizeof(char));
    else            // Else, we need 4 more.
        base64str = (char *)calloc(4*length+4, sizeof(char));

    for(i=0;i<length;i++)   // Create the first 4*length characters from the numbers array.
	{
		tmpnum = numbers[i];

		// Bitwise and the last 6 bits (using 0x3f), that will give us the base64 "position".
		base64str[4*i+3] = indextable[tmpnum&0x3f];
		//printf("%c", indextable[tmpnum&0x3f]);
		tmpnum >>= 6;	// Bit shift left by 6 bits, so we can get the next 6 bit value.

		base64str[4*i+2] = indextable[tmpnum&0x3f];
		//printf("%c", indextable[tmpnum&0x3f]);
		tmpnum >>= 6;

		base64str[4*i+1] = indextable[tmpnum&0x3f];
		//printf("%c", indextable[tmpnum&0x3f]);
		tmpnum >>= 6;

		base64str[4*i] = indextable[tmpnum&0x3f];
		//printf("%c\n", indextable[tmpnum&0x3f]);
	}

	if(3!=padding) // If we have padding, we need to deal with that.
	{
        if(2==padding)  // If we have a 2 byte padding.
            paddingbytes += bytes.bytes[bytes.length-1]*0x10000;
        if(1==padding)  // If we have a one byte padding.
        {
            paddingbytes += bytes.bytes[bytes.length-1]*0x100;
            paddingbytes += bytes.bytes[bytes.length-2]*0x10000;
        }

        base64str[4*length+3] = '=';    // The first one will be always padding.
        padding--;
        paddingbytes >>= 6;

        if(padding)     // The second one might be padding.
            base64str[4*length+2] = '=';
        else
            base64str[4*length+2] = indextable[paddingbytes&0x3f];
        paddingbytes >>= 6;

        base64str[4*length+1] = indextable[paddingbytes&0x3f];
        paddingbytes >>= 6;	// Bit shift left by 6 bits, so we can get the next 6 bit value.

        base64str[4*length] = indextable[paddingbytes&0x3f];
	}

	base64str[4*length+4] = '\0';

    return base64str;
}

/*
*   Decodes a base64 into a hex array.
*/
hex base64_decode(char * base64str)
{
    int i, j, tmpnum = 0, b64val, slen=strlen(base64str);

    int * numbers;

    hex bytes;
    if(slen%4)   //Check for a base64 string. If not, exit the function.
    {
        fprintf(stderr, "This is not a base64 string!\n");
        bytes.length =-1;

        return bytes;
    }

    bytes.bytes = (long int *)calloc(3*slen/4, sizeof(long int));
    bytes.length = 3*slen/4;

    for(i=0;i<slen;i++)
    {
        b64val = decode_base64_char(base64str[i]);

        //printf("0x%x %d\n", b64val, b64val);
        //getchar();

        if(-1!=b64val)
        {
                if(0==(i%4))
                    b64val <<= 18;
                else if(1==(i%4))
                    b64val <<= 12;
                else if(2==(i%4))
                    b64val <<= 6;

                //printf("0x%x\n", b64val);
                //getchar();

                tmpnum += b64val;
        }
        else
        {
            fprintf(stderr, "This is not a base64 string!\n");
            bytes.length = -1;

            return bytes;
        }

        if(3==(i%4))
        {
            printf("%d 0x%x\n", i, tmpnum);

            bytes.bytes[i-2] = tmpnum&0xff0000;
            bytes.bytes[i-2] >>= 16;
            printf("0x%x\n", bytes.bytes[i-2]);

            bytes.bytes[i-1] = tmpnum&0x00ff00;
            bytes.bytes[i-1] >>= 8;
            printf("0x%x\n", bytes.bytes[i-1]);

            bytes.bytes[i] = tmpnum&0x0000ff;
            printf("0x%x\n", bytes.bytes[i]);

            tmpnum = 0;
        }
    }

    return bytes;
}

/*
*   A simple function to decode the base64 characters back to integers.
*/
int decode_base64_char(char ch)
{
    int val;

    if('+'==ch)
        return 62;
    else if('/'==ch)
        return 63;
    else if('='==ch)
        return 0;
    else if((64<ch)||(91>ch))
        return (int )(ch-65);
    else if((96<ch)||(123>ch))
        return (int )(ch-66);

    return -1;
}

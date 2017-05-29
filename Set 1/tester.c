#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "functions.h"

int main(int argc, char *argv[])
{
    //char * teststr = "324dfe2356e2fcee";
    char * base64;
    hex original;

    //printf("%s", teststr);
    //getchar();

    //hex testhex = decodehex(argv[1]);
    hex testhex = string2hex(argv[1]);

    //printf("Hexstr:%s\n", hex2string(testhex, 0));

    base64 = base64_encode(testhex);

    printf("%s\n", base64);

    original = base64_decode(base64);
	
	//base64 = hex2string(original, 1);

    //printf("%s\n", base64);

    free(original.bytes);
    free(testhex.bytes);

    return 0;
}

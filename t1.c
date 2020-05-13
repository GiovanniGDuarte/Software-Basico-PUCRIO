  /* Giovanni Gomes Duarte Zavarise - 1720602 - Turma: 3WB */
#include <stdio.h>
#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS/8];
#include "biblio.h"






int main(void)
{	

	BigInt primArray={0X00, 0x00, 0X00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    	//BigInt segArray= {0x00, 0x00, 0X00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    	BigInt final = {};
	big_sar(final, primArray,10);
	printf("\n\n");

  
	printf("\nPrimeiro:\t");
	int a=0;
	while(a<16){
		printf(" %02x ",primArray[a]);
		a++;
	}
	/*
	printf("\nSegundo:\t");
	int b=0;
	while(b<16){
		printf(" %02x ",segArray[b]);
		b++;;
	}
*/
	printf("\nFinal:\t\t");
	int c=0;
	while(c<16){
		printf(" %02x ",final[c]);
		c++;;
	}
	
	
	printf("\n\n\n");
   	 return 0;
}

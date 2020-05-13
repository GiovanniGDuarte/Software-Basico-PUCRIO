#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS/8];
#include "biblio.h"
#include <stdio.h>

/* Atribuicao */

/*res = val (extensao com sinal)*/
void big_val (BigInt res, long val){
	unsigned char *p = (unsigned char *) &val;
	int i;
	
	for(i=0;i<8;i++){
		res[i] = *p;
		p++;
	}
	if(val < 0){
		for(i=8;i<16;i++){
			res[i] = 0x00;
		}
	}
	else{
		for(i=8;i<16;i++){
			res[i] = 0xFF;
		}
	
	}
	return;	
}



/* Operacoes aritmeticas */

/* res = -a */
void big_comp2(BigInt res, BigInt a){
	int i;
	for(i=0;i<16;i++){
		res[i] = ~(a[i]);
	}
	res[0] += 0x01;
}

/*
res = a + b */
void big_sum (BigInt res, BigInt a, BigInt b){
	int i, soma=0, vai1 = 0;
	for(i=0; i<15; i++){
		soma = a[i] + b[i] + vai1;
		res[i] = soma;
		vai1 = soma >> 8;			
	}
	return;
}

/*res = a - b*/
void big_sub (BigInt res, BigInt a, BigInt b){
	//A subtracao de A e B, basicamento eh a soma de A 
	//			com complemento a2 de B.
	
	BigInt comp_b; //Criando o Array do complemento de B
	
	big_comp2(comp_b, b);	//Guardando o complemento
	
	big_sum(res, a, comp_b); //Somando o complemento e o A
}


/*res = a * b */
void big_mul(BigInt res, BigInt a, BigInt b)
{
  BigInt p = {};
  BigInt auxArray= {};
  BigInt auyArray= {};
  int i,k=0;
  for(i=0;i<=15;i++)
  {
  	auxArray[i]=a[i];
  	auyArray[i]=b[i];
  	if (auyArray[i]!= 0)
  		k+=1;
  }

  while (k)
  {
    if (auyArray[0]%2 == 1)//se impar
      big_sum(p,p,a);//p += a;
    big_sar(auxArray,auxArray,2);// a*= 2;
    big_shr(auyArray,auyArray, 2);//b /= 2;
  }
}


/*Operacoes de deslocamento 

 res = a << n */
void big_shl (BigInt res, BigInt a, int n){
	
	int i, nByte,nBit;
	int bloco=0, casas=0, vai = 0;
	nByte = n/8; 	//separando em blocos/byte
	nBit = n%8;	//separando em casas/bits
	
	if(n < 8){	//Se n for menor que 8, volta casas:
		for(i=0; i < 16; i++){
			res[i]  = (a[i] << (nBit)) - vai;
			vai = a[i] >>(8-nBit);
		}
	}
	if(n%8 == 0){	//Se n for multiplo de 8, andar blocos:
		for(i=0; i < 16; i++){
			res[i - nByte]  = a[i] ;
		}
	}
	else{		//Entao n eh maior que 8 e nao multiplo
			//Separar para ver quantos bloco andar e depois casas
			//nByte sao os blocos e nBit sao as casas
		bloco = nByte;
		casas = nBit;
		while(bloco > 0){	//Shiftando em blocos
			for(i=0; i < 16; i++){
				res[i - nByte]  = a[i] ;
			}
			bloco--;		
		}
		while(casas > 0){	//Shiftando em casas
			for(i=0; i < 16; i++){
				res[i]  = (a[i] << (nBit)) + vai;
				vai = a[i] >> (8-nBit);
			}
			casas--;		
		}
	}	
}



/* res = a >> n (logico)*/

void big_shr (BigInt res, BigInt a, int n){
	
	int i, nByte,nBit;
	int bloco=0, casas=0, vai = 0;
	nByte = n/8; 	//separando em blocos/byte
	nBit = n%8;	//separando em casas/bits
	
	if(n < 8){	//Se n for menor que 8, andar casas:
		for(i=0; i < 16; i++){
			res[i]  = (a[i] >> (nBit)) + vai;
			
			vai = a[i] <<(8-nBit);
		}
	}
	else if(n%8 == 0){	//Se n for multiplo de 8, andar blocos:
		for(i=0; i < 16; i++){
			res[i + nByte]  = a[i] ;
		}
	}
	else{		//Entao n eh maior que 8 e nao multiplo
			//Separar para ver quantos bloco andar e depois casas
			//nByte sao os blocos e nBit sao as casas
		bloco = nByte;
		casas = nBit;
		while(bloco > 0){	//Shiftando em blocos
			for(i=0; i < 16; i++){
				res[i + nByte]  = a[i] ;
			}
			bloco--;		
		}
		while(casas > 0){	//Shiftando em casas
			for(i=0; i < 16; i++){
				res[i]  = (a[i] >> (nBit)) + vai;
				vai = a[i] << (8-nBit);
			}
			casas--;		
		}
	}	
}


/*res = a >> n (aritmetico) */
void big_sar (BigInt res, BigInt a, int n){
	
	int i, nByte,nBit;
	int bloco=0, casas=0, vai = 0;
	nByte = n/8; 	//separando em blocos/byte
	nBit = n%8;	//separando em casas/bits
	
	if(n < 8){	//Se n for menor que 8, andar casas:
		for(i=0; i < 16; i++){
			res[i]  = (a[i] >> (nBit)) + vai;
			vai = a[i] <<(8-nBit);
			if( (a[i]&0x80) == 0x80){
				res[i] = (res[i]| 0xFF);
			}
			
		}
	}
	else if(n%8 == 0){	//Se n for multiplo de 8, andar blocos:
		for(i=0; i < 16; i++){
			res[i + nByte]  = a[i];
			if( (a[i]&0x80) == 0x80){
				res[i] = (res[i]| 0xFF);
			}
		}
	}
	else{		//Entao n eh maior que 8 e nao multiplo
			//Separar para ver quantos bloco andar e depois casas
			//nByte sao os blocos e nBit sao as casas
		bloco = nByte;
		casas = nBit;
		while(bloco > 0){	//Shiftando em blocos
			for(i=0; i < 16; i++){
				res[i + nByte]  = a[i] ;
				if( (a[i]&0x80) == 0x80){
					res[i] = (res[i]| 0xFF);
				}
			}
			bloco--;		
		}
		while(casas > 0){	//Shiftando em casas
			for(i=0; i < 16; i++){
				res[i]  = (a[i] >> (nBit)) + vai;
				vai = a[i] << (8-nBit);
				if( (a[i]&0x80) == 0x80){
					res[i] = (res[i]| 0xFF);
				}
			}
			casas--;		
		}
	}	
}


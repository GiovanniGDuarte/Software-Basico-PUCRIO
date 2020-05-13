/* Atribuição (com extensão):
A função big_val atribui a res o valor fornecido por l (um signed long), corretamente estendido para 128 bits. */
void big_val (BigInt res, long val);

/* Operações Aritméticas 
A função big_comp2 atribui a res o valor "negado" (complemento a 2) de a. */

/* res = -a 	*/
void big_comp2(BigInt res, BigInt a);

/* res = a + b 
Operacao de soma	*/
void big_sum(BigInt res, BigInt a, BigInt b);

/* res = a - b
Operacao de subtracao	*/
void big_sub(BigInt res, BigInt a, BigInt b);

/* res = a * b 
Operacao de multiplicacao	*/
void big_mul(BigInt res, BigInt a, BigInt b);

/* Operações de Deslocamento */

/* res = a << n */
void big_shl(BigInt res, BigInt a, int n);

/* res = a >> n (lógico)*/
void big_shr(BigInt res, BigInt a, int n);

/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n);

#ifndef SJ_H
#define SJ_H 

typedef struct scj_ scj;

/*Construi uma lista de subconjuntos de tamnho 2^n
 
Arugumento:
	int n : numero de elementos para se criar uma lista de 
	todos subconjuntos possiveis

Retorna uma lista de subconjuntos 
*/
scj* construir_scj(int n);

//Insere um subconjunto em uma lista de subconjuntos 
void push_scj(scj* scj, int val);

//Retorna a capacidade total da lista de subconjuntos 
int tamanho_scj(scj* scj);

//Retorna o numero total de elementos inseridos na lista de adjacencia
int ultimo_scj(scj* scj);

//Retorna o conjunto no index especificado
int sub_pos_scj(scj* scj, int index);

//Destroi a lista de subconjuntos dando free em todos os elementos que ele possue
void destruir_scj(scj* scj);

#endif


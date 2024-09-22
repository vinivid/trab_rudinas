#ifndef LS_H
#define LS_H

#include <stdbool.h>

typedef struct lsc_ lsc;

//Constroi um lista encadeada sem nenhum valor especifico
lsc* construir_lsc();
//Libera o espaço alocado pela lista e os dados contidos nela.
void destruir_lsc(lsc* lsc);

/* Insere um novo nó que representa a cidade a ser uma conexão
 com o nó.

 A funcao pode ter excessoes retornando 0 quando ocorre
 com sucesso, 1 quando foi incapaz de alocar um novo nó, 2 quando 
 a lista de entrada foi nula.
 */
int inserir_lsc(lsc* lsc, int num_cidade, int custo);

/* Procura na lista a cidade do número dado e retorna o 
 custo de ir para ela a partir da cidade associada a lista.

 Retorna -1 caso o num_cidade não seja encontrado;
 */
int cidade_numero_lsc(lsc* lsc, int num_cidade);

/*retorna a quantidade total de nós na lista, se a lista nao
 exisitir retorna -1;
 */
int tamaho_lsc(lsc* lsc);

/*Retorna real se estiver vazia ou a lista for nula 
falso caso possua cidades nela.
*/
bool vazia_lsc(lsc* lsc);

#endif

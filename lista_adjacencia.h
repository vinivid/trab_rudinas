#ifndef LSA_H
#define LSA_H

typedef struct lsa_ lsa;

/*Constroi uma lista de adjacencia com a quantidade
 de cidades passada como argumento.
*/
lsa* construir_lsa(int qtd_cidades);

//Libera o espaço alocado pela lista e os dados contidos nela.
void destruir_lsa(lsa* lsa);

/* Insere na lista de adjacencia o custo de ir de uma
 cidade a para uma cidade b, o contrario tambem é 
 inserido. Alem disso NAO se pode inserir uma cidade de numero "0".
 Qualquer numero além da quantidade de cidades trara um SEGV.

 Retorna 0 quando obteve sucesso, -1 quando nao existe a lista de 
 adjacencia e -2 quando tenta se inserir uma cidade de numero "0".
 */
int inserir_lsa(lsa* lsa, int cidade_a, int cidade_b, int custo);

/* Retorna o custo de ir da cidade a para a cidade b. 
 Se a cidade a for igual a cidade b ele retorna zero.
 Se a cidade a não tiver conexao com a cidade b retorna -1.
 */
int custo_a_b_lsa(lsa* lsa, int cidade_a, int cidade_b);

/* Retorna a quantidade de cidades que serão armazenadas
 na lista de adjacencia. 
 
 Retorna -1 se a lista não existir.
 */
int qtd_cidades_lsa(lsa* lsa);

#endif

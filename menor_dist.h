#ifndef MD_H
#define MD_H

#include "lista_adjacencia.h"

/*
 A struct mapa representa as condicoes do problema dada pelo usuario 
 contendo nela todas as informações necessarias para se calcular o 
 caminho mais curto.
 */
typedef struct mapa_ {
	lsa* lista_mapa;
	int* perm_inicial;
	int tam;
}mapa;

/*
 A struct resposta representa o que foi computado após a computar 
 a a menor distância no mapa dado pelo usuario.
 */
typedef struct resposta {
	int* permutacao;
	int menor_dist;
}res;

/*
 Le as entradas do programa e retorna uma struct mapa das informações dadas pelo usuario
 nela contendo todas as conexoes em uma lista de adjacencia, uma permutacao inicial que 
 na primeira posicao contem a cidade de incio e todas as outras cidades. Exemplo:
 	n_cidades = 5; cidade_final = 2; isso criara a seguinte permutação inicial 
	{2, 1, 3, 4, 5}

também retorna junto ao mapa a quantidade de cidades.
 */
mapa ler_entrada();

/*
 Computa o caminho mais curto a partir das informações dadas por um mapa.

  
 */
res caminho_mais_curto (int tam, int* arr, lsa* lsa);

void printar_resposta(int tam, res resposta);

#endif

#ifndef MD_H
#define MD_H

#include "lista_adjacencia.h"

typedef struct mapa_ {
	lsa* lista_mapa;
	int* perm_inicial;
	int tam;
}mapa;

typedef struct resposta {
	int* permutacao;
	int menor_dist;
}res;

mapa ler_entrada();

res caminho_mais_curto (int tam, int* arr, lsa* lsa);

void printar_resposta(int tam, res resposta);

#endif

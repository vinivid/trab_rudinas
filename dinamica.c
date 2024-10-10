#include "dinamica.h"

#include "lista_adjacencia.h"
#include "menor_dist.h"
#include "subconjuntos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool naoTaAi(int prox, int subconjunto);
void criar_subconjuntos(int conjunto, int at, int r, int n, scj* subconjuntos);
scj* combinacoes (int rota, int tamanho);
int achaMelhorCusto(int tamanho, int inicio, int **memo, lsa *lsa);
int* achaMelhorRota(int tamanho, int inicio, int **memo, lsa *lsa);

res dinamica(int tamanho, int *caminho, lsa *lsa) {
    int inicio = caminho[0];
    
    int **memo = malloc(tamanho * sizeof(int*));

	if (!memo) {printf("\n\nERRO::FALHA NA ALOCACAO\n\n");}

    for(int i = 0; i < tamanho; i++) {
        memo[i] = calloc((1 << tamanho), sizeof(int));
    }

    for(int i = 0; i < tamanho; i++) {
        if(i == inicio) continue;
        memo[i][1 << inicio | 1 << i] = custo_a_b_lsa(lsa, inicio, i + 1);
    }

    for(int rota = 3; rota <= tamanho; rota++) {
		scj* combs = combinacoes(rota, tamanho);

		for (int i = 0; i < ultimo_scj(combs); ++i) {
			printf("comb[%d] = %d\n", i, sub_pos_scj(combs, i));
		}

        for(int sub = 0; sub < ultimo_scj(combs); ++sub){
            if(naoTaAi(inicio, sub_pos_scj(combs, sub))) continue;

            for(int prox = 0; prox < tamanho; prox++) {
                if (prox == inicio || naoTaAi(prox, sub_pos_scj(combs, sub))) continue;
				
				printf("estado amaldiçoado %d\n\n", sub_pos_scj(combs, sub));
                int estado = sub_pos_scj(combs, sub) ^ (1 << prox);
                int minDist = 2147483000;
				
				printf("\n\nChegou aqui   1\n\n");
                for(int i = 0; i < tamanho; i++) {
                    if(i == inicio || naoTaAi(i, sub_pos_scj(combs, sub)) || i == prox) continue;
					
					int novaDist = 0;
					printf("estado %d \n", estado);
					if (custo_a_b_lsa(lsa, i + 1, prox + 1) == -1) {
                    	novaDist = memo[i][estado] + 0;
					} else {
						novaDist = memo[i][estado] + custo_a_b_lsa(lsa, i + 1, prox + 1);
					}
                    if(novaDist < minDist) minDist = novaDist;
                }
				
				printf ("prox: %d\n", prox);
                memo[prox][sub_pos_scj(combs, sub)] = minDist;
            }
        }

		destruir_scj(combs);
    }
	
	res resposta;
    resposta.menor_dist = achaMelhorCusto(tamanho, inicio, memo, lsa);
    resposta.permutacao = achaMelhorRota(tamanho, inicio, memo, lsa);

	for (int i = 0; i < tamanho; ++i) free(memo[i]);
	free(memo);

	return resposta;
}

bool naoTaAi(int check, int subconjunto) {
    return !((1 << check) & subconjunto);
}

void criar_subconjuntos(int conjunto, int at, int r, int n, scj* subconjunto) {
	if (!r) {
		push_scj(subconjunto, conjunto);
	} else {
		for (int i = at; i < n; ++i) {
			conjunto = conjunto | (1 << i);

			criar_subconjuntos(conjunto, i + 1, r - 1, n, subconjunto);

			conjunto = conjunto & ~(1 << i);
		}
	}
}

scj* combinacoes (int rota, int tamanho) {
	scj* tmp = construir_scj(tamanho);
	criar_subconjuntos(0, 0, rota, tamanho, tmp);

	return tmp;
}

int achaMelhorCusto(int tamanho, int inicio, int **memo, lsa *lsa) {
    int estadoFinal = (1 << tamanho) - 1;
    int custoMinimo = 2147483000;
	printf("estado final %d\n", estadoFinal);
    for(int i = 1; i <= tamanho; i++) {
        if(i == inicio) continue;
		
		printf("custo wtf %d\n\n",  custo_a_b_lsa(lsa, i, inicio));
		
		if (custo_a_b_lsa(lsa, i, inicio) == -1) continue;
		printf("index do memo %d custo bizarro do memo %d\n", i - 1 ,memo[i - 1][estadoFinal]);
        int custo = memo[i - 1][estadoFinal] + custo_a_b_lsa(lsa, i, inicio);
        if(custo < custoMinimo) {
            custoMinimo = custo;
        }
    }

    return custoMinimo;
}

int* achaMelhorRota(int tamanho, int inicio, int **memo, lsa *lsa) {
    int ultimo = inicio;
    int estado = (1 << tamanho) - 1;
    int *rota = malloc((tamanho+1)*sizeof(int));

    for(int i = tamanho-1; i >= 1; i--) {
        int indice = -1;

        for(int j = 0; j < tamanho; j++) {
            if(j == inicio || naoTaAi(j, estado)) continue;

            if(indice == -1) indice = j;
			
			printf("dist do indice i %d e j %d e o ultimo %d\n\n", indice + 1, j + 1, ultimo + 1);
            int distanciaPrevia = memo[indice][estado] + custo_a_b_lsa(lsa, indice + 1, ultimo);
            int distanciaNova = memo[j][estado] + custo_a_b_lsa(lsa, j + 1, ultimo);

            if(distanciaNova < distanciaPrevia) indice = j;
        }

        rota[i] = indice;
        estado = estado ^ (1 << indice);
        ultimo = indice;
    }

    rota[0] = rota[tamanho] = inicio;
    return rota;
}

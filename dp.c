#include "held_lista.h"
#include "subconjuntos.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct mapa_ {
	lsa* lista_mapa;
	int tam;
	int cidade_origiem;
}mapa;

typedef struct resposta {
	int* permutacao;
	int menor_dist;
}res;

mapa ler_entrada();
void swap (int* a, int* b);
void cpy_arr (int tam, int* a, int* b);
void printar_resposta(int tam, res resposta, int cidade_origem);

bool naoTaAi(int prox, int subconjunto);
void criar_subconjuntos(int conjunto, int at, int r, int n, scj* subconjuntos);
scj* combinacoes (int rota, int tamanho);
int achaMelhorCusto(int tamanho, int inicio, int **memo, lsa *lsa);
int* achaMelhorRota(int tamanho, int inicio, int **memo, lsa *lsa);
res dinamica(int tamanho, lsa* lsa);

int main (void) {
	mapa omapa = ler_entrada();
	clock_t a, b;
	a = clock();
	res answ = dinamica(omapa.tam, omapa.lista_mapa);
	b = clock();
	printf("%d %lf\n", omapa.tam, (double)(b - a)/CLOCKS_PER_SEC);
	//printar_resposta(omapa.tam, answ, omapa.cidade_origiem);
}

res dinamica(int tamanho, lsa *lsa) {
    int inicio = 0;
    
    int **memo = malloc(tamanho * sizeof(int*));

	if (!memo) {printf("\n\nERRO::FALHA NA ALOCACAO\n\n");}

    for(int i = 0; i < tamanho; i++) {
        memo[i] = calloc((1 << tamanho), sizeof(int));
    }

    for(int i = 0; i < tamanho; i++) {
        if(i == inicio) continue;
        memo[i][1 << inicio | 1 << i] = custo_a_b_lsa(lsa, inicio, i);
    }

    for(int rota = 3; rota <= tamanho; rota++) {
		scj* combs = combinacoes(rota, tamanho);

        for(int sub = 0; sub < ultimo_scj(combs); ++sub){
            if(naoTaAi(inicio, sub_pos_scj(combs, sub))) continue;

            for(int prox = 0; prox < tamanho; prox++) {
                if (prox == inicio || naoTaAi(prox, sub_pos_scj(combs, sub))) continue;
                int estado = sub_pos_scj(combs, sub) ^ (1 << prox);
                int minDist = 2147483000;
				
                for(int i = 0; i < tamanho; i++) {
                    if(i == inicio || i == prox || naoTaAi(i, sub_pos_scj(combs, sub)) ) continue;
					
					if (custo_a_b_lsa(lsa, i, prox) == 0) continue;

					int novaDist = memo[i][estado] + custo_a_b_lsa(lsa, i, prox);
                    if(novaDist < minDist) { 
						minDist = novaDist;
					}
                }
				
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

	destruir_lsa(lsa);
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
    for(int i = 0; i < tamanho; i++) {
        if(i == inicio) continue;
		
        int custo = memo[i][estadoFinal] + custo_a_b_lsa(lsa, i, inicio);
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
			
            int distanciaPrevia = memo[indice][estado] + custo_a_b_lsa(lsa, indice, ultimo);
            int distanciaNova = memo[j][estado] + custo_a_b_lsa(lsa, j, ultimo);

            if(distanciaNova < distanciaPrevia) indice = j;
        }

        rota[i] = indice;
        estado = estado ^ (1 << indice);
        ultimo = indice;
    }

    rota[0] = rota[tamanho] = inicio;
    return rota;
}

mapa ler_entrada() {
	int n_cidades;
	int cidade_final;
	int estradas;
	scanf("%d", &n_cidades);

	lsa* conexoes = construir_lsa(n_cidades);
	
	scanf("%d", &cidade_final);
	scanf("%d", &estradas);

	for (int i = 0; i < estradas; ++i) {
		int cidade_a;
		int cidade_b;
		int distancia;

		scanf("%d %d %d", &cidade_a, &cidade_b, &distancia);

		inserir_lsa(conexoes, cidade_a - 1, cidade_b - 1, distancia);
	}
	
	mapa res = {conexoes, n_cidades, cidade_final};
	return res;
}

void printar_resposta(int tam, res resposta, int cidade_origiem) {
	printf("\nCidade de origem: %d\n", cidade_origiem);
	
	for (int i = 0; i < tam + 1; ++i) {++resposta.permutacao[i];}

	printf("Rota: ");

	while (resposta.permutacao[0] != cidade_origiem) {
		int tmp = resposta.permutacao[0];
		for (int i = 0; i < tam; i++)
			resposta.permutacao[i] = resposta.permutacao[i + 1];
		resposta.permutacao[tam-1] = tmp;
	}

	resposta.permutacao[tam] = cidade_origiem;

	for (int i = 0; i < tam; ++i) {
		printf("%d - ", resposta.permutacao[i]);
	}

	printf("%d\n", resposta.permutacao[0]);
	
	printf("Menor distância: %d\n", resposta.menor_dist);

	free(resposta.permutacao); resposta.permutacao = NULL;
}

#include "menor_dist.h"

#include <stdio.h>
#include <stdlib.h>
#include "lista_adjacencia.h"

void swap (int* a, int* b);

/*
Copia o arr a para o array b, os dois arrays precisam ter o mesmo tamnho.
 */ 
void cpy_arr (int tam, int* a, int* b);
int dist_tot_perm (int tam, int* arr, lsa* lsa);

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

	int* perm_inicial = (int *)malloc(n_cidades * sizeof(int));
	
	if (!perm_inicial) printf("\n\nERRO::FALHA NA ALOCACAO\n\n");
	
	perm_inicial[0] = cidade_final;
	
	int index = 0;
	for (int i = 0; i < n_cidades; ++i) {
		if (i == cidade_final - 1)
			continue;

		perm_inicial[index] = i;
		++index;
	}
	
	mapa res = {conexoes, perm_inicial, n_cidades};
	return res;
}

res caminho_mais_curto (int tam, int* arr, lsa* lsa) {
	int* sub_arr = arr + 1;
	int* c = (int *)malloc(tam * sizeof(int));

	res resp;
	resp.permutacao = (int *)malloc(tam * sizeof(int));
	resp.menor_dist = -1;

	if (!c || !resp.permutacao) {
		//Deixar dar segfault apos falha na alocacao e mais
		//seguro
		printf("\n\nERRO::FALHA NA ALOCACAO\n\n");
	}
	
	for (int i = 0; i < tam - 1; ++i)
		c[i] = 0;
	
	cpy_arr(tam, arr, resp.permutacao);
	resp.menor_dist = dist_tot_perm(tam, arr, lsa);

	int i = 1;

	while (i < tam - 1) {
		if (c[i] < i) {
			if (!(i%2)) {
				swap(&sub_arr[0], &sub_arr[i]);
			} else {
				swap(&sub_arr[c[i]], &sub_arr[i]);
			}
				
			int val_perm = dist_tot_perm(tam, arr, lsa);

			if ((resp.menor_dist == -1 && val_perm > -1)  || (val_perm != -1 && val_perm < resp.menor_dist)) {
				resp.menor_dist = val_perm;
				cpy_arr(tam, arr, resp.permutacao);
			}

			c[i] += 1;
			i = 1;
		} else {
			c[i] = 0;
			i += 1;
		}
	}
	
	free(c); c = NULL;
	free(arr); arr = NULL;
	destruir_lsa(lsa);

	return resp;
}

void printar_resposta(int tam, res resposta) {
	printf("\nCidade de origem: %d\n", resposta.permutacao[0]);
	
	printf("Rota: ");
	for (int i = 0; i < tam; ++i) {
		printf("%d - ", resposta.permutacao[i]);
	}

	printf("%d\n", resposta.permutacao[0]);
	
	printf("Menor distância: %d\n", resposta.menor_dist);

	free(resposta.permutacao); resposta.permutacao = NULL;
}

int dist_tot_perm (int tam, int* arr, lsa* lsa) {
	int total = 0;

	for (int i = 0; i < tam - 1; ++i) {
		int entre = custo_a_b_lsa(lsa, arr[i], arr[i + 1]);

		if (entre == 0)
			return -1;

		total += entre;
	}

	int entre = custo_a_b_lsa(lsa, arr[0], arr[tam - 1]);

	if (entre == 0)
		return -1;

	total += entre;

	return total;
}

void cpy_arr (int tam, int* a, int* b) {
	for (int i = 0; i < tam; ++i)
		b[i] = a[i];
}

void swap (int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

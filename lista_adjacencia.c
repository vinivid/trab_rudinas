#include "lista_adjacencia.h"

#include <stdlib.h>
#include <stdio.h>
#include "lista_encadeada.h"

struct lsa_ {
	lsc** container;
	int qtd_cidades;
};

lsa* construir_lsa(int qtd_cidades) {
	lsa* tmp = (lsa *)malloc(sizeof(lsa));

	if (!tmp) {
		printf("\n\nERRO::FALHA NA ALOCACAO DE MEMORIA\n\n");
		return NULL;
	}

	tmp->container = (lsc**)malloc(qtd_cidades * sizeof(lsc*));

	if (!tmp->container) {
		printf("\n\nERRO::FALHA NA ALOCACAO DE MEMORIA\n\n");
		return NULL;
	}

	tmp->qtd_cidades = qtd_cidades;
	
	//Nao tratar o erro por falta de memoria porque nao seria recuperavel
	//no caso deste programa, e melhor crashar.
	for (int i = 0; i < qtd_cidades; ++i) {
		tmp->container[i] = construir_lsc();
	}

	return tmp;
}

void destruir_lsa(lsa* lsa) {
	if (lsa) {
		for (int i = 0; i < lsa->qtd_cidades; ++i) {
			destruir_lsc(lsa->container[i]);
		}
		
		free(lsa->container);
		free(lsa); lsa = NULL;
	} else 
		return;
}

int inserir_lsa(lsa* lsa, int cidade_a, int cidade_b, int custo) {
	if (cidade_a == 0 || cidade_b == 0) {
		return -2;
	} else if (lsa) {
		return inserir_lsc(lsa->container[cidade_a - 1], cidade_b, custo); 
	} else 
		return -1;
}

int custo_a_b_lsa(lsa* lsa, int cidade_a, int cidade_b) {
	if (cidade_a == cidade_b) {
		return 0;
	} else if (lsa) {
		return cidade_numero_lsc(lsa->container[cidade_a - 1], cidade_b);
	} else 
		return -1;
}

int qtd_cidades_lsa(lsa* lsa) {
	if (lsa) {
		return lsa->qtd_cidades;
	} else 
		return -1;
}

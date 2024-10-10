#include "lista_adjacencia.h"

#include <stdlib.h>
#include <stdio.h>
#include "lista_encadeada.h"

struct lsa_ {
	lsc** container;
	int qtd_cidades;
};

//Constroi uma lista e inicializa cada um de seus componentes
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
	
	for (int i = 0; i < qtd_cidades; ++i) {
		tmp->container[i] = construir_lsc();
	}

	return tmp;
}

//Libera todos os conteudos contidos na lista de adjacencia 
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
//Insere em uma lista de adjacencia a conexão de a com b assim como b com a 
int inserir_lsa(lsa* lsa, int cidade_a, int cidade_b, int custo) {
	 if (lsa) {
		inserir_lsc(lsa->container[cidade_a], cidade_b, custo);
		inserir_lsc(lsa->container[cidade_b], cidade_a, custo);
		return 0;
	} else 
		return -1;
}

//Retorna a distancia entre uma cidade a e uma cidade b 
int custo_a_b_lsa(lsa* lsa, int cidade_a, int cidade_b) {
	if (cidade_a == cidade_b) {
		return 0;
	} else if (lsa){
		return cidade_numero_lsc(lsa->container[cidade_a], cidade_b);
	} else {
		return -1;
	}
}

//Retorna a quantidade de cidades contidas na lista de adjacencia
int qtd_cidades_lsa(lsa* lsa) {
	if (lsa) {
		return lsa->qtd_cidades;
	} else 
		return -1;
}

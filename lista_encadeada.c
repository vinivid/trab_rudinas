#include "lista_encadeada.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct no_ no;

struct no_ {
	int num_cidade;
	int custo;
	no* prox;
};

struct lsc_ {
	no* inicio;
	no* fim;
	int tamanho;
};

lsc* construir_lsc() {
	lsc* tmp = (lsc *)malloc(sizeof(lsc));

	if (!tmp) {
		printf("\n\nERRO::FALHA NA ALOCACAO DE MEMORIA\n\n");
		return NULL;
	}

	tmp->inicio = NULL;
	tmp->fim = NULL;
	tmp->tamanho = 0;

	return tmp;
}

void destruir_lsc(lsc* lsc) {
	while (lsc->inicio) {
		no* tmp = lsc->inicio;
		lsc->inicio = lsc->inicio->prox;
		free(tmp);
	}

	free(lsc); lsc = NULL;
}

int inserir_lsc(lsc* lsc, int num_cidade, int custo) {
	if (lsc) {
		if (lsc->tamanho) {
			no* novo_no = (no *)malloc(sizeof(no));
			
			if (!novo_no) {
				printf("\n\nERRO::FALHA NA ALOCACAO DE MEMORIA\n\n");
				return 1;
			}

			lsc->fim->prox = novo_no;
			lsc->fim = novo_no;

			lsc->fim->num_cidade = num_cidade;
			lsc->fim->custo = custo;
			lsc->fim->prox = NULL;

			++lsc->tamanho;

			return 0;
		} else {
			no* novo_no = (no *)malloc(sizeof(no));
			
			if (!novo_no) {
				printf("\n\nERRO::FALHA NA ALOCACAO DE MEMORIA\n\n");
				return 1;
			}

			lsc->inicio = novo_no;
			lsc->fim = novo_no;

			lsc->fim->num_cidade = num_cidade;
			lsc->fim->custo = custo;
			lsc->fim->prox = NULL;
			
			++lsc->tamanho;

			return 0;
		}
	} else {
		return 2;
	}
}

int cidade_numero_lsc(lsc* lsc, int num_cidade) {
	if (lsc) {
		no* next = lsc->inicio;

		while (next) {
			if (next->num_cidade == num_cidade)
				return next->custo;

			next = next->prox;
		}

		return -1;
	} else {
		return -1;
	}	
}

int tamanho_lsc(lsc* lsc) {
	if (lsc) {
		return lsc->tamanho;
	} else {
		return -1;
	}	
}

bool vazia_lsc(lsc* lsc) {
	if (lsc) {
		return lsc->tamanho ? false:true;	
	} else {
		return true;
	}
}

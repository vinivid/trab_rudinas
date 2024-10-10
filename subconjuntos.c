#include "subconjuntos.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct scj_ {
	int* arr_subconjuntos;
	int tamanho;
	int ultimo;
};

scj* construir_scj(int n) {
	scj* tmp = (scj *)malloc(sizeof(scj));
	
	if (!tmp) {printf("\n\nERRO::FALAHA EM ALOCAR\n\n"); return NULL;}
	
	tmp->tamanho = n * (int)pow(2, n);
	tmp->arr_subconjuntos = (int *)malloc(sizeof(int) * tmp->tamanho);
	
	tmp->ultimo = 0;

	return tmp;
}

void push_scj(scj* scj, int val) {
	if (scj) {
		if (scj->ultimo == scj->tamanho) {
		} else {
			scj->arr_subconjuntos[scj->ultimo] = val;
			++scj->ultimo;
		}
	}
}

int tamanho_scj(scj* scj) {
	if (scj) {
		return scj->tamanho;
	} else {
		return 0;
	}	
}

int sub_pos_scj(scj* scj, int index) {
	if (scj) {
		return scj->arr_subconjuntos[index];
	} else {
		return 0;
	}
}

void destruir_scj(scj* scj) {
	if (scj) {
		free(scj->arr_subconjuntos);

		free(scj); scj = NULL;
	} else {
		return;
	}
}

int ultimo_scj(scj* scj) {
	if (scj) {
		return scj->ultimo;
	} else {
		return 0;
	}
}

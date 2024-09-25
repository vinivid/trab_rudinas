#include <stdio.h>
#include <stdlib.h>
#include "lista_adjacencia.h"

typedef struct resposta {
	int* permutacao;
	int distancia_total;
}res;

void swap (int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//Copia o array a no b, os dois tem de ter o mesmo tamanho
void cpy_arr (int tam, int* a, int* b) {
	for (int i = 0; i < tam; ++i)
		b[i] = a[i];
}


void output (int n, int *a) {
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}

	printf("\n");
}

//Calcula a distancia total de uma permutacao
int dist_tot_perm (int tam, int* arr, lsa* lsa) {
	int total = 0;

	for (int i = 0; i < tam - 1; ++i) {
		int entre = custo_a_b_lsa(lsa, arr[i], arr[i + 1]);

		if (entre == -1)
			return -1;

		total += entre;
	}

	int entre = custo_a_b_lsa(lsa, arr[0], arr[tam - 1]);

	if (entre == -1)
		return -1;

	total += entre;

	return total;
}
//Algoritimo de heap para calcular todas as permutacoes possiveis de uma palavra
//modificado um pouco para calcular as distancias.
/*Dada uma permutacao se calcula ela se seu valor for menor que o calculado ate 
 agora se coloca essa permutacao como a que é a mais rapida se nao só vai para 
 a proxima.
 */
void caminho_mais_curto (int tam, int* arr, lsa* lsa) {
	int* sub_arr = arr + 1;
	int* c = (int *)malloc(tam * sizeof(int));

	res resp;
	resp.permutacao = (int *)malloc(tam * sizeof(int));
	resp.distancia_total = 0;

	if (!c || !resp.permutacao) {
		//Deixar dar segfault apos falha na alocacao e mais
		//seguro
		printf("\n\nERRO::FALHA NA ALOCACAO\n\n");
	}
	
	for (int i = 0; i < tam - 1; ++i)
		c[i] = 0;
	
	cpy_arr(tam, arr, resp.permutacao);
	dist_tot_perm()

	int i = 1;

	while (i < tam - 1) {
		if (c[i] < i) {
			if (!(i%2)) {
				swap (&sub_arr[0], &sub_arr[i]);
			} else {
				swap (&sub_arr[c[i]], &sub_arr[i]);
			}
			
			//Uma permutacao ocorre aqui
			output(tam, arr);
			c[i] += 1;
			i = 1;
		} else {
			c[i] = 0;
			i += 1;
		}
	}

}

int main (void) {
	int a[4] = {1,2,3,4};
	int tam = 4;

	caminho_mais_curto(tam, a);
}

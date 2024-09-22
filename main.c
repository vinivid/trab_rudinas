#include <stdio.h>
#include <stdlib.h>

#include "lista_adjacencia.h"

int main(void) {
	lsa* tst = construir_lsa(3);
	
	inserir_lsa(tst, 1, 3, 5);
	inserir_lsa(tst, 2, 3, 18);
	inserir_lsa(tst, 2, 1, 728);

	printf("distancia entre 2 e 1: %d\n\n", custo_a_b_lsa(tst, 2, 1));
	printf("distancia entre 1 e 3: %d\n\n", custo_a_b_lsa(tst, 1, 3));
	printf("distancia entre 1 e 2: %d\n\n", custo_a_b_lsa(tst, 1, 2));

	printf("quantidade de cidades, %d\n", qtd_cidades_lsa(tst));

	destruir_lsa(tst);
}
